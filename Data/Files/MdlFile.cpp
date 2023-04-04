#include "MdlFile.h"
#include "MdlFile.h"
#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>
#include <bitset>
#include "../LuminaBinaryReader.h"
#include "../../Models/Models/Model.h"


void MdlFile::LoadFromFile(const char* filePath) {
	std::ifstream ifs;
	try {
		ifs.open(filePath, std::ios::in | std::ios::binary);

		ifs.seekg(0, std::ios::end);
		long length = ifs.tellg();

		if (!ifs.good()) {
			fprintf(stderr, "File \"%s\" could not be read\f.", filePath);
			return;
		}

		ifs.seekg(0, std::ios::beg);
		//Data = new char[length];
		//ifs.read(Data, length);
		Data = std::vector<std::byte>(length);
		ifs.read((char*)&Data[0], length);

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
		fprintf(stderr, "Model file: %s could not be read.\n", filePath);
	}

	ifs.close();
}

MdlFile* MdlFile::LoadFromFileStatic(const char* filePath)
{
	std::ifstream ifs;
	try {
		ifs.open(filePath, std::ios::in | std::ios::binary);

		ifs.seekg(0, std::ios::end);
		long length = ifs.tellg();

		if (!ifs.good()) {
			fprintf(stderr, "File \"%s\" could not be read\f.", filePath);
			return nullptr;
		}

		ifs.seekg(0, std::ios::beg);
		//Data = new char[length];
		//ifs.read(Data, length);
		auto Data = std::vector<std::byte>(length);
		ifs.read((char*)&Data[0], length);

		return LoadFromData(Data);
	}
	catch (int e) {
		fprintf(stderr, "An exception has occurred: %i\n", e);
		fprintf(stderr, "Model file: %s could not be read.\n", filePath);
	}
	ifs.close();

	return nullptr;
}

MdlFile* LoadFromMemCopy(std::vector<std::byte> data) {
	MdlFile* ret = new MdlFile();
	ret->Data = data;
	LuminaBinaryReader Reader(data);

	Reader.MemCpy(&ret->FileHeader, sizeof(MdlStructs::ModelFileHeader));

	ret->VertexDeclarations.resize(ret->FileHeader.VertexDeclarationCount);
	for (int i = 0; i < ret->VertexDeclarations.size(); i++) {
		Reader.MemCpy(&ret->VertexDeclarations[i], sizeof(MdlStructs::VertexDeclarationStruct));
	}

	ret->StringCount = Reader.ReadUInt16();
	Reader.ReadUInt16();

	ret->StringSize = Reader.ReadUInt32();

	ret->Strings.resize(ret->StringSize);
	Reader.MemCpy(&ret->Strings[0], ret->StringSize);

	Reader.MemCpy(&ret->ModelHeader, sizeof(MdlStructs::ModelHeader));
	ret->ElementIds.resize(ret->ModelHeader.ElementIdCount);
	ret->Meshes.resize(ret->ModelHeader.MeshCount);
	ret->BoneTables.resize(ret->ModelHeader.BoneTableCount);
	ret->Shapes.resize(ret->ModelHeader.ShapeCount);
	ret->BoneBoundingBoxes.resize(ret->ModelHeader.BoneCount);

	for (int i = 0; i < ret->ModelHeader.ElementIdCount; i++) {
		Reader.MemCpy(&ret->ElementIds[i], sizeof(MdlStructs::ElementIdStruct));
	}
	Reader.MemCpy(&ret->Lods, sizeof(MdlStructs::LodStruct) * 3);

	ret->ExtraLodEnabled = (ret->ModelHeader.Flags2 << 0x10) > 0;
	if (ret->ExtraLodEnabled) {
		Reader.MemCpy(&ret->ExtraLods[0], sizeof(MdlStructs::ExtraLodStruct) * 3);
	}

	for (int i = 0; i < ret->Meshes.size(); i++) {
		Reader.MemCpy(&ret->Meshes[i], sizeof(MdlStructs::MeshStruct));
	}

	ret->AttributeNameOffsets.resize(ret->ModelHeader.AttributeCount);
	for (int i = 0; i < ret->AttributeNameOffsets.size(); i++) {
		Reader.MemCpy(&ret->AttributeNameOffsets[i], sizeof(uint32_t));
	}

	ret->TerrainShadowMeshes.resize(ret->ModelHeader.TerrainShadowMeshCount);
	for (int i = 0; i < ret->TerrainShadowMeshes.size(); i++) {
		Reader.MemCpy(&ret->TerrainShadowMeshes[i], sizeof(MdlStructs::TerrainShadowMeshStruct));
	}

	ret->Submeshes.resize(ret->ModelHeader.SubmeshCount);
	for (int i = 0; i < ret->Submeshes.size(); i++) {
		Reader.MemCpy(&ret->Submeshes[i], sizeof(MdlStructs::SubmeshStruct));
	}

	ret->TerrainShadowSubmeshes.resize(ret->ModelHeader.TerrainShadowSubmeshCount);
	for (int i = 0; i < ret->TerrainShadowSubmeshes.size(); i++) {
		Reader.MemCpy(&ret->TerrainShadowMeshes[i], sizeof(MdlStructs::TerrainShadowSubmeshStruct));
	}

	ret->MaterialNameOffsets.resize(ret->ModelHeader.MaterialCount);
	for (int i = 0; i < ret->MaterialNameOffsets.size(); i++) {
		Reader.MemCpy(&ret->MaterialNameOffsets[i], sizeof(uint32_t));
	}

	ret->BoneNameOffsets.resize(ret->ModelHeader.BoneCount);
	for (int i = 0; i < ret->BoneNameOffsets.size(); i++) {
		Reader.MemCpy(&ret->BoneNameOffsets[i], sizeof(uint32_t));
	}

	ret->BoneTables.resize(ret->ModelHeader.BoneTableCount);
	for (int i = 0; i < ret->BoneTables.size(); i++) {
		Reader.MemCpy(&ret->BoneTables[i], sizeof(MdlStructs::BoneTableStruct));
	}

	ret->Shapes.resize(ret->ModelHeader.ShapeCount);
	for (int i = 0; i < ret->Shapes.size(); i++) {
		Reader.MemCpy(& ret->Shapes[i], sizeof(MdlStructs::ShapeStruct));
	}

	ret->ShapeMeshes.resize(ret->ModelHeader.ShapeMeshCount);
	for (int i = 0; i < ret->ShapeMeshes.size(); i++) {
		Reader.MemCpy(&ret->ShapeMeshes[i], sizeof(MdlStructs::ShapeMeshStruct));
	}

	ret->ShapeValues.resize(ret->ModelHeader.ShapeValueCount);
	for (int i = 0; i < ret->ShapeValues.size(); i++) {
		Reader.MemCpy(&ret->ShapeValues[i], sizeof(MdlStructs::ShapeValueStruct));
	}

	uint32_t submeshBoneMapSize = Reader.ReadUInt32();
	ret->SubmeshBoneMap.resize((int)submeshBoneMapSize / 2);
	for (int i = 0; i < (int)submeshBoneMapSize / 2; i++) {
		Reader.MemCpy(&ret->SubmeshBoneMap[i], sizeof(uint16_t));
	}

	uint8_t paddingAmount = Reader.ReadByte();
	Reader.Seek(Reader.Position + paddingAmount);

	Reader.MemCpy(&ret->BoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
	Reader.MemCpy(&ret->ModelBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
	Reader.MemCpy(&ret->WaterBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));
	Reader.MemCpy(&ret->VerticalFogBoundingBoxes, sizeof(MdlStructs::BoundingBoxStruct));

	ret->BoneBoundingBoxes.resize(ret->ModelHeader.BoneCount);
	for (int i = 0; i < ret->BoneBoundingBoxes.size(); i++) {
		Reader.MemCpy(&ret->BoneBoundingBoxes[i], sizeof(MdlStructs::BoundingBoxStruct));
	}

	return ret;
}

MdlFile* MdlFile::LoadFromData(std::vector<std::byte> data) {

	return LoadFromMemCopy(data);

	MdlFile* ret = new MdlFile();
	LuminaBinaryReader Reader(data);
	Reader.ReadStructure(&ret->FileHeader);

	ret->VertexDeclarations.resize(ret->FileHeader.VertexDeclarationCount);
	for (int i = 0; i < ret->VertexDeclarations.size(); i++) {
		Reader.ReadStructure(&ret->VertexDeclarations[i]);
	}

	ret->StringCount = Reader.ReadUInt16();
	Reader.ReadUInt16();

	ret->StringSize = Reader.ReadUInt32();
	ret->Strings.resize(ret->StringSize);
	Reader.CopyBytesInto(ret->Strings[0], ret->StringSize);
	//memcpy(&ret->Strings[0], Reader.ReadBytes(ret->StringSize), ret->StringSize);

	Reader.ReadStructure(&ret->ModelHeader);
	ret->ElementIds.resize(ret->ModelHeader.ElementIdCount);
	for (int i = 0; i < ret->ElementIds.size(); i++) {
		Reader.ReadStructure(&ret->ElementIds[i]);
	}

	Reader.ReadStructure(&ret->Lods);
	ret->ExtraLodEnabled = (ret->ModelHeader.Flags2 << 0x10) > 0;
	if (ret->ExtraLodEnabled) {
		Reader.ReadStructure(&ret->ExtraLods);
	}

	ret->Meshes.resize(ret->ModelHeader.MeshCount);
	for (int i = 0; i < ret->Meshes.size(); i++) {
		Reader.ReadStructure(&ret->Meshes[i]);
	}

	ret->AttributeNameOffsets.resize(ret->ModelHeader.AttributeCount);

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