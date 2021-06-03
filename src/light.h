#pragma once

#ifndef _LIGHTS_
#define _LIGHTS_

struct Light {
	Light(glm::vec3 color, f32 intensity) : color(color), intensity(intensity) {}

	glm::vec3 color;
	f32 intensity;
};

struct AmbientLight : public Light {
	AmbientLight(glm::vec3 color, f32 intensity) : Light(color, intensity) {}
};

struct OmniLight : public Light {
	OmniLight(glm::vec3 position, glm::vec3 color, f32 intensity) : position(position), Light(color, intensity) {}

	glm::vec3 position;
};

#endif