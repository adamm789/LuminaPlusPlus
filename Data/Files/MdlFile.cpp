#include "MdlFile.h"
#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>
#include <bitset>
#include "../LuminaBinaryReader.h"
#include "../../Models/Models/Model.h"

void MdlFile::LoadFromFile(std::string filePath) {
	std::ifstream ifs;
	try {
		ifs.open(filePath, std::ios::in | std::ios::binary);

		ifs.seekg(0, std::ios::end);
		long length = ifs.tellg();

		if (!ifs.good()) {
			fprintf(stderr, "File \"%s\" could not be read.", filePath.c_str());
			return;
		}

		ifs.seekg(0, std::ios::beg);
		//Data = new char[length];
		//ifs.read(Data, length);
		Data = std::vector<std::byte>(length);
		ifs.read((char*) & Data[0], length);

		int pos = 0;

		ifs.seekg(0, std::ios::beg);

		ifs.read((char*)&FileHeader, sizeof(FileHeader));

		VertexDeclarations = std::vector<MdlStructs::VertexDeclarationStruct>(FileHeader.VertexDeclarationCount);

		// implement a (Lumina)BinaryReader?
		for (int i = 0; i < FileHeader.VertexDeclarationCount; i++) {
			ifs.read((char*)&VertexDeclarations[i], sizeof(MdlStructs::VertexDeclarationStruct));
		}
		ifs.read((char*)&StringCount, sizeof(StringCount));

		uint16_t val1 = 0;
		ifs.read((char*)&val1, sizeof(uint16_t));

		ifs.read((char*)&StringSize, sizeof(StringSize));

		Strings = std::vector<char>(StringSize);
		ifs.read((char*)&Strings[0], StringSize);


		ifs.read((char*)&ModelHeader, sizeof(MdlStructs::ModelHeader));

		ElementIds = std::vector<MdlStructs::ElementIdStruct>(ModelHeader.ElementIdCount);
		for (int i = 0; i < ModelHeader.ElementIdCount; i++) {
			ifs.read((char*)&ElementIds[i], sizeof(MdlStructs::ElementIdStruct));
		}

		ifs.read((char*)(&Lods), sizeof(Lods));

		ExtraLodEnabled = (ModelHeader.Flags2 << 0x10) > 0;
		if (ExtraLodEnabled) {
			ifs.read((char*)&ExtraLods, sizeof(ExtraLods));
		}

		Meshes = std::vector<MdlStructs::MeshStruct>(ModelHeader.MeshCount);
		for (int i = 0; i < ModelHeader.MeshCount; i++) {
			ifs.read((char*)&Meshes[i], sizeof(MdlStructs::MeshStruct));
		}

		AttributeNameOffsets = std::vector<uint32_t>(ModelHeader.AttributeCount);
		for (int i = 0; i < ModelHeader.AttributeCount; i++) {
			ifs.read((char*)&AttributeNameOffsets[i], sizeof(uint32_t));
		}

		TerrainShadowMeshes = std::vector<MdlStructs::TerrainShadowMeshStruct>(ModelHeader.TerrainShadowMeshCount);
		for (int i = 0; i < ModelHeader.TerrainShadowMeshCount; i++) {
			ifs.read((char*)&TerrainShadowMeshes[i], sizeof(MdlStructs::TerrainShadowMeshStruct));
		}

		Submeshes = std::vector<MdlStructs::SubmeshStruct>(ModelHeader.SubmeshCount);
		for (int i = 0; i < ModelHeader.SubmeshCount; i++) {
			ifs.read((char*)&Submeshes[i], sizeof(MdlStructs::SubmeshStruct));
		}

		TerrainShadowSubmeshes = std::vector<MdlStructs::TerrainShadowSubmeshStruct>(ModelHeader.TerrainShadowSubmeshCount);
		for (int i = 0; i < ModelHeader.TerrainShadowSubmeshCount; i++) {
			ifs.read((char*)&TerrainShadowMeshes[i], sizeof(MdlStructs::TerrainShadowSubmeshStruct));
		}

		MaterialNameOffsets = std::vector<uint32_t>(ModelHeader.MaterialCount);
		for (int i = 0; i < ModelHeader.MaterialCount; i++) {
			ifs.read((char*)&MaterialNameOffsets[i], sizeof(uint32_t));
		}

		BoneNameOffsets = std::vector<uint32_t>(ModelHeader.BoneCount);
		for (int i = 0; i < ModelHeader.BoneCount; i++) {
			ifs.read((char*)&BoneNameOffsets[i], sizeof(uint32_t));
		}

		BoneTables = std::vector<MdlStructs::BoneTableStruct>(ModelHeader.BoneTableCount);
		for (int i = 0; i < ModelHeader.BoneTableCount; i++) {
			ifs.read((char*)&BoneTables[i], sizeof(MdlStructs::BoneTableStruct));
		}

		Shapes = std::vector<MdlStructs::ShapeStruct>(ModelHeader.ShapeCount);
		for (int i = 0; i < ModelHeader.ShapeCount; i++) {
			ifs.read((char*)&Shapes[i], sizeof(MdlStructs::ShapeStruct));
		}

		ShapeMeshes = std::vector<MdlStructs::ShapeMeshStruct>(ModelHeader.ShapeMeshCount);
		for (int i = 0; i < ModelHeader.ShapeMeshCount; i++) {
			ifs.read((char*)&ShapeMeshes[i], sizeof(MdlStructs::ShapeMeshStruct));
		}

		ShapeValues = std::vector<MdlStructs::ShapeValueStruct>(ModelHeader.ShapeValueCount);
		for (int i = 0; i < ModelHeader.ShapeValueCount; i++) {
			ifs.read((char*)&ShapeValues[i], sizeof(MdlStructs::ShapeValueStruct));
		}

		uint32_t submeshBoneMapSize = 0;
		ifs.read((char*)&submeshBoneMapSize, sizeof(uint32_t));

		SubmeshBoneMap = std::vector<uint16_t>((int)submeshBoneMapSize / 2);
		for (int i = 0; i < (int)submeshBoneMapSize / 2; i++) {
			ifs.read((char*)&SubmeshBoneMap[i], sizeof(uint16_t));
		}

		uint8_t paddingAmount = 0;
		ifs.read((char*)&paddingAmount, sizeof(uint8_t));
		ifs.seekg((int)paddingAmount * sizeof(uint8_t), std::ios::cur);

		ifs.read((char*)&BoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
		ifs.read((char*)&ModelBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
		ifs.read((char*)&WaterBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
		ifs.read((char*)&VerticalFogBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));

		BoneBoundingBoxes = std::vector<MdlStructs::BoundingBoxStruct>(ModelHeader.BoneCount);
		for (int i = 0; i < ModelHeader.BoneCount; i++) {
			ifs.read((char*)&BoneBoundingBoxes[i], sizeof(MdlStructs::BoundingBoxStruct));
		}
		HasLoaded = true;
	}
	catch (int e) {
		fprintf(stderr, "An exception has occurred: %i\n", e);
		fprintf(stderr, "Model file: %s could not be read.\n", filePath.c_str());
	}
	ifs.close();
}




MdlFile* MdlFile::FromModel(Model* mdl) {
	MdlFile* ret = new MdlFile();

	return ret;
}

void MdlFile::WriteToFile(std::string outputPath) {
	std::ofstream ofs;
	try {

	}
	catch (int e) {

	}
	ofs.close();
}

MdlFile::~MdlFile() {
	
	//delete[] Data;
}
