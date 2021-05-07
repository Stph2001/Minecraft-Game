#version 330 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 vertUV;

out vec3 fragColor;
out vec2 fragUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vertPos, 1.0f);
	fragColor = vertColor;
	fragUV = vertUV;
}
