// ***************************************************
// *  Definición de Macros e inclusión de Librerías  *
// ***************************************************
#include "world.h"

// ***************
// *  Variables  *
// ***************
Camera camera(glm::vec3(-10.0f, 30.0f, 30.0f), glm::vec3(-10.0f, -45.0f, 0.0f));

const u32 SCR_WIDTH2 = 1920;
const u32 SCR_HEIGHT2 = 1080;
const u32 WND_WIDTH2 = 1600;
const u32 WND_HEIGHT2 = 900;

// Fuente de luz
OmniLight light(glm::vec3(0.0f, 65.0f, 5.0f), glm::vec3(1.0f, 0.9f, 0.8f), 1.0f);
AmbientLight envLight(glm::vec3(0.32f, 0.95f, 1.00f), 1.0f);

// *********************
// *  Otras librerías  *
// *********************
#include "events.h"

// ***************
// *  Funciones  *
// ***************
// Inserte funciones extra aquí...


// **********************
// * Función principal  *
// **********************
int main() {
	// Inicialización de OpenGL
	GLFWwindow* window = glutilInit(3, 3, WND_WIDTH2, WND_HEIGHT2, "Minecraft", SCR_WIDTH2, SCR_HEIGHT2);
	Shader* shader = new Shader("resources/shaders", "mcshader.vert", "mcshader.frag");
	Shader* lsShader = new Shader("resources/shaders", "lightsource.vert", "lightsource.frag");

	camera.zFar = 16 * 12;

	// Anclar eventos
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	// Activar funciones
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Inicializar función Noise
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// Bloque de prueba
	MCblock* testBlock = new MCblock(BlockID::REDSTONE_BLOCK, light.position);
	// Chunk de prueba
	Chunk* testChunk = new Chunk(glm::vec2(0.0f), noise);

	// Creación de la textura base
	Texture atlas = Texture(0, "resources/textures", "atlas.png", "diffuse", GL_RGBA, GL_NEAREST);

	while (!glfwWindowShouldClose(window)) {
		f32 currentFrame = (f32)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(envLight.color.r, envLight.color.g, envLight.color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->useProgram();
		shader->setVec3("lightPos", light.position);
		shader->setVec3("lightColor", light.color);
		shader->setF32("lightStrenght", light.intensity);
		shader->setVec3("ambientColor", glm::vec3(1.0f));
		shader->setF32("ambientStrenght", envLight.intensity);
		shader->setVec3("cameraPos", camera.position);

		testChunk->RenderChunk(shader, atlas, camera, REL_16_9);
		lsShader->useProgram();
		lsShader->setVec3("lightColor", light.color);
		lsShader->setF32("lightIntensity", light.intensity);
		testBlock->Render(lsShader, atlas, camera, REL_16_9);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;
	delete testBlock;
	delete testChunk;

	return 0;
}