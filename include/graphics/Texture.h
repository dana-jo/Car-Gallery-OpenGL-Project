#pragma once
#include <string>

enum class TextureWrap
{
    Repeat,
    Clamp
};

class Texture
{
public:
    unsigned int id = 0;
    bool hasAlpha = false;

    Texture(const std::string& path, TextureWrap wrap = TextureWrap::Repeat);
    ~Texture() = default;

    void bind(unsigned int unit = 0) const;
};
