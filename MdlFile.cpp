#include "MdlFile.h"
#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>

MdlFile::MdlFile() {}

MdlFile::MdlFile(std::string filePath) {
	std::ifstream ifs;
	std::cout << filePath << std::endl;
	ifs.open(filePath, std::ios::in | std::ios::binary);

	ifs.seekg(0, std::ios::end);
	long length = ifs.tellg();

	std::cout << "Data length: ";
	std::cout << length << std::endl;

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

	__int16 val1;
	ifs.read(reinterpret_cast<char*>(&val1), sizeof(val1));

	ifs.read(reinterpret_cast<char*>(&StringSize), sizeof(StringSize));

	Strings = new char[StringSize];
	ifs.read(Strings, StringSize);

	ifs.read(reinterpret_cast<char*>(&ModelHeader), sizeof(MdlStructs::ModelHeader));

	//if (ModelHeader.ElementIdCount > 0) {
	ElementIds = new MdlStructs::ElementIdStruct[ModelHeader.ElementIdCount];
	for (int i = 0; i < ModelHeader.ElementIdCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ElementIds[i]), sizeof(MdlStructs::ElementIdStruct));
	}
	//}
	ifs.read(reinterpret_cast<char*>(&Lods), sizeof(Lods));

	// if ExtraLodsEnabled
	ExtraLodEnabled = ((ModelHeader.Flags2 << 4) & (0b00001000)) != 0;
	if (ExtraLodEnabled) {
		ifs.read(reinterpret_cast<char*>(&ExtraLods), sizeof(ExtraLods));
	}

	//if (ModelHeader.MeshCount > 0) {
	Meshes = new MdlStructs::MeshStruct[ModelHeader.MeshCount];
	for (int i = 0; i < ModelHeader.MeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Meshes[i]), sizeof(MdlStructs::MeshStruct));
	}
	//}

	//if (ModelHeader.AttributeCount > 0) {
	AttributeNameOffsets = new unsigned int[ModelHeader.AttributeCount];
	for (int i = 0; i < ModelHeader.AttributeCount; i++) {
		ifs.read(reinterpret_cast<char*>(&AttributeNameOffsets[i]), sizeof(unsigned int));
	}
	//}

	//if (ModelHeader.TerrainShadowMeshCount > 0) {
	TerrainShadowMeshes = new MdlStructs::TerrainShadowMeshStruct[ModelHeader.TerrainShadowMeshCount];
	for (int i = 0; i < ModelHeader.TerrainShadowMeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&TerrainShadowMeshes[i]), sizeof(MdlStructs::TerrainShadowMeshStruct));
	}
	//}

	//if (ModelHeader.SubmeshCount > 0) {
	Submeshes = new MdlStructs::SubmeshStruct[ModelHeader.SubmeshCount];
	for (int i = 0; i < ModelHeader.SubmeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Submeshes[i]), sizeof(MdlStructs::SubmeshStruct));
	}
	//}

	//if (ModelHeader.TerrainShadowSubmeshCount > 0) {
	TerrainShadowSubmeshes = new MdlStructs::TerrainShadowSubmeshStruct[ModelHeader.TerrainShadowSubmeshCount];
	for (int i = 0; i < ModelHeader.TerrainShadowSubmeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&TerrainShadowMeshes[i]), sizeof(MdlStructs::TerrainShadowSubmeshStruct));
	}
	//}

	//if (ModelHeader.MaterialCount > 0) {
	MaterialNameOffsets = new unsigned int[ModelHeader.MaterialCount];
	for (int i = 0; i < ModelHeader.MaterialCount; i++) {
		ifs.read(reinterpret_cast<char*>(&MaterialNameOffsets[i]), sizeof(unsigned int));
	}
	//}

	//if (ModelHeader.BoneCount > 0) {
	BoneNameOffsets = new unsigned int[ModelHeader.BoneCount];
	for (int i = 0; i < ModelHeader.BoneCount; i++) {
		ifs.read(reinterpret_cast<char*>(&BoneNameOffsets[i]), sizeof(unsigned int));
	}
	//}

	//if (ModelHeader.BoneTableCount > 0) {
	BoneTables = new MdlStructs::BoneTableStruct[ModelHeader.BoneTableCount];
	for (int i = 0; i < ModelHeader.BoneTableCount; i++) {
		ifs.read(reinterpret_cast<char*>(&BoneTables[i]), sizeof(MdlStructs::BoneTableStruct));
	}
	//}

	//if (ModelHeader.ShapeCount > 0) {
	Shapes = new MdlStructs::ShapeStruct[ModelHeader.ShapeCount];
	for (int i = 0; i < ModelHeader.ShapeCount; i++) {
		ifs.read(reinterpret_cast<char*>(&Shapes[i]), sizeof(MdlStructs::ShapeStruct));
	}
	//}

	//if (ModelHeader.ShapeMeshCount > 0) {
	ShapeMeshes = new MdlStructs::ShapeMeshStruct[ModelHeader.ShapeMeshCount];
	for (int i = 0; i < ModelHeader.ShapeMeshCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ShapeMeshes[i]), sizeof(MdlStructs::ShapeMeshStruct));
	}
	//}

	//if (ModelHeader.ShapeValueCount > 0) {
	ShapeValues = new MdlStructs::ShapeValueStruct[ModelHeader.ShapeValueCount];
	for (int i = 0; i < ModelHeader.ShapeValueCount; i++) {
		ifs.read(reinterpret_cast<char*>(&ShapeValues[i]), sizeof(MdlStructs::ShapeValueStruct));
	}
	//}

	unsigned int submeshBoneMapSize;
	ifs.read(reinterpret_cast<char*>(&submeshBoneMapSize), sizeof(unsigned int));

	SubmeshBoneMap = new unsigned short[submeshBoneMapSize / 2];
	for (int i = 0; i < submeshBoneMapSize / 2; i++) {
		ifs.read(reinterpret_cast<char*>(&SubmeshBoneMap[i]), sizeof(unsigned short));
	}

	__int8 paddingAmount;
	std::cout << ifs.tellg() << std::endl;
	ifs.read(reinterpret_cast<char*>(&paddingAmount), sizeof(__int8));
	ifs.seekg((int)paddingAmount * (sizeof(__int8)), std::ios::cur);
	std::cout << ifs.tellg() << std::endl;

	ifs.read(reinterpret_cast<char*>(&BoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&ModelBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&WaterBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));
	ifs.read(reinterpret_cast<char*>(&VerticalFogBoundingBoxes), sizeof(MdlStructs::BoundingBoxStruct));

	//if (ModelHeader.BoneCount > 0) {
	BoneBoundingBoxes = new MdlStructs::BoundingBoxStruct[ModelHeader.BoneCount];
	for (int i = 0; i < ModelHeader.BoneCount; i++) {
		ifs.read(reinterpret_cast<char*>(&BoneBoundingBoxes[i]), sizeof(MdlStructs::BoundingBoxStruct));
	}
	//}
	int x = 0;
}

MdlFile::~MdlFile() {
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