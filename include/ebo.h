#pragma once

#ifndef _EBO_
#define _EBO_

class EBO {
	GLuint id;
public:
	inline EBO(GLsizeiptr size, const void* data) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}
	inline ~EBO() { glDeleteBuffers(1, &id); }

	inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
	inline void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};

#endif