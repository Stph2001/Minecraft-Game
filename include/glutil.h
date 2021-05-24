#pragma once

#ifndef _GLUTILS_
#define _GLUTILS_

// ************
// *  Macros  *
// ************
// Aspect Ratios
#define REL_3_2    3.0f /  2.0f
#define REL_4_3    4.0f /  3.0f
#define REL_5_4    5.0f /  4.0f
#define REL_14_9   5.0f /  4.0f
#define REL_16_9  16.0f /  9.0f
#define REL_16_10 16.0f / 10.0f
#define REL_17_9  17.0f /  9.0f
#define REL_21_9  21.0f /  9.0f
#define REL_12_5  12.0f /  5.0f
#define REL_23_9  23.0f /  9.0f
#define REL_13_5  13.0f /  5.0f
#define REL_8_3    8.0f /  3.0f
#define REL_11_4  11.0f /  4.0f
#define REL_4_1    4.0f /  1.0f
#define REL_12_1  12.0f /  1.0f

// **************
// *  Typedefs  *
// **************
typedef float  f32;
typedef double f64;

typedef char      i8;
typedef short int i16;
typedef int       i32;
typedef long long i64;

typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// ***************
// *  Libraries  *
// ***************
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

// Standard
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>

// Custom
#include <path.h>
#include <vao.h>      // Contains vbo.h
#include <ebo.h>
#include <camera.h>
#include <shader.h>
#include <texture.h>
#include <mesh.h>     // Unfinished

// **********************
// *  Global variables  *
// **********************
const u32 SCR_WIDTH = 1366;
const u32 SCR_HEIGHT = 768;
const u32 WND_WIDTH = 800;
const u32 WND_HEIGHT = 600;

const u32 FSIZE = sizeof(f32);
const u32 ISIZE = sizeof(i32);
const f32 ASPECT = (f32)WND_WIDTH / (f32)WND_HEIGHT;

bool firstMouse = true;
f32 lastX = WND_WIDTH / 2.0f;
f32 lastY = WND_HEIGHT / 2.0f;

f32 deltaTime = 0.0f;
f32 lastFrame = 0.0f;

// ***************
// *  Functions  *
// ***************
void FramebufferSizeCallback(GLFWwindow*, i32 width, i32 height) { glViewport(0, 0, width, height); }

// Window initialization
GLFWwindow* glutilInit(
	i32 major, i32 minor,
	i32 width, i32 height,
	const i8* title,
	i32 screenWidth = 1366,
	i32 screenHeight = 768
) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetWindowPos(window, screenWidth / 2 - width / 2, screenHeight / 2 - height / 2);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW Window\n";
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Not GLAD at all!\n";
		return nullptr;
	}

	return window;
}

#endif