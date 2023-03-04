#include "Model.h"
#include "Material.h"
#include <list>

Model::Model() {

}

Model::Model(MdlFile* mdlFile, Model::ModelLod lod, int variantId) {
	File = mdlFile;
	Lod = lod;
	VariantId = variantId;

	ReadStrings();
	ReadMaterials();
	ReadMeshes();
}

void Model::BuildModel() {

}

void Model::ReadStrings() {
	std::string str = "";
	int offset = 0;
	for (int i = 0; i < File->StringSize; i++) {
		if (File->Strings[i] != '\0') {
			str += File->Strings[i];
		}
		else {
			if (str != "") {
				StringOffsetToStringMap.insert(std::pair<int, std::string>(offset, str));
				str = "";
				offset = i + 1;
			}
		}
	}
}

void Model::ReadMaterials() {
	//Materials = new Material*[File->FileHeader.MaterialCount];
	Materials = std::vector<Material>();
	for (int i = 0; i < File->FileHeader.MaterialCount; i++) {
		int pathOffset = File->MaterialNameOffsets[i];
		std::string path = StringOffsetToStringMap[pathOffset];
		std::vector<Material>::iterator it = Materials.begin();

		Materials.insert(it, i + 1, Material(this, path, VariantId));
	}
}

void Model::ReadMeshes() {
	std::vector<std::pair<int, int>> ranges;
	MdlStructs::LodStruct currentLod = File->Lods[(int)Lod];

	ranges.push_back(std::pair<int, int>(currentLod.MeshIndex, currentLod.MeshIndex + currentLod.MeshCount));
	ranges.push_back(std::pair<int, int>(currentLod.WaterMeshIndex, currentLod.WaterMeshIndex + currentLod.WaterMeshCount));
	ranges.push_back(std::pair<int, int>(currentLod.ShadowMeshIndex, currentLod.ShadowMeshIndex + currentLod.ShadowMeshCount));
	ranges.push_back(std::pair<int, int>(currentLod.TerrainShadowMeshIndex, currentLod.TerrainShadowMeshIndex + currentLod.TerrainShadowMeshCount));
	ranges.push_back(std::pair<int, int>(currentLod.VerticalFogMeshIndex, currentLod.VerticalFogMeshIndex + currentLod.VerticalFogMeshCount));

	if (File->ExtraLodEnabled) {
		MdlStructs::ExtraLodStruct extraLod = File->ExtraLods[(int)Lod];
		ranges.push_back(std::pair<int, int>(extraLod.LightShaftMeshIndex, extraLod.LightShaftMeshIndex + extraLod.LightShaftMeshCount));
		ranges.push_back(std::pair<int, int>(extraLod.GlassMeshIndex, extraLod.GlassMeshIndex + extraLod.GlassMeshCount));
		ranges.push_back(std::pair<int, int>(extraLod.MaterialChangeMeshIndex, extraLod.MaterialChangeMeshIndex + extraLod.MaterialChangeMeshCount));
		ranges.push_back(std::pair<int, int>(extraLod.CrestChangeMeshIndex, extraLod.CrestChangeMeshIndex + extraLod.CrestChangeMeshCount));
	}

	int totalMeshes = 0;
	bool atIndex = true;
	while (atIndex) {
		atIndex = false;
		for (int i = 0; i < ranges.size(); i++) {
			std::pair<int, int> pair = ranges.at(i);
			int s = pair.first;
			int e = pair.second;

			if (s <= totalMeshes && totalMeshes < e) {
				atIndex = true;
				totalMeshes++;
				break;
			}
		}
	}

	Meshes = std::vector<Mesh>();
	for (int i = 0; i < totalMeshes;  i++) {
		std::vector<Mesh>::iterator it = Meshes.begin();
		Meshes.insert(it, i + 1, Mesh(this, i, GetMeshTypes(i)));
	}
}
std::list<Mesh::MeshType> Model::GetMeshTypes(int index) {
	std::list<Mesh::MeshType> types;

	if (index >= File->Lods[(int)Lod].MeshIndex &&
		index < File->Lods[(int)Lod].MeshIndex + File->Lods[(int)Lod].MeshCount &&
		File->Lods[(int)Lod].MeshCount > 0)
		types.push_back(Mesh::MeshType::Main);
	if (index >= File->Lods[(int)Lod].WaterMeshIndex &&
		index < File->Lods[(int)Lod].WaterMeshIndex + File->Lods[(int)Lod].WaterMeshCount &&
		File->Lods[(int)Lod].WaterMeshCount > 0)
		types.push_back(Mesh::MeshType::Water);
	if (index >= File->Lods[(int)Lod].ShadowMeshIndex &&
		index < File->Lods[(int)Lod].ShadowMeshIndex + File->Lods[(int)Lod].ShadowMeshCount &&
		File->Lods[(int)Lod].ShadowMeshCount > 0)
		types.push_back(Mesh::MeshType::Shadow);
	if (index >= File->Lods[(int)Lod].TerrainShadowMeshIndex &&
		index < File->Lods[(int)Lod].TerrainShadowMeshIndex + File->Lods[(int)Lod].TerrainShadowMeshCount &&
		File->Lods[(int)Lod].TerrainShadowMeshCount > 0)
		types.push_back(Mesh::MeshType::TerrainShadow);
	if (index >= File->Lods[(int)Lod].VerticalFogMeshIndex &&
		index < File->Lods[(int)Lod].VerticalFogMeshIndex + File->Lods[(int)Lod].VerticalFogMeshCount &&
		File->Lods[(int)Lod].VerticalFogMeshCount > 0)
		types.push_back(Mesh::MeshType::VerticalFog);

	if (!File->ExtraLodEnabled) return types;

	if (index >= File->ExtraLods[(int)Lod].LightShaftMeshIndex &&
		index < File->ExtraLods[(int)Lod].LightShaftMeshIndex + File->ExtraLods[(int)Lod].LightShaftMeshCount &&
		File->ExtraLods[(int)Lod].LightShaftMeshCount > 0)
		types.push_back(Mesh::MeshType::LightShaft);
	if (index >= File->ExtraLods[(int)Lod].GlassMeshIndex &&
		index < File->ExtraLods[(int)Lod].GlassMeshIndex + File->ExtraLods[(int)Lod].GlassMeshCount &&
		File->ExtraLods[(int)Lod].GlassMeshCount > 0)
		types.push_back(Mesh::MeshType::Glass);
	if (index >= File->ExtraLods[(int)Lod].MaterialChangeMeshIndex &&
		index < File->ExtraLods[(int)Lod].MaterialChangeMeshIndex + File->ExtraLods[(int)Lod].MaterialChangeMeshCount &&
		File->ExtraLods[(int)Lod].MaterialChangeMeshCount > 0)
		types.push_back(Mesh::MeshType::MaterialChange);
	if (index >= File->ExtraLods[(int)Lod].CrestChangeMeshIndex &&
		index < File->ExtraLods[(int)Lod].CrestChangeMeshIndex + File->ExtraLods[(int)Lod].CrestChangeMeshCount &&
		File->ExtraLods[(int)Lod].CrestChangeMeshCount > 0)
		types.push_back(Mesh::MeshType::CrestChange);

	return types;
}
