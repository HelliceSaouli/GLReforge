#include "resouceloader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
		/* am taking only pos and u vfor now */
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : 
																					new aiVector3D(0.0f, 0.0f, 0.0f);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);

		buffer.push_back(vertex(vec3(pPos->x, pPos->y, pPos->z), 
							    vec3(pTexCoord->x, pTexCoord->y, 0.0f),
								vec3(pNormal->x, pNormal->y, pNormal->z)));
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

GLubyte* resouceloader::load_texture(const std::string& path, GLint* width, GLint* Heigh) {
	GLint nrChannels; // I don't need this now
	stbi_set_flip_vertically_on_load(1); /* since opengl use images from buttom to top*/
	return stbi_load(path.c_str(), width, Heigh, &nrChannels, 0); /* mybe i  should cast this ?? */
}

void resouceloader::free_texture_data(GLubyte* data) {
	stbi_image_free(data);
}