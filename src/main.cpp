// ***************************************************
// *  Definición de Macros e inclusión de Librerías  *
// ***************************************************
#include <glutil.h>
#include "FastNoiseLite.h"
#include "mc_blocks.h"
//#include "chunk.h"

// ***************
// *  Variables  *
// ***************
Camera camera(glm::vec3(5.0f, 40.0f, 5.0f), glm::vec3(-30.0f, 45.0f, 0.0f));

// Fuente de luz
glm::vec3 lightPos(1.0f, 40.0f, 1.0f);
glm::vec3 lightColor(1.0f, 0.9f, 0.8f);
f32 lightStrenght = 0.4f;

// Entorno
glm::vec3 envLight(0.1f, 0.2f, 0.3f);
f32 envStrength = 1.0f;

const u32 SCR_WIDTH2 = 2048;
const u32 SCR_HEIGHT2 = 1152;
const u32 WND_WIDTH2 = 1600;
const u32 WND_HEIGHT2 = 900;

// Otros
f32 amplitud = 4.0f;
i32 altura_minima = 32;

// *********************
// *  Otras librerías  *
// *********************
#include "events.h"

// ***************
// *  Funciones  *
// ***************
std::vector<Block*>* Wall(std::vector<Block*>* bloques, i32 fila, i32 columna, i8 c, f32 t, f32 inicio) {
	f32 x, y, z;

	auto temp = bloques;

	for (u32 i = 1; i < fila + 1; i++)
		for (u32 j = 0; j < columna; j++) {
			switch (c) {
			case 'f': z = t; x = inicio + j; break;
			default:  x = t; z = inicio + j; break;
			}
			y = i;
			glm::vec3 pos = glm::vec3(x, y + altura_minima + (i32)(amplitud / 2) + 1, z);
			temp->push_back(new Block(BlockID::OAK_PLANKS, pos));
		}

	return temp;
}

// **********************
// * Función principal  *
// **********************
int main() {
	// Inicialización de OpenGL
	GLFWwindow* window = glutilInit(3, 3, WND_WIDTH2, WND_HEIGHT2, "Minecraft!", SCR_WIDTH2, SCR_HEIGHT2);
	Shader* shader = new Shader();

	// Anclar eventos
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	// Activar funciones
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Inicializar función Noise
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// Creación de la textura base
	Texture atlas = Texture(0, "resources/textures", "atlas.png", "diffuse", GL_RGBA, GL_NEAREST);

	// Bloque de prueba
	Block test = Block(BlockID::TEST, glm::vec3(0.0f));

	// Creación del terreno
	// 1 chunk equivale a 16 bloques
	u32 l = 32;
	std::vector<Block*> blocksTerreno;
	for (u32 x = 0; x < l; x++) {
		for (u32 z = 0; z < l; z++) {
			glm::vec3 pos = glm::vec3(x, (i32)(noise.GetNoise((f32)x, (f32)z) * amplitud + altura_minima), z);
			blocksTerreno.push_back(new Block(BlockID::GRASS, pos));

			if (blocksTerreno[x * l + z]->getPosition().y <= 34) {
				blocksTerreno[x * l + z]->ChangeBlock(BlockID::SAND);
			}
			if (blocksTerreno[x * l + z]->getPosition().y <= 32) {
				blocksTerreno[x * l + z]->ChangeBlock(BlockID::WATER);
			}
			//std::cout << blocksTerreno[x * l + z]->getPosition().y << " ";
		}
		//std::cout << std::endl;
	}

	// Creación de la pared
	std::vector<Block*> blocksParedes;

	// Parametro Pared
	std::vector<glm::vec3> positionsPared;
	blocksParedes = *Wall(&blocksParedes, 5, 4, 'f', 10, 11);
	blocksParedes = *Wall(&blocksParedes, 5, 6, 'p', 10, 10);
	blocksParedes = *Wall(&blocksParedes, 5, 6, 'p', 15, 10);

	while (!glfwWindowShouldClose(window)) {
		f32 currentFrame = (f32)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->useProgram();
		shader->setVec3("lightPos", lightPos);
		shader->setVec3("lightColor", lightColor);
		shader->setF32("lightStrenght", lightStrenght);

		// test.Render(shader, atlas, camera, REL_16_9);
		for (u32 i = 0; i < blocksTerreno.size(); i++)
			blocksTerreno[i]->Render(shader, atlas, camera, REL_16_9);
		for (u32 i = 0; i < blocksParedes.size(); i++)
			blocksParedes[i]->Render(shader, atlas, camera, REL_16_9);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;

	return 0;
}