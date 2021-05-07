#version 330 core
in vec3 fragColor;
in vec2 fragUVs;

out vec4 finalColor;

uniform sampler2D texture0;

void main() {
	finalColor = texture(texture0, fragUVs) * vec4(fragColor, 1.0f);
}
