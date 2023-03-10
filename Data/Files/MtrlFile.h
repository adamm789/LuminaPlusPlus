#pragma once
#include <vector>
#include <string>
#include "../Parsing/MtrlStructs.h"

class MtrlFile
{
public:
	MtrlStructs::MaterialFileHeader FileHeader;
	MtrlStructs::MaterialHeader MaterialHeader;
	std::vector<MtrlStructs::TextureOffset> TextureOffsets;
	std::vector<MtrlStructs::UvColorSet> UvColorSets;
	std::vector<MtrlStructs::ColorSet> ColorSets;

	MtrlStructs::ColorSetInfo ColorSetInfo;
	MtrlStructs::ColorSetDyeInfo ColorSetDyeInfo;

	std::vector<MtrlStructs::ShaderKey> ShaderKeys;
	std::vector<MtrlStructs::Constant> Constants;
	std::vector<MtrlStructs::Sampler> Samplers;

	std::vector<uint32_t> ShaderValues;
	char* Strings;

	void LoadFromFile(std::string filePath);
};

