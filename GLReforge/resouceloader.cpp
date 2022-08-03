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


GLboolean resouceloader::load_mesh(const std::string& path, mesh* object) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << "Failed to load the mesh \" " << path << " \" " << importer.GetErrorString() << std::endl;
		return GL_FALSE;
	}

	object->create_geometry_buffer();
	std::vector<vertex> buffer;
	std::vector<GLuint> indices;

	/* the object contain one mesh for now */
	// std::cout << "meshes = " << scene->mNumMeshes << std::endl;
	const aiMesh* paiMesh = scene->mMeshes[0];
	for (GLuint i = 0; i < paiMesh->mNumVertices; ++i) {
		/* am taking only pos for now */
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		buffer.push_back(vertex(pPos->x, pPos->y, pPos->z));
	}


	for (GLuint i = 0; i < paiMesh->mNumFaces; ++i) {
		const aiFace& Face = paiMesh->mFaces[i];
		//assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	object->glmemcpy(buffer, indices);
	return GL_TRUE;
}