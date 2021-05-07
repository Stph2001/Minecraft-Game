#pragma once

#ifndef _VAO_
#define _VAO_

#include <glad/glad.h>

class VAO {
	GLuint id;
public:
	VAO() {
		glGenVertexArrays(1, &id);
		Bind();
	}
	~VAO() { glDeleteVertexArrays(1, &id); }

	void SetVertexAttribPointer(unsigned int location, unsigned int offset, unsigned int stride, unsigned int starting_point) {
		glVertexAttribPointer(location, offset, GL_FLOAT, GL_FALSE, stride, (void*)starting_point);
		glEnableVertexAttribArray(location);
	}

	void Bind() { glBindVertexArray(id); }
	void Unbind() { glBindVertexArray(0); }
};

#endif