#version 330 core
out vec4 fragColor;

uniform vec3 lightColor;
uniform float lightIntensity;

uniform sampler2D atlas;

void main() {
	fragColor = lightIntensity * vec4(lightColor, 1.0f);
}