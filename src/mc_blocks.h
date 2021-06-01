#pragma once

#ifndef _MC_BLOCKS_
#define _MC_BLOCKS_

enum class BlockID {
	// A
	AIR,
	// B
	BEDROCK,
	BRICKS,
	// C
	CLAY,
	COAL_BLOCK,
	COAL_ORE,
	COBBLESTONE,
	CRAFTING_TABLE,
	// D
	DANDELION,
	DIAMOND_BLOCK,
	DIAMOND_ORE,
	DIRT,
	// E
	EMERALD_BLOCK,
	EMERALD_ORE,
	// F
	FURNANCE,
	FURNANCE_ON,
	// G
	GLASS,
	GOLD_BLOCK,
	GOLD_ORE,
	GRASS,
	GRASS_BLOCK,
	GRAVEL,
	// I
	IRON_BLOCK,
	IRON_ORE,
	// L
	LAPIS_BLOCK,
	LAPIS_ORE,
	LAVA,
	// O
	OAK_LEAVES,
	OAK_LOG,
	OAK_PLANKS,
	OBSIDIAN,
	// P
	POPPY,
	// R
	REDSTONE_BLOCK,
	REDSTONE_ORE,
	// S
	SAND,
	SANDSTONE,
	STONE,
	STONE_BRICKS,
	// T
	TEST,
	// U
	UNKNOWN,
	// W
	WATER
};
enum class BlockSFX {
	PLANT,
	DIRT,
	STONE,
	SAND,
	WOOD,
	WATER,
	LAVA,
	GLASS,
	NONE
};
enum class BlockMeshType {
	DEFAULT,
	STAIR,
	SLAB,
	FLUID,
	SPRITE
};

#include "cube_base.h"

struct MCblock {
	MCblock(BlockID id, glm::vec3 position) : id(id) { SetBlock(id, position); }
	~MCblock() { delete block; }

	// Condición única para renderizar: Que el bloque no sea de aire
	void Render(Shader* shader, Texture& texture, Camera camera, f32 aspect_ratio) {
		if (id != BlockID::AIR) block->Render(*shader, texture, camera, aspect_ratio);
	}

	// Esto simulará la acción de romper / colocar bloque
	void ChangeBlock(BlockID new_id) { SetBlock(new_id, block->getPosition()); }

	// Retornar posición del bloque
	glm::vec3 getPosition() { return block->getPosition(); }
private:
	void SetBlock(BlockID first_id, glm::vec3 position) {
		id = first_id;

		switch (id) {
		case BlockID::AIR:            Air(position);           break;
		case BlockID::BEDROCK:        Bedrock(position);       break;
		case BlockID::BRICKS:         Bricks(position);        break;
		case BlockID::CLAY:           Clay(position);          break;
		case BlockID::COAL_BLOCK:     CoalBlock(position);     break;
		case BlockID::COAL_ORE:       CoalOre(position);       break;
		case BlockID::CRAFTING_TABLE: CraftingTable(position); break;
		case BlockID::DANDELION:      Dandelion(position);     break;
		case BlockID::DIAMOND_BLOCK:  DiamondBlock(position);  break;
		case BlockID::DIAMOND_ORE:    DiamondOre(position);    break;
		case BlockID::DIRT:           Dirt(position);          break;
		case BlockID::EMERALD_BLOCK:  EmeralBlock(position);   break;
		case BlockID::EMERALD_ORE:    EmeraldOre(position);    break;
		case BlockID::FURNANCE:       Furnance(position);      break;
		case BlockID::FURNANCE_ON:    FurnanceOn(position);    break;
		case BlockID::GLASS:          Glass(position);         break;
		case BlockID::GOLD_BLOCK:     GoldBlock(position);     break;
		case BlockID::GOLD_ORE:       GoldOre(position);       break;
		case BlockID::GRASS:          Grass(position);         break;
		case BlockID::GRASS_BLOCK:    GrassBlock(position);    break;
		case BlockID::GRAVEL:         Gravel(position);        break;
		case BlockID::IRON_BLOCK:     IronBlock(position);     break;
		case BlockID::IRON_ORE:       IronOre(position);       break;
		case BlockID::LAPIS_BLOCK:    LapisBlock(position);    break;
		case BlockID::LAPIS_ORE:      LapisOre(position);      break;
		case BlockID::LAVA:           Lava(position);          break;
		case BlockID::OAK_LEAVES:     OakLeaves(position);     break;
		case BlockID::OAK_LOG:        OakLog(position);        break;
		case BlockID::OAK_PLANKS:     OakPlanks(position);     break;
		case BlockID::POPPY:          Poppy(position);         break;
		case BlockID::REDSTONE_BLOCK: RedstoneBlock(position); break;
		case BlockID::REDSTONE_ORE:   RedstoneOre(position);   break;
		case BlockID::SAND:           Sand(position);          break;
		case BlockID::SANDSTONE:      Sandstone(position);     break;
		case BlockID::STONE:          Stone(position);         break;
		case BlockID::STONE_BRICKS:   StoneBricks(position);   break;
		case BlockID::TEST:           Test(position);          break;
		case BlockID::UNKNOWN:        Unknown(position);       break;
		case BlockID::WATER:          Water(position);         break;
		}
	}
public:
	// Properties of the block
	bool is_solid;
	bool is_fluid;
	bool is_transparent;
	bool emits_light;
	bool obbeys_gravity;

	BlockID id;
	BlockMeshType mesh_type;
	BlockSFX sfx;
	std::string block_name;

private:
	Cube* block;

	// Modify this value when adding more tiles to the texture atlas
	f32 atlas_rescale = 1.0f / 8.0f;

	// Block settings
	// A
	void Air(glm::vec3 pos);
	// B
	void Bedrock(glm::vec3 pos);
	void Bricks(glm::vec3 pos);
	// C
	void Clay(glm::vec3 pos);
	void CoalBlock(glm::vec3 pos);
	void CoalOre(glm::vec3 pos);
	void Cobblestone(glm::vec3 pos);
	void CraftingTable(glm::vec3 pos);
	// D
	void Dandelion(glm::vec3 pos);
	void DiamondBlock(glm::vec3 pos);
	void DiamondOre(glm::vec3 pos);
	void Dirt(glm::vec3 pos);
	// E
	void EmeralBlock(glm::vec3 pos);
	void EmeraldOre(glm::vec3 pos);
	// F
	void Furnance(glm::vec3 pos);
	void FurnanceOn(glm::vec3 pos);
	// G
	void Glass(glm::vec3 pos);
	void GoldBlock(glm::vec3 pos);
	void GoldOre(glm::vec3 pos);
	void Grass(glm::vec3 pos);
	void GrassBlock(glm::vec3 pos);
	void Gravel(glm::vec3 pos);
	// I
	void IronBlock(glm::vec3 pos);
	void IronOre(glm::vec3 pos);
	// L
	void LapisBlock(glm::vec3 pos);
	void LapisOre(glm::vec3 pos);
	void Lava(glm::vec3 pos);
	// O
	void OakLeaves(glm::vec3 pos);
	void OakLog(glm::vec3 pos);
	void OakPlanks(glm::vec3 pos);
	void Obsidian(glm::vec3 pos);
	// P
	void Poppy(glm::vec3 pos);
	// R
	void RedstoneBlock(glm::vec3 pos);
	void RedstoneOre(glm::vec3 pos);
	// S
	void Sand(glm::vec3 pos);
	void Sandstone(glm::vec3 pos);
	void Stone(glm::vec3 pos);
	void StoneBricks(glm::vec3 pos);
	// T
	void Test(glm::vec3 pos);
	// U
	void Unknown(glm::vec3 pos);
	// W
	void Water(glm::vec3 pos);
};

// **********************************************************************
// |       Block Properties Configurator functions definitions          |
// | ------------------------------------------------------------------ |
// |  WARNING: This is gonna turn into a way loooooong file for now...  |
// **********************************************************************
// *  A
// * ---
void MCblock::Air(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::NONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Air";

	block = new Cube(pos, atlas_rescale, { 65, 65, 65, 65, 65, 65 });
}
// * ---
// *  B
// * ---
void MCblock::Bedrock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Bedrock";

	block = new Cube(pos, atlas_rescale, { 5, 5, 5, 5, 5, 5 });
}
void MCblock::Bricks(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Bricks";

	block = new Cube(pos, atlas_rescale, { 19, 19, 19, 19, 19, 19 });
}
// * ---
// *  C
// * ---
void MCblock::Clay(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::DIRT;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Clay";

	block = new Cube(pos, atlas_rescale, { 15, 15, 15, 15, 15, 15 });
}
void MCblock::CoalBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Coal Block";

	block = new Cube(pos, atlas_rescale, { 40, 40, 40, 40, 40, 40 });
}

void MCblock::CoalOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Coal Ore";

	block = new Cube(pos, atlas_rescale, { 8, 8, 8, 8, 8, 8 });
}
void MCblock::Cobblestone(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Cobblestone";

	block = new Cube(pos, atlas_rescale, { 4, 4, 4, 4, 4, 4 });
}
void MCblock::CraftingTable(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::WOOD;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Crafting Table";

	block = new Cube(pos, atlas_rescale, { 24, 27, 25, 25, 26, 26 });
}
// * ---
// *  D
// * ---
void MCblock::Dandelion(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::PLANT;
	mesh_type = BlockMeshType::SPRITE;

	block_name = "Dandelion";

	block = new Cube(pos, atlas_rescale, { 30, 30, 30, 30, 30, 30 });
}
void MCblock::DiamondBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Diamond Block";

	block = new Cube(pos, atlas_rescale, { 45, 45, 45, 45, 45, 45 });
}
void MCblock::DiamondOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Diamond Ore";

	block = new Cube(pos, atlas_rescale, { 13, 13, 13, 13, 13, 13 });
}
void MCblock::Dirt(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::DIRT;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Dirt";

	block = new Cube(pos, atlas_rescale, { 2, 2, 2, 2, 2, 2 });
}
// * ---
// *  E
// * ---
void MCblock::EmeralBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Emerald Block";

	block = new Cube(pos, atlas_rescale, { 46, 46, 46, 46, 46, 46 });
}
void MCblock::EmeraldOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Emerald Ore";

	block = new Cube(pos, atlas_rescale, { 14, 14, 14, 14, 14, 14 });
}
// * ---
// *  F
// * ---
void MCblock::Furnance(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Furnance";

	block = new Cube(pos, atlas_rescale, { 35, 35, 32, 34, 34, 34 });
}
void MCblock::FurnanceOn(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Furnance On";

	block = new Cube(pos, atlas_rescale, { 35, 35, 33, 34, 34, 34 });
}
// * ---
// *  G
// * ---
void MCblock::Glass(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::GLASS;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Glass";

	block = new Cube(pos, atlas_rescale, { 36, 36, 36, 36, 36, 36 });
}
void MCblock::GoldBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Gold Block";

	block = new Cube(pos, atlas_rescale, { 42, 42, 42, 42, 42, 42 });
}
void MCblock::GoldOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Gold Ore";

	block = new Cube(pos, atlas_rescale, { 10, 10, 10, 10, 10, 10 });
}
void MCblock::Grass(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::PLANT;
	mesh_type = BlockMeshType::SPRITE;

	block_name = "Grass";

	block = new Cube(pos, atlas_rescale, { 31, 31, 31, 31, 31, 31 });
}
void MCblock::GrassBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::PLANT;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Grass Block";

	block = new Cube(pos, atlas_rescale, { 0, 2, 1, 1, 1, 1 });
}
void MCblock::Gravel(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = true;

	sfx = BlockSFX::DIRT;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Gravel";

	block = new Cube(pos, atlas_rescale, { 7, 7, 7, 7, 7, 7 });
}
// * ---
// *  I
// * ---
void MCblock::IronBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Iron Block";

	block = new Cube(pos, atlas_rescale, { 41, 41, 41, 41, 41, 41 });
}
void MCblock::IronOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Iron Ore";

	block = new Cube(pos, atlas_rescale, { 9, 9, 9, 9, 9, 9 });
}
// * ---
// *  L
// * ---
void MCblock::LapisBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Lapis Lazuli Block";

	block = new Cube(pos, atlas_rescale, { 43, 43, 43, 43, 43, 43 });
}
void MCblock::LapisOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Lapis Lazuli Ore";

	block = new Cube(pos, atlas_rescale, { 11, 11, 11, 11, 11, 11 });
}
void MCblock::Lava(glm::vec3 pos) {
	is_solid = false;
	is_fluid = true;
	is_transparent = false;
	emits_light = true;
	obbeys_gravity = false;

	sfx = BlockSFX::LAVA;
	mesh_type = BlockMeshType::FLUID;

	block_name = "Lava";

	block = new Cube(pos, atlas_rescale, { 55, 55, 55, 55, 55, 55 });
}
// * ---
// *  O
// * ---
void MCblock::OakLeaves(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::PLANT;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Oak Leaves";

	block = new Cube(pos, atlas_rescale, { 23, 23, 23, 23, 23, 23 });
}
void MCblock::OakLog(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::WOOD;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Oak Log";

	block = new Cube(pos, atlas_rescale, { 22, 22, 21, 21, 21, 21 });
}
void MCblock::OakPlanks(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::WOOD;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Oak Planks";

	block = new Cube(pos, atlas_rescale, { 27, 27, 27, 27, 27, 27 });
}
void MCblock::Obsidian(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Obsidian";

	block = new Cube(pos, atlas_rescale, { 28, 28, 28, 28, 28, 28 });
}
// * ---
// *  P
// * ---
void MCblock::Poppy(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = true;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::PLANT;
	mesh_type = BlockMeshType::SPRITE;

	block_name = "Poppy";

	block = new Cube(pos, atlas_rescale, { 29, 29, 29, 29, 29, 29 });
}
// * ---
// *  R
// * ---
void MCblock::RedstoneBlock(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Redstone Block";

	block = new Cube(pos, atlas_rescale, { 44, 44, 44, 44, 44, 44 });
}
void MCblock::RedstoneOre(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Redstone Ore";

	block = new Cube(pos, atlas_rescale, { 12, 12, 12, 12, 12, 12 });
}
// * ---
// *  S
// * ---
void MCblock::Sand(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = true;

	sfx = BlockSFX::SAND;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Sand";

	block = new Cube(pos, atlas_rescale, { 6, 6, 6, 6, 6, 6 });
}
void MCblock::Sandstone(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Sandstone";

	block = new Cube(pos, atlas_rescale, { 16, 18, 17, 17, 17, 17 });
}
void MCblock::Stone(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Stone";

	block = new Cube(pos, atlas_rescale, { 3, 3, 3, 3, 3, 3 });
}
void MCblock::StoneBricks(glm::vec3 pos) {
	is_solid = true;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Stone Bricks";

	block = new Cube(pos, atlas_rescale, { 20, 20, 20, 20, 20, 20 });
}
// * ---
// *  T
// * ---
void MCblock::Test(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = true;

	sfx = BlockSFX::STONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "Test Block";

	block = new Cube(pos, atlas_rescale, { 62, 62, 62, 62, 62, 62 });
}
// * ---
// *  U
// * ---
void MCblock::Unknown(glm::vec3 pos) {
	is_solid = false;
	is_fluid = false;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::NONE;
	mesh_type = BlockMeshType::DEFAULT;

	block_name = "???";

	block = new Cube(pos, atlas_rescale, { 63, 63, 63, 63, 63, 63 });
}
// * ---
// *  W
// * ---
void MCblock::Water(glm::vec3 pos) {
	is_solid = false;
	is_fluid = true;
	is_transparent = false;
	emits_light = false;
	obbeys_gravity = false;

	sfx = BlockSFX::WATER;
	mesh_type = BlockMeshType::FLUID;

	block_name = "Water";

	block = new Cube(pos, atlas_rescale, { 54, 54, 54, 54, 54, 54 });
}
#endif