#include <glutil.h>
#include <figures.h>
#include <camera.h>
#include <vbo.h>
#include <vao.h>
#include <ebo.h>
#include <FastNoiseLite.h>

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// FSIZE -> Numero de bytes de float
// ISIZE -> Numero de bytes de int
const unsigned int FSIZE = sizeof(float);
const unsigned int ISIZE = sizeof(int);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const float ASPECT = (float)SCR_WIDTH / (float)SCR_HEIGHT;

// Aun no se ha movido el mouse
bool firstMouse = true;

// Punto medio
float lastx = SCR_WIDTH / 2.0f;
float lasty = SCR_HEIGHT / 2.0f;

// Tiempos
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Inicializar clase camara
Cam* camera = new Cam();

// Input de teclado
void processInput(GLFWwindow* window, float n) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboard(FORWARD, deltaTime * 2);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->processKeyboard(RIGHT, deltaTime);
	}
	/*if ((camera->getPos().y < 1.5f || camera->getPos().y > 1.5f)) {
		camera->setPos(camera->getPos().x, 1.5f, camera->getPos().z);
	}*/
	if (camera->getPos().x >= n - 1) {
		camera->setPos(n - 1, camera->getPos().y, camera->getPos().z);
	}
	if (camera->getPos().x <= 0) {
		camera->setPos(0, camera->getPos().y, camera->getPos().z);
	}
	if (camera->getPos().z >= n - 1) {
		camera->setPos(camera->getPos().x, camera->getPos().y, n - 1);
	}
	if (camera->getPos().z <= 0) {
		camera->setPos(camera->getPos().x, camera->getPos().y, 0);
	}
}

// Movimiento de camara con mouse
void mouse_callback(GLFWwindow*, double xpos, double ypos) {
	if (firstMouse) {
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos;

	camera->processMouse(xoffset, yoffset);
}

// Zoom con Mouse
void scroll_callback(GLFWwindow*, double, double yoffset) {
	camera->processScroll(yoffset);
}

vector<glm::vec3> Wall(vector<glm::vec3> positions, i32 fila, i32 columna, char c, f32 t, f32 inicio) {
	f32 x, y, z, l;
	l = inicio;

	for (int i = 1; i < fila + 1; ++i) {
		for (int j = 0; j < columna; ++j) {

			if (c == 'f') {
				z = t;
				x = l + j;
			}
			else
			{
				x = t;
				z = l + j;
			}
			y = i;
			positions.push_back(glm::vec3(x, y, z));
		}
	}
	return positions;
}

int main() {
	// Inicializar OpenGL (Version, version, Ancho, Altura, Titulo)
	GLFWwindow* window = glutilInit(4, 4, SCR_WIDTH, SCR_HEIGHT, "Lo lograste crack?");

	// Insertar funciones de movimiento de mouse y zoom
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Crear shaders (Ruta actual, Ruta recursos, Ruta vertex, Ruta fragment)
	Shader* shader = new Shader("D:/Users/steph/Documents/UPC Ciclo 5/Computación Gráfica/Proyecto Minecraft/Minecraft/Minecraft");
	Shader* shaderHouse = new Shader("D:/Users/steph/Documents/UPC Ciclo 5/Computación Gráfica/Proyecto Minecraft/Minecraft/Minecraft");

	// Inicializar Cubo o Cualquier figura q quieras
	Cube* cubex = new Cube();

	// Inicializar función noise
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// Crear posiciones pa el terreno
	int n = 64;
	vector<glm::vec3> positions;
	for (int x = 0; x < n; ++x) {
		for (int z = 0; z < n; ++z) {
			positions.push_back(glm::vec3(x, int(noise.GetNoise((float)x, (float)z) * 2), z));
		}
	}

	//Parametro Pared(positions, numero de filas, numero de columnas, frontal(f) ó paralela(p), pos X, pos Z);
	vector<glm::vec3> positions2;
	positions2 = Wall(positions2, 5, 4, 'f', 10, 11);
	positions2 = Wall(positions2, 5, 6, 'p', 10, 10);
	positions2 = Wall(positions2, 5, 6, 'p', 15, 10);

	// Creacion del objeto 
	VAO vao;
	VBO vbo(cubex->getVSize() * FSIZE, cubex->getVertices());
	EBO ebo(cubex->getISize() * ISIZE, cubex->getIndices());

	vao.SetVertexAttribPointer(0, 3, 8 * FSIZE, 0);
	vao.SetVertexAttribPointer(1, 3, 8 * FSIZE, 3 * FSIZE);
	vao.SetVertexAttribPointer(2, 2, 8 * FSIZE, 6 * FSIZE);

	VAO vaoHouse;
	VBO vbo2(cubex->getVSize() * FSIZE, cubex->getVertices());
	EBO ebo2(cubex->getISize() * ISIZE, cubex->getIndices());

	vaoHouse.SetVertexAttribPointer(0, 3, 8 * FSIZE, 0);
	vaoHouse.SetVertexAttribPointer(1, 3, 8 * FSIZE, 3 * FSIZE);
	vaoHouse.SetVertexAttribPointer(2, 2, 8 * FSIZE, 6 * FSIZE);

	// Cargar texturas
	int texture = shader->loadTexture("grass.jpg");
	int texture2 = shader->loadTexture("water.jpg");
	int texture3 = shader->loadTexture("sand.jpg");
	int textureHouse = shaderHouse->loadTexture("rock.jpg");

	// Depth buffer para renderizar 
	glEnable(GL_DEPTH_TEST);

	// Transcurso de la aplicaciÃ³n hasta que se cierre
	while (!glfwWindowShouldClose(window)) {
		// Tiempo actual
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Aparecer textura
		glBindTexture(GL_TEXTURE_2D, texture);

		// Iniciar ventana de la aplicaciÃ³n, con color de fondo
		processInput(window, (float)n);
		glClearColor(0.0f, 1.0f, 1.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iniciar shader con propiedades
		shader->useProgram();

		// Proyeccion: perspective(getZoom, ASPECT, camara cerca, camara lejana)
		glm::mat4 projection = glm::perspective(camera->getZoom(), ASPECT, 0.1f, 100.0f);
		shader->setMat4("proj", projection);

		// Vista: getView
		glm::mat4 view = glm::mat4(1.0f);
		view = camera->getViewM4();
		shader->setMat4("view", view);

		// Aparecer objeto (vao)
		vao.Bind();

		// Model: translate y rotation
		// translate -> posicion
		// rotation -> rotacion
		for (unsigned int i = 0; i < positions.size(); ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, positions[i]);
			if (i > 3500) {
				glBindTexture(GL_TEXTURE_2D, texture2);
			}
			if (i <= 3500 && i > 3300) {
				glBindTexture(GL_TEXTURE_2D, texture3);
			}

			shader->setMat4("model", model);
			// Dibujar(forma, Nro de puntos, GL_UNSIGNED_INT, 0)
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		}

		glBindTexture(GL_TEXTURE_2D, textureHouse);

		shaderHouse->useProgram();

		vaoHouse.Bind();

		shaderHouse->setMat4("proj", projection);
		shaderHouse->setMat4("view", view);
		for (int i = 0; i < positions2.size(); ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, positions2[i]);
			shaderHouse->setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;
	delete cubex;
	delete camera;

	return 0;
}