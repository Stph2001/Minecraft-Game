#pragma once

#ifndef _VBO_
#define _VBO_

class VBO {
	GLuint id;
public:
	inline VBO(GLsizeiptr size, const void* data) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}
	inline ~VBO() { glDeleteBuffers(1, &id); }

	inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }
	inline void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};

#endif