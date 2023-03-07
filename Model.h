#pragma once
#include "MdlFile.h"
#include "Material.h"
#include "Mesh.h"
#include "Shape.h"

#include <map>
#include <list>

class Material;
class Mesh;
class Model
{
public:
	enum class ModelLod {
		High, Med, Low
	};

	Model(MdlFile* mdlFile, ModelLod lod = Model::ModelLod::High, int variantId = 1);

	MdlFile* File;
	ModelLod Lod;
	std::vector<Mesh> Meshes;
	std::vector<Material> Materials;
	std::map<std::string, Shape> Shapes;
	std::map<int, std::string> StringOffsetToStringMap;
	int VariantId;
private:
	void BuildModel();
	void ReadStrings();
	void ReadMaterials();
	void ReadMeshes();
	void ReadShapes();
	std::vector<Mesh::MeshType> GetMeshTypes(int index);
};

