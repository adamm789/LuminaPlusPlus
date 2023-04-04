#include "Shape.h"
#include "Submesh.h"
#include "Model.h"
#include "Mesh.h"

//https://github.com/NotAdam/Lumina/blob/master/src/Lumina/Models/Models/Submesh.cs

Submesh::Submesh()
{
}

Submesh::Submesh(Model* model, int meshIndex, int subMeshIndex) {
	MdlStructs::MeshStruct currentMesh = model->File->Meshes[meshIndex];
	int subMeshListIndex = currentMesh.SubMeshIndex + subMeshIndex;
	MdlStructs::SubmeshStruct* currentSubMesh = &model->File->Submeshes[subMeshListIndex];

	IndexOffset = currentSubMesh->IndexOffset;
	IndexNum = currentSubMesh->IndexCount;

	for (int i = 0; i < model->File->ModelHeader.AttributeCount; i++) {
		if (((1 << i) & currentSubMesh->AttributeIndexMask) > 0) {
			int nameOffset = model->File->AttributeNameOffsets[i];
			Attributes.push_back(model->StringOffsetToStringMap[(int)nameOffset]);
		}
	}

	if (currentSubMesh->BoneStartIndex == 65535) return;
	int boneEndIndex = currentSubMesh->BoneStartIndex + currentSubMesh->BoneCount;
	if (boneEndIndex > model->File->SubmeshBoneMap.size()) {
		boneEndIndex = model->File->SubmeshBoneMap.size();
	}
	for (int i = currentSubMesh->BoneStartIndex; i < boneEndIndex; i++) {
		if (i > model->File->SubmeshBoneMap.size()) {
			continue;
		}

		uint16_t boneIndex = model->File->SubmeshBoneMap[i];
		uint32_t boneOffset = model->File->BoneNameOffsets[boneIndex];
		std::string boneName = model->StringOffsetToStringMap[(int)boneOffset];
		Bones.push_back(boneName);
	}
}