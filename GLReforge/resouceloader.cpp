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


GLboolean resouceloader::load_static_model(const std::string& path, staticmodel* model) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << "Failed to load the mesh \" " << path << " \" " << importer.GetErrorString() << std::endl;
		return GL_FALSE;
	}
	model->init_model(scene->mNumMeshes, scene->mNumMaterials);
	if (model == NULL) {
		std::cout << " model pointer is null something is wrong" << std::endl;
		return GL_FALSE;
	}
	for (GLuint index = 0; index < scene->mNumMeshes; index++) {
		const aiMesh* paiMesh = scene->mMeshes[index];

		std::vector<vertex> buffer;
		std::vector<GLuint> indices;
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

		// object->glmemcpy(buffer, indices);
		model->add_mesh(paiMesh->mMaterialIndex, buffer, indices, index);
	}

	/* texture diractory setup */
	std::string diractory;
	std::string::size_type slashindex = path.find_last_of("/");
	if (slashindex == std::string::npos) {
		diractory = ".";
	}
	else if (slashindex == 0) {
		diractory = "/";
	}
	else {
		diractory = path.substr(0, slashindex);
	}

	for (GLuint index = 0; index < scene->mNumMaterials; index++) {
		const aiMaterial* pMaterial = scene->mMaterials[index];
		
		//fill the albedo texture, assuming each material has one albedo texture
		if (pMaterial->GetTextureCount(aiTextureType_BASE_COLOR) > 0) {
			aiString texturepath;
			if (pMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &texturepath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullpath = diractory + "/" + texturepath.data;
				model->set_albedo_texture(fullpath, index);
			}
		}
	}
	return GL_TRUE;
}

GLubyte* resouceloader::load_texture(const std::string& path, GLint* width, GLint* Heigh, GLint* nrChannels) {
	stbi_set_flip_vertically_on_load(1); /* since opengl use images from buttom to top*/
	return stbi_load(path.c_str(), width, Heigh, nrChannels, 0); /* mybe i  should cast this ?? */
}

void resouceloader::free_texture_data(GLubyte* data) {
	stbi_image_free(data);
}