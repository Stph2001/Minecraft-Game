#ifndef __PATH_H__
#define __PATH_H__

#include <string>

class Path2 {
	std::string shadersPath;
	std::string texturesPath;
public:
	Path2(std::string shadersPath="bin",
		   std::string texturesPath="resources/textures")
		: shadersPath(shadersPath), texturesPath(texturesPath) {}
	std::string sp(const std::string& name) {
		std::string str = shadersPath + "/";
		str += name;
		return str;
	}
	std::string tp(const std::string& name) {
		std::string str = texturesPath + "/";
		str += name;
		return str;
	}
};

#endif
