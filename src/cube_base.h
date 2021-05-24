#pragma once

#ifndef _CUBE_BASE_
#define _CUBE_BASE_

class Cube {
	glm::vec3 scale;
	glm::vec3 position;

	f32* vertices;
	u32* indices;

	VAO vao;

	u32 vSize, iSize;
public:
	Cube(
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		f32 uv_scale = 0.25f,
		std::vector<u32> tile_id = {
			0,  // Top tile
			0,  // Bottom tile
			0,  // Front tile
			0,  // Back tile
			0,  // Left tile
			0   // Right tile
		}
	) :
		scale(scale),
		position(position),
		vertices(new f32[11 * 24]), indices(new u32[6 * 6]) {
		glm::vec3 half = scale * 0.5f;

		std::vector<glm::vec2> tiles;
		for (u32 i = 0; i < 6; i++) {
			u32 numTiles = 1 / uv_scale;
			u32 y = tile_id[i] / numTiles;
			u32 x = tile_id[i] - numTiles * y;
			tiles.push_back(glm::vec2(x, y));
		}

		f32 vTemp[] = {
			// Top
			 half.x,  half.y, -half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * (1 + tiles[0].x), 1 - uv_scale *      tiles[0].y,   //  0
			-half.x,  half.y, -half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale *      tiles[0].x,  1 - uv_scale *      tiles[0].y,   //  1
			-half.x,  half.y,  half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale *      tiles[0].x,  1 - uv_scale * (1 + tiles[0].y),  //  2
			 half.x,  half.y,  half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * (1 + tiles[0].x), 1 - uv_scale * (1 + tiles[0].y),  //  3
			// Bottom
			 half.x, -half.y,  half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * (1 + tiles[1].x), 1 - uv_scale *      tiles[1].y,   //  4
			-half.x, -half.y,  half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale *      tiles[1].x,  1 - uv_scale *      tiles[1].y,   //  5
			-half.x, -half.y, -half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale *      tiles[1].x,  1 - uv_scale * (1 + tiles[1].y),  //  6
			 half.x, -half.y, -half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * (1 + tiles[1].x), 1 - uv_scale * (1 + tiles[1].y),  //  7
			// Front
			 half.x,  half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * (1 + tiles[2].x), 1 - uv_scale *      tiles[2].y,   //  8
			-half.x,  half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale *      tiles[2].x,  1 - uv_scale *      tiles[2].y,   //  9
			-half.x, -half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale *      tiles[2].x,  1 - uv_scale * (1 + tiles[2].y),  // 10
			 half.x, -half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * (1 + tiles[2].x), 1 - uv_scale * (1 + tiles[2].y),  // 11
			// Back
			-half.x,  half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * (1 + tiles[3].x), 1 - uv_scale *      tiles[3].y,   // 12
			 half.x,  half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale *      tiles[3].x,  1 - uv_scale *      tiles[3].y,   // 13
			 half.x, -half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale *      tiles[3].x,  1 - uv_scale * (1 + tiles[3].y),  // 14
			-half.x, -half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * (1 + tiles[3].x), 1 - uv_scale * (1 + tiles[3].y),  // 15
			// Left
			-half.x,  half.y,  half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[4].x), 1 - uv_scale *      tiles[4].y,   // 16
			-half.x,  half.y, -half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale *      tiles[4].x,  1 - uv_scale *      tiles[4].y,   // 17
			-half.x, -half.y, -half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale *      tiles[4].x,  1 - uv_scale * (1 + tiles[4].y),  // 18
			-half.x, -half.y,  half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[4].x), 1 - uv_scale * (1 + tiles[4].y),  // 19
			// Right
			 half.x,  half.y, -half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[5].x), 1 - uv_scale *      tiles[5].y,   // 20
			 half.x,  half.y,  half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale *      tiles[5].x,  1 - uv_scale *      tiles[5].y,   // 21
			 half.x, -half.y,  half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale *      tiles[5].x,  1 - uv_scale * (1 + tiles[5].y),  // 22
			 half.x, -half.y, -half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[5].x), 1 - uv_scale * (1 + tiles[5].y),  // 23
		};
		u32 iTemp[] = {
			 0,  1,  2,    0,  2,  3,  // Top
			 4,  5,  6,    4,  6,  7,  // Bottom
			 8,  9, 10,    8, 10, 11,  // Front
			12, 13, 14,   12, 14, 15,  // Back
			16, 17, 18,   16, 18, 19,  // Left
			20, 21, 22,   20, 22, 23   // Right
		};
		vSize = 24 * 11;
		iSize =  6 *  6;

		for (u32 i = 0; i < vSize; i++)
			vertices[i] = vTemp[i];
		for (u32 i = 0; i < iSize; i++)
			indices[i] = iTemp[i];

		VBO vbo(vSize * FSIZE, vertices);

		vao.Bind();
		vbo.Bind();

		vao.SetVertexAttribPointer(vbo, 0, 3, 11 * FSIZE, 0);
		vao.SetVertexAttribPointer(vbo, 1, 3, 11 * FSIZE, 3 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 2, 3, 11 * FSIZE, 6 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 3, 2, 11 * FSIZE, 9 * FSIZE);

		vao.Unbind();
		vbo.Unbind();

	}
	~Cube() { delete[] vertices, indices; }

	f32* getVertices() { return vertices; }
	u32* getIndices() { return indices; }

	u32 getVSize() { return vSize; }
	u32 getISize() { return iSize; }

	glm::mat4 getModel() { return glm::translate(glm::mat4(1.0f), position); }

	glm::vec3 getPosition() { return position; }
		
	void Render(Shader& shader, Texture& texture, Camera camera, f32 aspect_ratio) {
		VBO vbo(vSize * FSIZE, vertices);
		EBO ebo(iSize * ISIZE, indices);
		
		vao.Bind();
		vbo.Bind();
		ebo.Bind();

		texture.Bind();
		texture.setUniform2D(shader, "atlas", 0);

		shader.useProgram();
		shader.setMat4("projection", glm::perspective(camera.getFovAngle(), aspect_ratio, camera.zNear, camera.zFar));
		shader.setMat4("view", camera.getView());
		shader.setMat4("model", getModel());

		glDrawElements(GL_TRIANGLES, iSize, GL_UNSIGNED_INT, 0);
		
		texture.Unbind();
		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}
};

#endif