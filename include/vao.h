#pragma once

#ifndef _VAO_
#define _VAO_

#include <vbo.h>

class VAO {
	GLuint id;
public:
	inline VAO() { glGenVertexArrays(1, &id); }
	inline ~VAO() { glDeleteVertexArrays(1, &id); }

	inline void SetVertexAttribPointer(VBO& vbo, u32 location, u32 offset, u32 stride, u32 starting_point) {
		vbo.Bind();
		glVertexAttribPointer(location, offset, GL_FLOAT, GL_FALSE, stride, (void*)starting_point);
		glEnableVertexAttribArray(location);
		vbo.Unbind();
	}

	inline void Bind() { glBindVertexArray(id); }
	inline void Unbind() { glBindVertexArray(0); }
};

#endif