#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex;
// optionally add material color / other maps here

void main()
{
    vec4 color = texture(tex, TexCoord);

    // If fully transparent or alpha below threshold, discard to avoid sorting artifacts
    if (color.a < 0.01)
        discard;

    // Simple lit color pass (replace with your lighting if you have it)
    FragColor = color;
}
