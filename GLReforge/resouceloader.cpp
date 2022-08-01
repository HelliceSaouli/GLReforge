#include "resouceloader.h"

std::string resouceloader::load_shader_source(const std::string& path) {

	std::string  source;

	std::ifstream file;
	file.open((path).c_str());
	std::string line;

	if (!file.is_open())
	{
		std::cerr << " Enable to load shader: " << path << "...!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (file.good())
	{
		getline(file, line);
		source.append(line + "\n");
	}

	file.close();
	return source;
}