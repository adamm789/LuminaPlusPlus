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

	Mesh(Model* parent, int index, std::vector<Mesh::MeshType> types);
	~Mesh();

	Model* Parent;
	int MeshIndex;
	std::vector<Mesh::MeshType> Types;
	std::vector<std::string> Attributes;
	std::vector<Submesh> Submeshes;
	uint16_t* BoneTable;
	std::vector<Vertex> Vertices;
	std::vector<uint16_t> Indices;
	Material* Material;

	std::vector<Shape> Shapes;
	void AddShape(Shape s);

private:
	void BuildMesh();
	void ReadBoneTable();
	void ReadIndices();
	void ReadVertices();
	void ReadSubmeshes();

	int SetElementField(Vertex* v, MdlStructs::VertexElement element, std::vector<std::byte> arr, int offset);
};

