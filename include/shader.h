#pragma once

#ifndef _SHADER_
#define _SHADER_

class Shader {
	GLuint id;
	Path* path;

	i32 ok;          // check for error status
	i8 infoLog[512]; // get error status info

public:
	Shader(
		std::string shadersPath = "resources/shaders",
		std::string vertexFileName = "shader.vert",
		std::string fragmentFileName = "shader.frag"
	) : path(new Path(shadersPath, "resources/textures")) {

		std::ifstream vertexFile(path->shader(vertexFileName));
		std::string vertexSrc;
		std::getline(vertexFile, vertexSrc, '\0');

		std::ifstream fragmentFile(path->shader(fragmentFileName));
		std::string fragmentSrc;
		std::getline(fragmentFile, fragmentSrc, '\0');

		u32 vertex = makeShader(vertexSrc.c_str(), GL_VERTEX_SHADER);
		u32 fragment = makeShader(fragmentSrc.c_str(), GL_FRAGMENT_SHADER);

		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &ok);
		if (!ok) {
			glGetProgramInfoLog(id, 512, nullptr, infoLog);
			std::cout << "Error::shader::program::link_failed\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	~Shader() {
		glDeleteProgram(id);
		glfwTerminate();
	}

	void useProgram() { glUseProgram(id); }
	GLuint getProgram() { return id; }

	// Set uniforms
	void setI32(const i8* name, const i32& i) const {
		glUniform1i(glGetUniformLocation(id, name), i);
	}
	void setVec3(const i8* name, glm::vec3 vector) const {
		glUniform3f(glGetUniformLocation(id, name), vector.x, vector.y, vector.z);
	}
	void setMat4(const i8* name, const glm::mat4& mat) const {
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
	}
	void setF32(const i8* name, const f32 value) const {
		glUniform1f(glGetUniformLocation(id, name), value);
	}

	// Get uniform location
	u32 getLocation(const i8* name) { return glGetUniformLocation(id, name); }

private:
	u32 makeShader(const i8* source, GLenum type) {
		u32 shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
		if (!ok) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "Error::shader::compilation_failed\n" << infoLog << std::endl;
			return 0;
		}
		return shader;
	}
};

#endif