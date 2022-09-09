#include "texture.h"
#include "resouceloader.h"

#include <iostream>
texture::texture(GLenum target, const std::string& _image_name) {
	texture_target = target;
	image_name = _image_name;
}

texture::~texture() {

}
/* TODO : call this load_texture2D and support mulitple texture target */
GLboolean texture::load_texture() {
	GLint width; 
	GLint heigh;
	GLint nrChannels;
	GLubyte* image_data = resouceloader::load_texture(image_name, &width, &heigh, &nrChannels);

	if (image_data == nullptr) {
		std::cout << " Failed to load the current texture image \" " << image_name <<"\" "<< std::endl;
		return GL_FALSE;
	}
	glGenTextures(1, &texture_object);
	glBindTexture(texture_target, texture_object);
	if (texture_target == GL_TEXTURE_2D) {
		/* Gamma correction */
		if (nrChannels == 1) {
			glTexImage2D(texture_target, 0, GL_RED, width, heigh, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
		}
		else if (nrChannels == 3) {
			glTexImage2D(texture_target, 0, GL_SRGB, width, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		}
		else if(nrChannels == 4){

			glTexImage2D(texture_target, 0, GL_SRGB_ALPHA, width, heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		}
		
	}
	else{
		std::cout << " Support for target texture " << texture_target << "is not implemented yet" << std::endl;
		return GL_FALSE;
	}

	if (nrChannels == 4) {
		glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}
	else {
		glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindTexture(texture_target, 0);
	resouceloader::free_texture_data(image_data);

	return GL_TRUE;
}

GLboolean texture::load_normal_maps() {
	GLint width;
	GLint heigh;
	GLint nrChannels;
	GLubyte* image_data = resouceloader::load_texture(image_name, &width, &heigh, &nrChannels);

	if (image_data == nullptr) {
		std::cout << " Failed to load the current texture image \" " << image_name << "\" " << std::endl;
		return GL_FALSE;
	}
	glGenTextures(1, &texture_object);
	glBindTexture(texture_target, texture_object);
	if (texture_target == GL_TEXTURE_2D) {
		glTexImage2D(texture_target, 0, GL_RGB, width, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	}
	else {
		std::cout << " Support for target texture " << texture_target << "is not implemented yet" << std::endl;
		return GL_FALSE;
	}


	glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindTexture(texture_target, 0);
	resouceloader::free_texture_data(image_data);

	return GL_TRUE;
}

void texture::use_texture(GLenum texture_unit) {
	glActiveTexture(texture_unit);
	glBindTexture(texture_target, texture_object);
}