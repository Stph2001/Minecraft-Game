#pragma once

#ifndef _TEXTURE_
#define _TEXTURE_

class Texture {
	GLuint id;
	u32 slot;

	Path* path;
public:
	std::string type;
public:
	Texture(
		u32 slot,
		std::string texturesPath = "resources/textures",
		std::string textureFileName = "box.jpg",
		std::string textureType = "diffuse",
		GLenum colorFormat = GL_RGB,
		GLenum textureFilter = GL_LINEAR,
		GLenum wrapU = GL_REPEAT,
		GLenum wrapV = GL_REPEAT
	) : slot(slot),
		type(textureType),
		path(new Path("resources/shaders", texturesPath)) {
		std::string filePath = path->texture(textureFileName);

		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0 + slot);
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapU);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapV);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilter);
		i32 width, height, nrChannels;

		stbi_set_flip_vertically_on_load(true);
		u8* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
		if (data != nullptr) {
			glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
			std::cerr << "Can't load texture\n";
		stbi_image_free(data);

		Unbind();
	}
	~Texture() { glDeleteTextures(1, &id); }

	void Bind() {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	void setUniform2D(Shader& shader, const i8* name, const i32& i) {
		shader.useProgram();
		shader.setI32(name, i);
	}
};

#endif