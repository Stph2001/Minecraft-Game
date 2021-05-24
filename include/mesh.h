#pragma once

#ifndef _MESH_
#define _MESH_

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 uvCoords;
};

class Mesh {
	glm::mat4 model;

	void UpdateModelMatrix() {
		glm::mat4 temp = glm::mat4(1.0f);
		temp = glm::translate(temp, position);
		temp = glm::rotate(temp, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		temp = glm::rotate(temp, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		temp = glm::rotate(temp, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		temp = glm::scale(temp, scale);

		model = temp;
	}

public:
	std::vector<Vertex> vertices;
	std::vector<u32> indices;
	std::vector<Texture> textures;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	VAO vao;

	Mesh(
		glm::vec3 initial_position,
		glm::vec3 initial_rotation,
		glm::vec3 initial_scale,
		std::vector<Vertex>& vertices,
		std::vector<u32>& indices,
		std::vector<Texture>& textures
	) : position(initial_position), rotation(initial_rotation), scale(initial_scale),
		vertices(vertices), indices(indices), textures(textures),
		model(glm::mat4(1.0f)) {
		
		VBO vbo(vertices.size() * sizeof(Vertex), vertices.data());
		EBO ebo(indices.size() * sizeof(u32), indices.data());

		vao.SetVertexAttribPointer(vbo, 0, 3, sizeof(Vertex), 0);                // Positions
		vao.SetVertexAttribPointer(vbo, 1, 3, sizeof(Vertex), 3 * sizeof(f32));  // Normals
		vao.SetVertexAttribPointer(vbo, 2, 3, sizeof(Vertex), 6 * sizeof(f32));  // Colors
		vao.SetVertexAttribPointer(vbo, 3, 2, sizeof(Vertex), 9 * sizeof(f32));  // UVs

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}

	void Draw(Shader& shader, Camera& camera, glm::mat4 projection) {
		shader.useProgram();
		vao.Bind();

		u32 DiffuseCount = 0;
		u32 SpecularCount = 0;

		for (u32 i = 0; i < textures.size(); i++) {
			std::string num;
			std::string type = textures[i].type;

			if (type == "diffuse")
				num = std::to_string(DiffuseCount++);
			else if (type == "specular")
				num = std::to_string(SpecularCount++);
			textures[i].setUniform2D(shader, (type + num).c_str(), i);
			textures[i].Bind();
		}

		// shader.setVec3("camPos", camera.position);
		shader.setMat4("view", camera.getView());
		shader.setMat4("projection", projection);
		shader.setMat4("model", model);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		UpdateModelMatrix();
	}

	void Translate(glm::vec3 v) {
		position += v;

		UpdateModelMatrix();
	}
	void Rotate(glm::vec3 v) {
		rotation += v;

		UpdateModelMatrix();
	}
	void Scale(glm::vec3 v) {
		scale *= v;

		UpdateModelMatrix();
	}
};

#endif