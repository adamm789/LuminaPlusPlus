#include "MtrlFile.h"
#include "../Parsing/MtrlStructs.h"

#include <string>
#include <fstream>

void MtrlFile::LoadFromFile(std::string filePath) {
	std::ifstream ifs;
	try {
		ifs.open(filePath, std::ios::in | std::ios::binary);

		ifs.read((char*) & FileHeader, sizeof(MtrlStructs::MaterialFileHeader));
	}
	catch (int e) {
		fprintf(stderr, "An exception has occurred: %i\n", e);
		fprintf(stderr, "Material file: \"%s\" could not be read.\n", filePath.c_str());
	}
}