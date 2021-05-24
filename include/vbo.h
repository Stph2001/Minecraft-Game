#pragma once

#ifndef _VBO_
#define _VBO_

class VBO {
	GLuint id;
public:
	VBO(GLsizeiptr size, const void* data) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}
	~VBO() { glDeleteBuffers(1, &id); }

	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};

#endif