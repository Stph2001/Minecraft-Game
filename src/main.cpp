// ***************************************************
// *  Definición de Macros e inclusión de Librerías  *
// ***************************************************
#include "world.h"
//#include <figures.h>

// ***************
// *  Variables  *
// ***************
Camera camera(glm::vec3(15.0f, 30.0f, 25.0f), glm::vec3(-10.0f, -45.0f, 0.0f));

const u32 SCR_WIDTH2 = 1920;
const u32 SCR_HEIGHT2 = 1080;
const u32 WND_WIDTH2 = 1600;
const u32 WND_HEIGHT2 = 900;

// Fuente de luz
OmniLight light(glm::vec3(15.0f, 30.0f, 5.0f), glm::vec3(0.89f, 0.89f, 1.0f), 1.0f);
AmbientLight envLight(glm::vec3(0.00f, 0.00f, 0.12f), 0.2f);

// *********************
// *  Otras librerías  *
// *********************
#include "events.h"

// *************************
// *  Librerías de Model3D *
// *************************
#include "classesTeacher/files.hpp"
#include "classesTeacher/model.hpp"

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

	// Models 3D
	Files* files = new Files();
	Shader2* shaderModel = new Shader2(files, "shader.vert", "shader.frag");
	Model* player = new Model(files, "player/steve.obj");
	Model* player2 = new Model(files, "player/alex.obj");
	Model* cloud = new Model(files, "clouds/cloud1.obj");
	Model* pig = new Model(files, "pig/Pig.obj");

	// pos nube
	float posCloud = 18.0f;
	float posCloud2 = 30.0f;
	float direc = 1.0f;
	float direc2 = -1.0f;

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

	std::vector<Chunk*> chunkSet;
	for (u32 x = 0; x < 2; x++)
		for (u32 z = 0; z < 2; z++)
			chunkSet.push_back(new Chunk(glm::vec2((f32)x, (f32)z), noise));

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

		for (u32 i = 0; i < chunkSet.size(); i++)
			chunkSet[i]->RenderChunk(shader, atlas, camera, REL_16_9);

		lsShader->useProgram();
		lsShader->setVec3("lightColor", light.color);
		lsShader->setF32("lightIntensity", light.intensity);
		testBlock->Render(lsShader, atlas, camera, REL_16_9);

		// Models
		shaderModel->use();
		shaderModel->setVec3("xyz", light.position);
		shaderModel->setVec3("xyzColor", light.color);
		shaderModel->setVec3("xyzView", camera.getPos());
		glm::mat4 proj = glm::perspective(camera.getFovAngle(), ASPECT, 0.1f, 100.0f);
		shaderModel->setMat4("proj", proj);
		shaderModel->setMat4("view", camera.getView());

		// Steve
		glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(16.0f, 28.5f, 16.0f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, 90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		shaderModel->setMat4("model", model);
		player->Draw(shaderModel);

		// Alex
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = translate(model2, glm::vec3(15.0f, 28.5f, 18.0f));
		model2 = glm::scale(model2, glm::vec3(0.05f));
		model2 = glm::rotate(model2, 90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		shaderModel->setMat4("model", model2);
		player2->Draw(shaderModel);

		// Nubes
		glm::mat4 model3 = glm::mat4(1.0f);
		glm::mat4 model3_2 = glm::mat4(1.0f);
		posCloud = posCloud + deltaTime * direc;
		posCloud2 = posCloud2 + deltaTime * direc2;
		if (posCloud >= 40.0f || posCloud <= 0.0f) {
			direc *= -1;
		}
		if (posCloud2 >= 40.0f || posCloud2 <= 0.0f) {
			direc2 *= -1;
		}
		model3 = translate(model3, glm::vec3(15.0f, 40.0f, posCloud));
		model3 = glm::scale(model3, glm::vec3(0.05f));
		shaderModel->setMat4("model", model3);
		cloud->Draw(shaderModel);
		model3_2 = translate(model3_2, glm::vec3(10.0f, 40.0f, posCloud2));
		model3_2 = glm::scale(model3_2, glm::vec3(0.05f));
		shaderModel->setMat4("model", model3_2);
		cloud->Draw(shaderModel);

		// Animal
		glm::mat4 model4 = glm::mat4(1.0f);
		model4 = translate(model4, glm::vec3(12.0f, 28.5f, 17.0f));
		model4 = glm::scale(model4, glm::vec3(0.2f));
		shaderModel->setMat4("model", model4);
		pig->Draw(shaderModel);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;
	delete testBlock;

	return 0;
}