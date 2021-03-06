#pragma once

#ifndef _MC_CHUNK_
#define _MC_CHUNK_

#include "mc_blocks.h"

class Chunk {
	f32 noise_amplitude = 10.0f;
	i32 min_height = 20;
	i32 water_level = 22;
public:
	// Constantes del chunk
	const u32 width = 16;
	const u32 lenght = 16;
	const u32 height = 75;  // Max height in Minecraft is 256 blocks

	std::vector<MCblock*> blocks;

	glm::vec3 absolute_position;

	Chunk(glm::vec2 position, FastNoiseLite noise) :
		absolute_position(glm::vec3(width* position.x, 0.0f, lenght* position.y))

	{
		// Step 1: Generate all the blocks in a chunk as AIR blocks and turn the ones below the generated noise into STONE
		// PLUS: Water is generated in this step too!
		for (u32 y = 0; y < height; y++) for (u32 x = 0; x < width; x++) for (u32 z = 0; z < lenght; z++) {
			blocks.push_back(new MCblock(BlockID::AIR, absolute_position + glm::vec3(x, y, z)));
			u32 slot = (y * lenght + x) * width + z;
			i32 noiseHeight = noise.GetNoise((f32)(absolute_position.x + x), (f32)(absolute_position.z + z)) * noise_amplitude + min_height;

			auto block = blocks[slot];

			// If the block is below the noise map, replace it with STONE
			if (block->getPosition().y < noiseHeight) block->ChangeBlock(BlockID::STONE);

			// If the AIR block is below the water level, turn it into WATER
			if (block->id == BlockID::AIR && block->getPosition().y <= water_level) block->ChangeBlock(BlockID::WATER);
		}
		// Step 2: Replace the top layers of the stone with surface blocks like DIRT, GRASS_BLOCK, SAND, and so on...
		for (u32 y = 0; y < height; y++) {
			i32 dirt_depth = rand() % 4 + 3;

			for (u32 x = 0; x < width; x++) for (u32 z = 0; z < lenght; z++) {
				i32 noiseHeight = noise.GetNoise((f32)(absolute_position.x + x), (f32)(absolute_position.z + z)) * noise_amplitude + min_height;

				u32 slot = (y * lenght + x) * width + z;
				auto block = blocks[slot];

				if (block->getPosition().y == 0 || (block->getPosition().y < 4 && rand() % 100 < 65))
					block->ChangeBlock(BlockID::BEDROCK);

				if (block->id == BlockID::STONE && (noiseHeight - dirt_depth <= block->getPosition().y && block->getPosition().y <= noiseHeight)) {
					block->ChangeBlock(BlockID::DIRT);

					if (block->getPosition().y == noiseHeight - 1)
						block->ChangeBlock(BlockID::GRASS_BLOCK);
				}
				if (block->id == BlockID::WATER) {
					auto block_below = blocks[((y - 1) * lenght + x) * width + z];

					if (block_below->id != BlockID::WATER)
						block_below->ChangeBlock(BlockID::SAND);
				}
			}
		}
		// Step 3 (Actually it's step 4, but since we don't have any perlin-worm-like library we're skipping that part): Generate ores
		u32 absolutely = 18;
		u32 common = 9;
		u32 rare = 4;
		u32 none = 0;

		for (u32 y = 0; y < height; y++) for (u32 x = 0; x < width; x++) for (u32 z = 0; z < lenght; z++) {
			u32 slot = (y * lenght + x) * width + z;
			auto block = blocks[slot];

			// Ore spawn chances handling
			// --------------------------
			// Coal
			if (block->id == BlockID::STONE) {
				u32 coal_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 52) { coal_chance = absolutely; }
				else if (block->getPosition().y <= 124) { coal_chance = common; }
				else if (block->getPosition().y <= 127) { coal_chance = rare; }

				if (rand() % 300 < coal_chance) block->ChangeBlock(BlockID::COAL_ORE);
			}
			// Iron
			if (block->id == BlockID::STONE) {
				u32 iron_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 54) { iron_chance = absolutely; }
				else if (block->getPosition().y <= 61) { iron_chance = common; }
				else if (block->getPosition().y <= 63) { iron_chance = rare; }

				if (rand() % 400 < iron_chance) block->ChangeBlock(BlockID::IRON_ORE);
			}
			// Gold
			if (block->id == BlockID::STONE) {
				u32 gold_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 29) { gold_chance = absolutely; }
				else if (block->getPosition().y <= 29) { gold_chance = common; }
				else if (block->getPosition().y <= 33) { gold_chance = rare; }

				if (rand() % 500 < gold_chance) block->ChangeBlock(BlockID::GOLD_ORE);
			}
			// Lapis L??zuli
			if (block->id == BlockID::STONE) {
				u32 lapis_chance = none;
				if (13 <= block->getPosition().y && block->getPosition().y <= 17) { lapis_chance = absolutely; }
				else if (block->getPosition().y <= 23) { lapis_chance = common; }
				else if (block->getPosition().y <= 33) { lapis_chance = rare; }

				if (rand() % 1250 < lapis_chance) block->ChangeBlock(BlockID::LAPIS_ORE);
			}
			// Redstone
			if (block->id == BlockID::STONE) {
				u32 redstone_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 12) { redstone_chance = absolutely; }
				else if (block->getPosition().y <= 13) { redstone_chance = common; }
				else if (block->getPosition().y <= 15) { redstone_chance = rare; }

				if (rand() % 500 < redstone_chance) block->ChangeBlock(BlockID::REDSTONE_ORE);
			}
			// DIAMOND
			if (block->id == BlockID::STONE) {
				u32 diamond_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 12) { diamond_chance = absolutely; }
				else if (block->getPosition().y <= 13) { diamond_chance = common; }
				else if (block->getPosition().y <= 15) { diamond_chance = rare; }

				if (rand() % 1250 < diamond_chance) block->ChangeBlock(BlockID::DIAMOND_ORE);
			}
			// Emerald
			if (block->id == BlockID::STONE) {
				u32 emerald_chance = none;
				if (5 <= block->getPosition().y && block->getPosition().y <= 28) { emerald_chance = absolutely; }
				else if (block->getPosition().y <= 29) { emerald_chance = common; }
				else if (block->getPosition().y <= 32) { emerald_chance = rare; }

				if (rand() % 5000 < emerald_chance) block->ChangeBlock(BlockID::EMERALD_ORE);
			}
		}

	}

	void RenderChunk(Shader* shader, Texture& texture, Camera camera, f32 aspect_ratio, bool ch_front = true, bool ch_back = true, bool ch_left = true, bool ch_right = true) {
		for (u32 y = 0; y < height; y++) for (u32 x = 0; x < width; x++) for (u32 z = 0; z < lenght; z++) {
			bool _top = true, _bottom = true, _front = true, _back = true, _left = true, _right = true;
			auto block = blocks[(y * lenght + x) * width + z];

			if (x > 0) {
				auto left = blocks[(y * lenght + (x - 1)) * width + z];
				if (block->is_fluid) { if (block->id == left->id) _left = false; }
				else if (block->is_solid == left->is_solid) _left = false;
			}
			else if (!ch_left) _left = false;
			if (x < width - 1) {
				auto right = blocks[(y * lenght + (x + 1)) * width + z];
				if (block->is_fluid) { if (block->id == right->id) _right = false; }
				else if (block->is_solid == right->is_solid) _right = false;
			}
			else if (!ch_right) _right = false;

			if (y > 0) {
				auto bottom = blocks[((y - 1) * lenght + x) * width + z];
				if (block->is_fluid) { if (block->id == bottom->id) _bottom = false; }
				else if (block->is_solid == bottom->is_solid) _bottom = false;
			}
			if (y < height - 1) {
				auto top = blocks[((y + 1) * lenght + x) * width + z];
				if (block->is_fluid) { if (block->id == top->id) _top = false; }
				else if (block->is_solid == top->is_solid) _top = false;
			}

			if (z > 0) {
				auto back = blocks[(y * lenght + x) * width + (z - 1)];
				if (block->is_fluid) { if (block->id == back->id) _back = false; }
				else if (block->is_solid == back->is_solid) _back = false;
			}
			else if (!ch_back) _back = false;
			if (z < lenght - 1) {
				auto front = blocks[(y * lenght + x) * width + (z + 1)];
				if (block->is_fluid) { if (block->id == front->id) _front = false; }
				else if (block->is_solid == front->is_solid) _front = false;
			}
			else if (!ch_front) _front = false;

			block->Render(shader, texture, camera, aspect_ratio, _top, _bottom, _front, _back, _left, _right);
		}
	}
};

#endif