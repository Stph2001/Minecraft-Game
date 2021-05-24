#pragma once

#ifndef _MC_BLOCKS_
#define _MC_BLOCKS_

#include "cube_base.h"

enum class BlockID {
	AIR,          //  0
	GRASS,        //  1
	DIRT,         //  2
	STONE,        //  3
	COBBLESTONE,  //  4
	SAND,         //  5
	OAK_LOG,      //  6
	OAK_PLANKS,   //  7
	OAK_LEAVES,   //  8
	WATER,        //  9
	LAVA,         // 10
	GLASS,        // 11
	BEDROCK,      // 12
	TEST,         // 13
	UNKNOWN       // 14
};
enum class BlockSFX {
	PLANT,  // 0
	DIRT,   // 1
	STONE,  // 2
	SAND,   // 3
	WOOD,   // 4
	WATER,  // 5
	LAVA,   // 6
	GLASS,  // 7
	NONE    // 8
};

struct Block {
private:
	Cube* block;

	void InitialSet(BlockID first_id, glm::vec3 position) {
		id = first_id;

		// Is the block solid or a fluid?
		switch (id) {
		case BlockID::WATER:
		case BlockID::LAVA:
			is_solid = false;
			is_fluid = true;  break;
		case BlockID::AIR:
			is_solid = false;
			is_fluid = false; break;
		default:
			is_solid = true;
			is_fluid = false; break;
		}

		// Does the block obbey physics?
		switch (id) {
		case BlockID::SAND:
			obbeys_gravity = true;  break;
		default:
			obbeys_gravity = false; break;
		}

		// Which sound effect should the block have?
		switch (id) {
		case BlockID::GRASS:
		case BlockID::OAK_LEAVES:
			sfx = BlockSFX::PLANT; break;
		case BlockID::DIRT:
			sfx = BlockSFX::DIRT;  break;
		case BlockID::STONE:
		case BlockID::COBBLESTONE:
		case BlockID::BEDROCK:
		case BlockID::TEST:
			sfx = BlockSFX::STONE; break;
		case BlockID::SAND:
			sfx = BlockSFX::SAND;  break;
		case BlockID::OAK_LOG:
		case BlockID::OAK_PLANKS:
			sfx = BlockSFX::WOOD;  break;
		case BlockID::WATER:
			sfx = BlockSFX::WATER; break;
		case BlockID::LAVA:
			sfx = BlockSFX::LAVA;  break;
		case BlockID::GLASS:
			sfx = BlockSFX::GLASS; break;
		default:
			sfx = BlockSFX::NONE;  break;
		}

		// Assign a UV coordinate for each side of the cube based on its type
		switch (id) {
		case BlockID::GRASS:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					0, 2, 1, 1, 1, 1
				});
			block_name = "Grass block"; break;
		case BlockID::DIRT:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					2, 2, 2, 2, 2, 2
				});
			block_name = "Dirt block"; break;
		case BlockID::STONE:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					3, 3, 3, 3, 3, 3
				});
			block_name = "Stone"; break;
		case BlockID::COBBLESTONE:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					4, 4, 4, 4, 4, 4
				});
			block_name = "Cobblestone"; break;
		case BlockID::SAND:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					5, 5, 5, 5, 5, 5
				});
			block_name = "Sand block"; break;
		case BlockID::OAK_LOG:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					7, 7, 6, 6, 6, 6
				});
			block_name = "Oak log"; break;
		case BlockID::OAK_PLANKS:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					8, 8, 8, 8, 8, 8
				});
			block_name = "Oak planks"; break;
		case BlockID::OAK_LEAVES:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					9, 9, 9, 9, 9, 9
				});
			block_name = "Oak leaves"; break;
		case BlockID::WATER:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					10, 10, 10, 10, 10, 10
				});
			block_name = "Water"; break;
		case BlockID::LAVA:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					11, 11, 11, 11, 11, 11
				});
			block_name = "Lava"; break;
		case BlockID::GLASS:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					12, 12, 12, 12, 12, 12
				});
			block_name = "Glass block"; break;
		case BlockID::BEDROCK:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					13, 13, 13, 13, 13, 13
				});
			block_name = "Bedrock"; break;
		case BlockID::TEST:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					14, 14, 14, 14, 14, 14
				});
			block_name = "Test block"; break;
		default:
			block = new Cube(position, glm::vec3(1.0f), 0.25,
				{
					15, 15, 15, 15, 15, 15
				});
			block_name = "???"; break;
		}
	}
public:
	bool is_solid;
	bool is_fluid;
	bool obbeys_gravity;
	BlockID id;
	BlockSFX sfx;
	std::string block_name;
public:
	Block(BlockID id, glm::vec3 position) : id(id) { InitialSet(id, position); }
	~Block() { delete block; }

	// Condición única para renderizar: Que el bloque no sea de aire
	void Render(Shader* shader, Texture& texture, Camera camera, f32 aspect_ratio) {
		if (id != BlockID::AIR) block->Render(*shader, texture, camera, aspect_ratio);
	}

	// Esto simulará la acción de romper / colocar bloque
	void ChangeBlock(BlockID new_id) { InitialSet(new_id, block->getPosition()); }

	// Retornar posición del bloque
	glm::vec3 getPosition() { return block->getPosition(); }
};

#endif