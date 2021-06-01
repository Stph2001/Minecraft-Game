#pragma once

#ifndef _EVENTS_
#define _EVENTS_

bool wireframe_mode = false;

// ************
// *  Events  *
// ************
void processInput(GLFWwindow* window) {
	// ¿Terminar programa?
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Controlar velocidad de la cámara
	CameraSpeed speedFactor = CameraSpeed::NORMAL;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		speedFactor = CameraSpeed::FAST;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		speedFactor = CameraSpeed::SLOW;

	// Movimiento en los 3 ejes
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::FORWARD, deltaTime, speedFactor);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::LEFT, deltaTime, speedFactor);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::BACKWARD, deltaTime, speedFactor);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::RIGHT, deltaTime, speedFactor);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::UP, deltaTime, speedFactor);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		camera.ControlsKeyboard(CameraDirection::DOWN, deltaTime, speedFactor);

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		wireframe_mode = !wireframe_mode;

	if (wireframe_mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Evitar que el jugador se salga de los límites del mundo
	/*
	if (camera.position.x >= n - 1)
		camera.position.x = n - 1;
	if (camera.position.x <= 0)
		camera.position.x = 0;
	if (camera.position.z >= n - 1)
		camera.position.z = n - 1;
	if (camera.position.z <= 0)
		camera.position.z = 0;
	*/
}

// **********************
// *  OpenGL callbacks  *
// **********************
void MouseCallback(GLFWwindow* window, f64 xPos, f64 yPos) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (firstMouse) {
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
			return;
		}
		camera.ControlsMouse((f32)(xPos - lastX), (f32)(lastY - yPos));
		lastX = xPos;
		lastY = yPos;
	}
	else
		firstMouse = true;
}

void ScrollCallback(GLFWwindow*, f64 xOffset, f64 yOffset) { camera.ControlsWheel((f32)yOffset); }

void MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
	if (action == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (action == GLFW_RELEASE)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

#endif