#pragma once

#ifndef _EBO_
#define _EBO_

class EBO {
	GLuint id;
public:
	EBO(GLsizeiptr size, const void* data) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}
	~EBO() { glDeleteBuffers(1, &id); }

	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};

#endif