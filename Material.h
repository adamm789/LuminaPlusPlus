#pragma once
#include <string>
#include "Texture.h"

class Model;
class Material
{
public:
	Material();
	Material(Model* parent, std::string path, int variantId = 1);
	~Material();

	std::string MaterialPath;
	std::string ResolvedPath;
	Model* Parent;
	// TODO: MtrlFile File
	Texture* Textures;
	std::string ShaderPack;
	int VariantId;
};

