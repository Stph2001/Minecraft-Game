#version 330 core
// Inputs from VAO::SetVertexAttribPointer function
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec3 vertNormal;
layout (location = 3) in vec2 vertUVs;

// Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Outputs
out vec3 fragPos;
out vec3 fragColor;
out vec3 fragNormal;
out vec2 fragUVs;

void main() {
	fragPos = vec3(model * vec4(vertPos, 1.0f));
	fragNormal = vertNormal;
	fragColor = vertColor;
	fragUVs = vertUVs;

	gl_Position = projection * view * vec4(fragPos, 1.0f);
}