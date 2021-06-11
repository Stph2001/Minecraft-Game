#pragma once

#ifndef _CUBE_BASE_
#define _CUBE_BASE_

#include <glutil.h>

// Improved base mesh class (UNCOMPLETE)
// ------ IGNORE THIS FOR NOW... ------
/*
static const Vertex verticesSprite[] = {
	// Face 1
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Face 2
	{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) }
};
static const Vertex verticesHexahedron[] = {
	// Top
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Bottom
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Front
	{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Back
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Left
	{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Right
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) }
};
static const Vertex verticesStairs[] = {
	// Top Top
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.5f) },
	{ glm::vec3( 0.5f,  0.5f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	// Top Bottom
	{ glm::vec3( 0.5f,  0.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	{ glm::vec3(-0.5f,  0.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.5f) },
	{ glm::vec3(-0.5f,  0.0f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f,  0.0f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Bottom
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Front Front
	{ glm::vec3( 0.5f,  0.0f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	{ glm::vec3(-0.5f,  0.0f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.5f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Front Back
	{ glm::vec3( 0.5f,  0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.5f) },
	{ glm::vec3( 0.5f,  0.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	// Back
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	// Left
	{ glm::vec3(-0.5f,  0.5f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.5f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(-0.5f,  0.0f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	{ glm::vec3(-0.5f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.5f, 0.5f) },
	// Right
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.5f, 1.0f) },
	{ glm::vec3( 0.5f,  0.5f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3( 0.5f,  0.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3( 0.5f,  0.0f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.0f) },
	{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(1.0f, 0.5f) },
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(1.0f), glm::vec2(0.5f, 0.5f) }
};

static const u32 indicesSprite[] = {
	0, 1, 2,   0, 2, 3,  // Face 1
	4, 5, 6,   4, 6, 7   // Face 2
};
static const u32 indicesHexahedron[] = {
	  0,  1,  2,    0,  2,  3,  // Top
	  4,  5,  6,    4,  6,  7,  // Bottom
	  8,  9, 10,    8, 10, 11,  // Front
	 12, 13, 14,   12, 14, 15,  // Back
	 16, 17, 18,   16, 18, 19,  // Left
	 20, 21, 22,   20, 22, 23   // Right
};
static const u32 indicesStairs[] = {
	 0,  1,  2,    0,  2,  3,  // Top Top
	 4,  5,  6,    4,  6,  7,  // Top Bottom
	 8,  9, 10,    8, 10, 11,  // Bottom
	12, 13, 14,   12, 14, 15,  // Front Front
	16, 17, 18,   16, 18, 19,  // Front Back
	20, 21, 22,   20, 22, 23,  // Back
	24, 25, 26,   24, 26, 27,  // Left
	28, 29, 30,   28, 30, 31   // Right
};

class BlockMesh {
	BlockMeshType mesh_type;

	VAO vao;

	Vertex* vertices;
	u32* indices;

	u32 vrtSize;
	u32 idxSize;
public:
	glm::vec3 position;
public:
	BlockMesh(
		BlockID id,
		glm::vec3 position,
		f32 uv_scale,
		u32 tile = 0) : position(position) {

		switch (id) {
		case BlockID::DANDELION:
		case BlockID::POPPY:
			mesh_type = BlockMeshType::SPRITE;  break;
		case BlockID::LAVA:
		case BlockID::WATER:
			mesh_type = BlockMeshType::FLUID;   break;
		default:
			mesh_type = BlockMeshType::DEFAULT; break;
		}

		switch (mesh_type) {
		case BlockMeshType::SPRITE:
			vertices = const_cast<Vertex*>(verticesSprite);
			indices  = const_cast<u32*>(indicesSprite); break;
		default:
			vertices = const_cast<Vertex*>(verticesHexahedron);
			indices = const_cast<u32*>(indicesHexahedron);
		}

		vrtSize = sizeof(vertices) / sizeof(Vertex);
		idxSize = sizeof(indices) / sizeof(u32);

		VBO vbo(sizeof(vertices), vertices);
		vao.SetVertexAttribPointer(vbo, 0, 3, 11 * FSIZE, 0);
		vao.SetVertexAttribPointer(vbo, 1, 3, 11 * FSIZE, 3 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 2, 3, 11 * FSIZE, 6 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 3, 2, 11 * FSIZE, 9 * FSIZE);

		vao.Unbind();
		vbo.Unbind();

		u32 numTiles = 1 / uv_scale;
		u32 y = tile / numTiles;
		u32 x = tile - numTiles * y;
		glm::vec2 tile_pos(x, y);

		// UV coordinates assignation is not yet available for:
		//    - Slabs
		//    - Stairs
		switch (mesh_type) {
		case BlockMeshType::DEFAULT:
		case BlockMeshType::FLUID:
		case BlockMeshType::SLAB:
			for (u32 i = 0; i < vrtSize / 4; i++) {
				vertices[4 * i + 0].uvCoords = glm::vec2(uv_scale * (1 + tile_pos.x), 1 - uv_scale *      tile_pos.y);
				vertices[4 * i + 1].uvCoords = glm::vec2(uv_scale *      tile_pos.x , 1 - uv_scale *      tile_pos.y);
				vertices[4 * i + 2].uvCoords = glm::vec2(uv_scale *      tile_pos.x , 1 - uv_scale * (1 + tile_pos.y));
				vertices[4 * i + 3].uvCoords = glm::vec2(uv_scale * (1 + tile_pos.x), 1 - uv_scale * (1 + tile_pos.y));
			}
			break;
		default: break;
		}
	}
	BlockMesh(
		BlockID id,
		glm::vec3 position,
		f32 uv_scale,
		std::vector<u32> tile_set = {
			0,  // Top
			2,  // Bottom
			1,  // Front
			1,  // Back
			1,  // Left
			1   // Right
		}) : position(position) {

	}
	~BlockMesh() { delete[] vertices, indices; }

	glm::mat4 getModel() { return glm::translate(glm::mat4(1.0f), position); }

	void Render(Shader& shader, Texture& texture, Camera camera, f32 aspect_ratio) {
		vao.Bind();
		vbo.Bind();
		ebo.Bind();

		texture.Bind();
		texture.setUniform2D(shader, "atlas", 0);

		shader.useProgram();
		shader.setMat4("projection", glm::perspective(camera.getFovAngle(), aspect_ratio, camera.zNear, camera.zFar));
		shader.setMat4("view", camera.getView());
		shader.setMat4("model", getModel());

		glDrawElements(GL_TRIANGLES, idxSize, GL_UNSIGNED_INT, 0);

		texture.Unbind();
		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}
};
*/

//
class Cube {
	glm::vec3 position;

	f32* vertices;
	u32* indices;

	VAO vao;

	u32 vSize, iSize;
public:
	Cube(
		glm::vec3 position = glm::vec3(0.0f),
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
		position(position),
		vertices(new f32[11 * 24]), indices(new u32[6 * 6]) {
		glm::vec3 half = glm::vec3(0.5f);

		std::vector<glm::vec2> tiles;
		for (u32 i = 0; i < 6; i++) {
			u32 numTiles = 1 / uv_scale;
			u32 y = tile_id[i] / numTiles;
			u32 x = tile_id[i] - numTiles * y;
			tiles.push_back(glm::vec2(x, y));
		}

		f32 vTemp[] = {
			// Top
			 half.x,  half.y, -half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * (1 + tiles[0].x), 1 - uv_scale * tiles[0].y,   //  0
			-half.x,  half.y, -half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * tiles[0].x,  1 - uv_scale * tiles[0].y,   //  1
			-half.x,  half.y,  half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * tiles[0].x,  1 - uv_scale * (1 + tiles[0].y),  //  2
			 half.x,  half.y,  half.z,   1.0f, 1.0f, 1.0f,    0.0f,  1.0f,  0.0f,   uv_scale * (1 + tiles[0].x), 1 - uv_scale * (1 + tiles[0].y),  //  3
			// Bottom
			 half.x, -half.y,  half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * (1 + tiles[1].x), 1 - uv_scale * tiles[1].y,   //  4
			-half.x, -half.y,  half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * tiles[1].x,  1 - uv_scale * tiles[1].y,   //  5
			-half.x, -half.y, -half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * tiles[1].x,  1 - uv_scale * (1 + tiles[1].y),  //  6
			 half.x, -half.y, -half.z,   1.0f, 1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   uv_scale * (1 + tiles[1].x), 1 - uv_scale * (1 + tiles[1].y),  //  7
			// Front
			 half.x,  half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * (1 + tiles[2].x), 1 - uv_scale * tiles[2].y,   //  8
			-half.x,  half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * tiles[2].x,  1 - uv_scale * tiles[2].y,   //  9
			-half.x, -half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * tiles[2].x,  1 - uv_scale * (1 + tiles[2].y),  // 10
			 half.x, -half.y,  half.z,   1.0f, 0.0f, 0.0f,    0.0f,  0.0f,  1.0f,   uv_scale * (1 + tiles[2].x), 1 - uv_scale * (1 + tiles[2].y),  // 11
			// Back
			-half.x,  half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * (1 + tiles[3].x), 1 - uv_scale * tiles[3].y,   // 12
			 half.x,  half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * tiles[3].x,  1 - uv_scale * tiles[3].y,   // 13
			 half.x, -half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * tiles[3].x,  1 - uv_scale * (1 + tiles[3].y),  // 14
			-half.x, -half.y, -half.z,   1.0f, 0.5f, 0.0f,    0.0f,  0.0f, -1.0f,   uv_scale * (1 + tiles[3].x), 1 - uv_scale * (1 + tiles[3].y),  // 15
			// Left
			-half.x,  half.y,  half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[4].x), 1 - uv_scale * tiles[4].y,   // 16
			-half.x,  half.y, -half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * tiles[4].x,  1 - uv_scale * tiles[4].y,   // 17
			-half.x, -half.y, -half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * tiles[4].x,  1 - uv_scale * (1 + tiles[4].y),  // 18
			-half.x, -half.y,  half.z,   0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[4].x), 1 - uv_scale * (1 + tiles[4].y),  // 19
			// Right
			 half.x,  half.y, -half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale * (1 + tiles[5].x), 1 - uv_scale * tiles[5].y,   // 20
			 half.x,  half.y,  half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale * tiles[5].x,  1 - uv_scale * tiles[5].y,   // 21
			 half.x, -half.y,  half.z,   0.0f, 0.0f, 1.0f,    1.0f,  0.0f,  0.0f,   uv_scale * tiles[5].x,  1 - uv_scale * (1 + tiles[5].y),  // 22
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
		iSize = 6 * 6;

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

	void Render(Shader& shader, Texture& texture, Camera camera, f32 aspect_ratio, bool top, bool bottom, bool front, bool back, bool left, bool right) {
		// Important! Build new arrays for vertices and indices based on the face booleans
		u32 rendered_faces = 0;

		bool faces[] = { top, bottom, front, back, left, right };
		for (bool face : faces) if (face) rendered_faces++;

		i32 vTempSize = rendered_faces * 4 * 11;
		i32 iTempSize = rendered_faces * 1 * 6;

		f32* vTemp = new f32[vTempSize];
		u32* iTemp = new u32[iTempSize];

		u32 vtx = 0;
		for (u32 i = 0; i < rendered_faces; i++) {
			while (true) {
				if (faces[vtx]) break;
				vtx++;
			}
			for (u32 j = 0; j < 44; j++)
				vTemp[i * 44 + j] = vertices[vtx * 44 + j];
			vtx++;
		}

		for (u32 i = 0; i < rendered_faces * 6; i++)
			iTemp[i] = indices[i];

		VBO vbo(vTempSize * FSIZE, vTemp);
		EBO ebo(iTempSize * ISIZE, iTemp);

		vao.Bind();
		vbo.Bind();
		ebo.Bind();

		vao.SetVertexAttribPointer(vbo, 0, 3, 11 * FSIZE, 0);
		vao.SetVertexAttribPointer(vbo, 1, 3, 11 * FSIZE, 3 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 2, 3, 11 * FSIZE, 6 * FSIZE);
		vao.SetVertexAttribPointer(vbo, 3, 2, 11 * FSIZE, 9 * FSIZE);

		texture.Bind();
		texture.setUniform2D(shader, "atlas", 0);

		shader.useProgram();
		shader.setMat4("projection", glm::perspective(camera.getFovAngle(), aspect_ratio, camera.zNear, camera.zFar));
		shader.setMat4("view", camera.getView());
		shader.setMat4("model", getModel());

		glDrawElements(GL_TRIANGLES, iTempSize, GL_UNSIGNED_INT, 0);

		texture.Unbind();
		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}
};

#endif