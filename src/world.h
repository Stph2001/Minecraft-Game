#pragma once

#ifndef _MC_WORLD_
#define _MC_WORLD_

#include "FastNoiseLite.h"
#include "chunk.h"
#include "light.h"

const f32 gravity = 9.81f;

// WARNING! DO NOT USE THIS CLASS YET UNTIL UNNECESSARY FACE ELIMINATION METHOD HAS BEEN FULLY IMPLEMENTED, UNLESS YOU WANT YOUR PC TO EXPLODE!!!
class World {
	std::vector<Chunk*> chunks;
	Texture mcWorldTextureAtlas;
	Shader* mcShader;
	FastNoiseLite mcNoise;
	u32 mcSeed;
public:
	// Minecraft generates its worlds either randomly, or by inputing a string (which will be converted into a seed)
	// CASE 1: Seed not provided
	World() : 
		mcShader(new Shader("resources/shaders", "mcShader.vert", "mcShader.frag")),
		mcWorldTextureAtlas(Texture(0, "resources/textures", "atlas.png", "diffuse", GL_RGBA, GL_NEAREST))
	{
		srand(time(NULL));
		mcSeed = rand();

		Init();
	}
	// Case 2: Seed provided
	World(std::string seed) :
		mcSeed(StrToHash(seed)),
		mcShader(new Shader("resources/shaders", "mcShader.vert", "mcShader.frag")),
		mcWorldTextureAtlas(Texture(0, "resources/textures", "atlas.png", "diffuse", GL_RGBA, GL_NEAREST))
	{

		Init();
	}
	~World() { delete mcShader; }

	void Render(Camera camera, f32 aspect_ratio) {
		for (auto chunk : chunks) {
			chunk->RenderChunk(mcShader, mcWorldTextureAtlas, camera, aspect_ratio);
		}
	}

	Shader* getMCShader() { return mcShader; }

private:
	u32 StrToHash(std::string& str) {
		u32 hash = 0;
		u32 val = 32;
		for (auto chr : str)
			hash = val * hash + chr;
		return hash;
	}

	void Init() {		
		// 1. Initialize FastNoiseLite class using the mcSeed generated
		mcNoise = FastNoiseLite(mcSeed);

		// 2. Generate chunks
		u32 chunkSizeTest = 5;

		for (u32 x = 0; x < chunkSizeTest; x++) {
			for (u32 z = 0; z < chunkSizeTest; z++) {
				chunks.push_back(new Chunk(glm::vec2(x, z), mcNoise));
			}
		}
	}
public:
	AmbientLight envLight = AmbientLight(glm::vec3(0.32f, 0.95f, 1.00f), 1.0f);
};

#endif