#pragma once
#include "Material.h"
#include "Submesh.h"
#include "Vertex.h"
#include "MdlStructs.h"

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

	Mesh(Model* parent, int index, std::list<Mesh::MeshType> types);

	Model* Parent;
	int MeshIndex;
	std::list<Mesh::MeshType> Types;
	std::string* Attributes;
	std::vector<Submesh> Submeshes;
	unsigned short* BoneTable;
	std::vector<Vertex> Vertices;
	std::vector<unsigned short> Indices;
	Material Material;


private:
	void BuildMesh();
	void ReadBoneTable();
	void ReadIndices();
	void ReadVertices();
	void ReadSubmeshes();

	int SetElementField(Vertex* v, MdlStructs::VertexElement element, char* arr, int offset);
};

