#pragma once
#include <string>

class Texture
{
public:
	enum class Usage {
        Catchlight,
        Diffuse,
        Envmap,
        Mask,
        Normal,
        Reflection,
        Specular,
        Wave,
        Whitecap,
	};

    Usage TextureUsageSimple;
    std::string TexturePath;
};

