#include "MdlFile.h"
#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>

MdlFile::MdlFile() {}

MdlFile::MdlFile(const char* filePath) {
	std::ifstream ifs;
	ifs.open(filePath, std::ios::in | std::ios::binary);

	ifs.seekg(0, std::ios::end);
	long length = ifs.tellg();

	if (!ifs.good()) {
		std::cout << "input stream was not good" << std::endl;
		return;
	}

	ifs.seekg(0, std::ios::beg);
	Data = new char[length];
	ifs.read(Data, length);

	ifs.seekg(0, std::ios::beg);

	ifs.read(reinterpret_cast<char*>(&FileHeader), sizeof(FileHeader));

	VertexDeclarations = new MdlStructs::VertexDeclarationStruct[FileHeader.VertexDeclarationCount];
	for (int i = 0; i < FileHeader.VertexDeclarationCount; i++) {
		ifs.read(reinterpret_cast<char*>(&VertexDeclarations[i]), sizeof(MdlStructs::VertexDeclarationStruct));
	}
	ifs.read(reinterpret_cast<char*>(&StringCount), sizeof(StringCount));

	uint16_t val1 = 0;
	ifs.read(reinterpret_cast<char*>(&val1), sizeof(val1));

	ifs.read(reinterpret_cast<char*>(&StringSize), sizeof(StringSize));

	Strings = new char[StringSize];
	ifs.read(Strings, StringSize);

	ifs.read(reinterpret_cast<char*>(&ModelHeader), sizeof(MdlStructs::ModelHeader));

	ElementIds = new MdlStructs::ElementIdStruct[ModelHeader.ElementIdCount];
	for (int i = 0; i < ModelHeader.ElementIdCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ElementIds[i]), sizeof(MdlStructs::ElementIdStruct));
	}

	ifs.read(reinterpret_cast<char*>(&Lods), sizeof(Lods));

	ExtraLodEnabled = ((ModelHeader.Flags2 << 4) & (0b00001000)) != 0;
	if (ExtraLodEnabled) {
		ifs.read(reinterpret_cast<char*>(&ExtraLods), sizeof(ExtraLods));
	}

	Meshes = new MdlStructs::MeshStruct[ModelHeader.MeshCount];
	for (int i = 0; i < ModelHeader.MeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Meshes[i]), sizeof(MdlStructs::MeshStruct));
	}

	AttributeNameOffsets = new unsigned int[ModelHeader.AttributeCount];
	for (int i = 0; i < ModelHeader.AttributeCount; i++) {
		ifs.read(reinterpret_cast<char*>(&AttributeNameOffsets[i]), sizeof(unsigned int));
	}

	TerrainShadowMeshes = new MdlStructs::TerrainShadowMeshStruct[ModelHeader.TerrainShadowMeshCount];
	for (int i = 0; i < ModelHeader.TerrainShadowMeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&TerrainShadowMeshes[i]), sizeof(MdlStructs::TerrainShadowMeshStruct));
	}

	Submeshes = new MdlStructs::SubmeshStruct[ModelHeader.SubmeshCount];
	for (int i = 0; i < ModelHeader.SubmeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Submeshes[i]), sizeof(MdlStructs::SubmeshStruct));
	}

	TerrainShadowSubmeshes = new MdlStructs::TerrainShadowSubmeshStruct[ModelHeader.TerrainShadowSubmeshCount];
	for (int i = 0; i < ModelHeader.TerrainShadowSubmeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&TerrainShadowMeshes[i]), sizeof(MdlStructs::TerrainShadowSubmeshStruct));
	}

	MaterialNameOffsets = new uint32_t[ModelHeader.MaterialCount];
	for (int i = 0; i < ModelHeader.MaterialCount; i++) {
		ifs.read(reinterpret_cast<char*>(&MaterialNameOffsets[i]), sizeof(uint32_t));
	}

	BoneNameOffsets = new uint32_t[ModelHeader.BoneCount];
	for (int i = 0; i < ModelHeader.BoneCount; i++) {
		ifs.read(reinterpret_cast<char*>(&BoneNameOffsets[i]), sizeof(uint32_t));
	}

	BoneTables = new MdlStructs::BoneTableStruct[ModelHeader.BoneTableCount];
	for (int i = 0; i < ModelHeader.BoneTableCount; i++) {
		//std::fill(BoneTables[i].BoneIndex, BoneTables[i].BoneIndex + 64, 0);
		ifs.read(reinterpret_cast<char*>(&BoneTables[i]), sizeof(MdlStructs::BoneTableStruct));
	}

	Shapes = new MdlStructs::ShapeStruct[ModelHeader.ShapeCount];
	for (int i = 0; i < ModelHeader.ShapeCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Shapes[i]), sizeof(MdlStructs::ShapeStruct));
	}

	ShapeMeshes = new MdlStructs::ShapeMeshStruct[ModelHeader.ShapeMeshCount];
	for (int i = 0; i < ModelHeader.ShapeMeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ShapeMeshes[i]), sizeof(MdlStructs::ShapeMeshStruct));
	}

	ShapeValues = new MdlStructs::ShapeValueStruct[ModelHeader.ShapeValueCount];
	for (int i = 0; i < ModelHeader.ShapeValueCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ShapeValues[i]), sizeof(MdlStructs::ShapeValueStruct));
	}

	uint32_t submeshBoneMapSize = 0;
	ifs.read(reinterpret_cast<char*>(&submeshBoneMapSize), sizeof(uint32_t));

	fprintf(stdout, "submeshBoneMapSize: %i\n", (int)submeshBoneMapSize/2);

	SubmeshBoneMap = new uint16_t[(int)submeshBoneMapSize/2];
	for (int i = 0; i < (int)submeshBoneMapSize/2; i++) {
		ifs.read(reinterpret_cast<char*>(&SubmeshBoneMap[i]), sizeof(uint16_t));
	}

	unsigned char paddingAmount;
	std::cout << ifs.tellg() << std::endl;
	ifs.read(reinterpret_cast<char*>(&paddingAmount), sizeof(unsigned char));
	ifs.seekg((int)paddingAmount * (sizeof(unsigned char)), std::ios::cur);
	std::cout << ifs.tellg() << std::endl;

	ifs.read(reinterpret_cast<char*>(&BoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&ModelBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&WaterBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&VerticalFogBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));

	BoneBoundingBoxes = new MdlStructs::BoundingBoxStruct[ModelHeader.BoneCount];
	for (int i = 0; i < ModelHeader.BoneCount; i++) {
		ifs.read(reinterpret_cast<char*>(&BoneBoundingBoxes[i]), sizeof(MdlStructs::BoundingBoxStruct));
	}
	int x = 0;
}

void MdlFile::Destroy() {
	delete[] Data;
	delete[] VertexDeclarations;
	delete[] Strings;

	delete[] ElementIds;
	delete[] Meshes;

	delete[] AttributeNameOffsets;

	delete[] TerrainShadowMeshes;
	delete[] Submeshes;
	delete[] TerrainShadowSubmeshes;

	delete[] MaterialNameOffsets;
	delete[] BoneNameOffsets;
	delete[] BoneTables;

	delete[] Shapes;
	delete[] ShapeMeshes;
	delete[] ShapeValues;

	delete[] SubmeshBoneMap;

	delete[] BoneBoundingBoxes;
}
