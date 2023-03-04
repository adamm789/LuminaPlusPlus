#include "Mesh.h"
#include "Model.h"
#include "MdlStructs.h"

#include <algorithm>
#include <array>

Mesh::Mesh(Model* parent, int index, std::list<Mesh::MeshType> types)
{
	Parent = parent;
	MeshIndex = index;
	Types = types;

	BuildMesh();
}

void Mesh::BuildMesh() {
	ReadBoneTable();
	ReadIndices();
	ReadVertices();
	ReadSubmeshes();

	int matIndex = Parent->File->Meshes[MeshIndex].MaterialIndex;
	Material = Parent->Materials[matIndex];
}

void Mesh::ReadBoneTable() {
	MdlStructs::MeshStruct currentMesh = Parent->File->Meshes[MeshIndex];
	int boneTableIndex = currentMesh.BoneTableIndex;
	if (boneTableIndex != 255) {
		BoneTable = Parent->File->BoneTables[boneTableIndex].BoneIndex;
	}
}

void Mesh::ReadIndices() {
	MdlStructs::MeshStruct currentMesh = Parent->File->Meshes[MeshIndex];

	int offset = Parent->File->FileHeader.IndexOffset[(int)Parent->Lod] + (currentMesh.StartIndex * 2);
	int count = currentMesh.IndexCount;

	for (int i = 0; i < count; i++) {
		unsigned char byte1 = Parent->File->Data[offset + (i * 2)];
		unsigned char byte2 = Parent->File->Data[offset + (i * 2) + 1];

		//unsigned short number = byte1 + (byte2 << 8);
		unsigned short number;
		memcpy(&number, &Parent->File->Data[offset + (i * 2)], sizeof(number));
		Indices.push_back(number);
	}
}

bool CompareVertexElement(const MdlStructs::VertexElement& lhs, const MdlStructs::VertexElement& rhs) {
	return lhs.Offset < rhs.Offset;
}

bool ValidVertexElement(const MdlStructs::VertexElement v) {
	if (v.Stream < 0) return false;
	switch ((Vertex::VertexType)v.Type) {
	case Vertex::VertexType::Single3:
	case Vertex::VertexType::Single4:
	case Vertex::VertexType::UInt:
	case Vertex::VertexType::ByteFloat4:
	case Vertex::VertexType::Half2:
	case Vertex::VertexType::Half4:
		break;
	default:
		return false;
	}
	switch ((Vertex::VertexUsage)v.Usage) {
	case Vertex::VertexUsage::Normal:
	case Vertex::VertexUsage::BlendIndices:
	case Vertex::VertexUsage::Position:
	case Vertex::VertexUsage::BlendWeights:
	case Vertex::VertexUsage::UV:
	case Vertex::VertexUsage::Tangent2:
	case Vertex::VertexUsage::Tangent1:
	case Vertex::VertexUsage::Color:
		break;
	default:
		return false;
	}
	return true;
}

void Mesh::ReadVertices() {
	MdlStructs::MeshStruct currentMesh = Parent->File->Meshes[MeshIndex];
	MdlStructs::VertexDeclarationStruct currentDecl = Parent->File->VertexDeclarations[MeshIndex];

	std::vector<MdlStructs::VertexElement> orderedElements;
	std::copy_if(std::begin(currentDecl.VertexElements), std::end(currentDecl.VertexElements), std::back_inserter(orderedElements), ValidVertexElement);
	std::sort(std::begin(orderedElements), std::end(orderedElements), CompareVertexElement);

	int offsets[3] = {
		Parent->File->FileHeader.VertexOffset[(int)Parent->Lod] + currentMesh.VertexBufferOffset[0],
		Parent->File->FileHeader.VertexOffset[(int)Parent->Lod] + currentMesh.VertexBufferOffset[1],
		Parent->File->FileHeader.VertexOffset[(int)Parent->Lod] + currentMesh.VertexBufferOffset[2]
	};

	for (int i = 0; i < currentMesh.VertexCount; i++) {
		Vertices.push_back(Vertex());

		for (int j = 0; j < orderedElements.size(); j++) {
			MdlStructs::VertexElement element = orderedElements[j];
			if ((Vertex::VertexUsage)element.Usage == Vertex::VertexUsage::Position) {
				int x = 0;
			}
			int stream = element.Stream;
			int bytesRead = SetElementField(&Vertices[i], element, Parent->File->Data, offsets[stream]);
			if (bytesRead == 0) {
				std::cout << "Read zero bytes" << std::endl;
				return;
			}
			offsets[stream] += bytesRead;
		}
	}
	int x = 0;
}



/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="element"></param>
/// <param name="arr"></param>
/// <param name="offset"></param>
/// <returns>The number of bytes read</returns>
int Mesh::SetElementField(Vertex* v, MdlStructs::VertexElement element, char* arr, int offset) {

	Vertex::VertexType type = (Vertex::VertexType)element.Type;
	Vertex::VertexUsage usage = (Vertex::VertexUsage)element.Usage;

	float data[4]{ 0,0,0,0 };
	switch (type) {
	case Vertex::VertexType::Single3:
		// Vector3
		for (int i = 0; i < 3; i++) {
			memcpy(&data[i], &arr[offset + (i * 4)], sizeof(float));
		}
		data[3] = 1;
		break;
	case Vertex::VertexType::Single4:
		//Vector4
		for (int i = 0; i < 4; i++) {
			memcpy(&data[i], &arr[offset + (i * 4)], sizeof(float));
		}
		break;
	case Vertex::VertexType::UInt:
		//Vector4
		for (int i = 0; i < 4; i++) {
			data[i] = (unsigned char)arr[offset + i];
		}
		break;
	case Vertex::VertexType::ByteFloat4:
		//Vector4
		for (int i = 0; i < 4; i++) {
			data[i] = (float)((arr[offset + i]) / 255);
		}
		break;
	case Vertex::VertexType::Half2:
		//Vector2
		//memcpy(&data[0], &arr[offset], sizeof(__int16));
		//memcpy(&data[1], &arr[offset + 2], sizeof(__int16));
		data[0] = arr[offset] + (arr[offset + 1] << 8);
		data[1] = arr[offset + 2] + (arr[offset + 3] << 8);
		data[2] = 0;
		data[3] = 0;
		break;
	case Vertex::VertexType::Half4:
		//Vector4
		data[0] = arr[offset] + (arr[offset + 1] << 8);
		data[1] = arr[offset + 2] + (arr[offset + 3] << 8);
		data[2] = arr[offset + 4] + (arr[offset + 5] << 8);
		data[3] = arr[offset + 6] + (arr[offset + 7] << 8);
		break;
	default:
		break;
	}

	switch (usage) {
	case Vertex::VertexUsage::Position:
		for (int i = 0; i < 4; i++) {
			v->Position[i] = data[i];
		}
		//std::cout << offset << std::endl;
		break;
	case Vertex::VertexUsage::BlendWeights:
		for (int i = 0; i < 4; i++) {
			v->BlendWeights[i] = data[i];
		}
		break;
	case Vertex::VertexUsage::BlendIndices:
		for (int i = 0; i < 4; i++) {
			v->BlendIndices[i] = (char)data[i];
		}
		break;
	case Vertex::VertexUsage::Normal: 
		for (int i = 0; i < 3; i++) {
			v->Normal[i] = data[i];
		}
		break;
	case Vertex::VertexUsage::UV:
		for (int i = 0; i < 4; i++) {
			v->UV[i] = data[i];
		}
		break;
	case Vertex::VertexUsage::Tangent2:
		for (int i = 0; i < 4; i++) {
			v->Tangent2[i] = data[i];
		}
		break;
	case Vertex::VertexUsage::Tangent1:
		for (int i = 0; i < 4; i++) {
			v->Tangent1[i] = data[i];
		}
		break;
	case Vertex::VertexUsage::Color:
		for (int i = 0; i < 4; i++) {
			v->Color[i] = data[i];
		}
		break;
	default:
		break;
	}

	switch (type) {
	case Vertex::VertexType::Single3:
		return 12;
	case Vertex::VertexType::Single4:
		return 16;
	case Vertex::VertexType::UInt:
		return 4;
	case Vertex::VertexType::ByteFloat4:
		return 4;
	case Vertex::VertexType::Half2:
		return 4;
	case Vertex::VertexType::Half4:
		return 8;
	default:
		return 0;
	}
}

void Mesh::ReadSubmeshes() {
	MdlStructs::MeshStruct currentMesh = Parent->File->Meshes[MeshIndex];

	for (int i = 0; i < currentMesh.SubMeshCount; i++) {
		Submeshes.push_back(Submesh(Parent, MeshIndex, i));
	}
}

