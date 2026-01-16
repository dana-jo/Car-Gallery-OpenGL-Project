#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;             // camera position in world space
uniform sampler2D tex;            // base/albedo texture
uniform float material_shininess; // e.g. 32.0

// tunable limits
const int MAX_POINT_LIGHTS = 15; //8
const int MAX_SPOT_LIGHTS = 15; //4

// Light structs
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool enabled;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    bool enabled;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;      // cos(innerAngle)
    float outerCutOff; // cos(outerAngle)
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    bool enabled;
};

uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int numSpotLights;

// helper: compute Blinn-Phong contribution from a directional light
vec3 calcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 albedo)
{
    vec3 lightDir = normalize(-light.direction); // direction points to light source
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(normal, halfway), 0.0), material_shininess);

    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec; // we don't have a specular map -> white highlight
    return ambient + diffuse + specular;
}

// helper: point light with attenuation
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(normal, halfway), 0.0), material_shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return ambient + diffuse + specular;
}

// helper: spotlight (cone + attenuation + smooth edges)
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(normal, halfway), 0.0), material_shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity based on angle
    float theta = dot(lightDir, normalize(-light.direction)); // cos of angle between light cone axis and fragment
    float epsilon = light.cutOff - light.outerCutOff; // cutOff > outerCutOff (both cosines)
    float intensity = clamp((theta - light.outerCutOff) / max(epsilon, 0.001), 0.0, 1.0);

    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}

void main()
{
    vec4 texColor = texture(tex, TexCoord);
    if (texColor.a < 0.01)
        discard;

    vec3 albedo = texColor.rgb;
    vec3 N = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);

    if (dirLight.enabled)
        result += calcDirLight(dirLight, N, viewDir, albedo);

    for (int i = 0; i < numPointLights && i < MAX_POINT_LIGHTS; ++i)
    {
        if (pointLights[i].enabled)
            result += calcPointLight(pointLights[i], N, FragPos, viewDir, albedo);
    }
    for (int i = 0; i < numSpotLights && i < MAX_SPOT_LIGHTS; ++i)
    {
        if (spotLights[i].enabled)
            result += calcSpotLight(spotLights[i], N, FragPos, viewDir, albedo);
    }

    FragColor = vec4(result, texColor.a);
}
