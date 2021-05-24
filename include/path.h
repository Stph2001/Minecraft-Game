#pragma once

#ifndef _PATH_
#define _PATH_

class Path {
	std::string shaderPath;
	std::string texturePath;
public:
	Path(
		std::string shaderPath = "resources/shaders",
		std::string texturePath = "resources/textures"
	) : shaderPath(shaderPath), texturePath(texturePath) {}

	std::string shader(const std::string& name) { return shaderPath + "/" + name; }
	std::string texture(const std::string& name) { return texturePath + "/" + name; }
};

#endif