#version 330 core
// Inputs from the Vertex Shader
in vec3 fragPos;
in vec3 fragColor;
in vec3 fragNormal;
in vec2 fragUVs;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightStrenght;

uniform vec3 ambientColor;
uniform float ambientStrenght;

uniform vec3 cameraPos;

uniform sampler2D atlas;

out vec4 color;

void main() {
	// Ambient
	vec3 ambient = ambientStrenght * ambientColor;

	// Diffuse
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specStrenght = 0.5f;
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
	vec3 specular = specStrenght * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) /** fragColor*/;
	color = texture(atlas, fragUVs) * vec4(result, 1.0f);
}