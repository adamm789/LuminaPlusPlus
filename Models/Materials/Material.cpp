#include "Material.h"
#include "../Models/Model.h"

Material::Material() {

}

Material::Material(Model* parent, std::string path, int variantId) {
	Parent = parent;
	MaterialPath = path;
	VariantId = variantId;
}
