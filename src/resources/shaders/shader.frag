#version 330 core
// Inputs from the Vertex Shader
in vec3 fragPos;
in vec3 fragColor;
in vec3 fragNormal;
in vec2 fragUVs;

// This will contain the texture info to use. (Only ONE texture needef at the moment)
uniform sampler2D atlas;

// Other uniforms
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightStrenght;

// Final color as output
out vec4 finalColor;

void main() {
	vec3 ambient = lightStrenght * lightColor;

	vec3 normal = normalize(fragNormal);
	vec3 lightDirection = normalize(lightPos - fragPos);
	float diff          = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse        = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(1.0f);

	finalColor = texture(atlas, fragUVs) * vec4(result, 1.0f);
}