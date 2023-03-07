#pragma once
#include <string>
#include <vector>
#include "Texture.h"

class Model;
class Material
{
public:
	Material();
	Material(Model* parent, std::string path, int variantId = 1);

	std::string MaterialPath;
	std::string ResolvedPath;
	Model* Parent;
	// TODO: MtrlFile File
	std::vector<Texture> Textures;
	std::string ShaderPack;
	int VariantId;
};

