#pragma once
#include "../Materials/Material.h"
#include "Submesh.h"
#include "Vertex.h"
#include "../../Data/Parsing/MdlStructs.h"
#include "Shape.h"

#include <string>
#include <list>

class Model;
class Mesh
{
public:
	enum class MeshType {
		Main,
		Water,
		Shadow,
		TerrainShadow,
		VerticalFog,
		LightShaft,
		Glass,
		MaterialChange,
		CrestChange
	};

	__declspec(dllexport) Mesh(int index);
	__declspec(dllexport) Mesh(Model* parent, int index, std::vector<Mesh::MeshType> types);
	__declspec(dllexport) ~Mesh();

	Model* Parent = nullptr;
	int MeshIndex = 0;
	std::vector<Mesh::MeshType> Types;
	std::vector<std::string> Attributes;
	std::vector<Submesh> Submeshes;
	uint16_t BoneTable[64];
	std::vector<Vertex> Vertices;
	std::vector<uint16_t> Indices;
	Material* Material = nullptr;

	// TODO: Do meshes need to know which Shapes it contains?
	std::vector<Shape> Shapes;

private:
	void BuildMesh();
	void ReadBoneTable();
	void ReadIndices();
	void ReadVertices();
	void ReadSubmeshes();

	int SetElementField(Vertex* v, MdlStructs::VertexElement element, std::vector<std::byte> arr, int offset);
};

