#pragma once
class Texture
{
public:
    ~Texture();
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
};

