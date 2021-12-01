#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

};

struct Light{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

//uniform float mixVal;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main(){

	//FragColor = mix(texture(texture1,texCoord),texture(texture2,texCoord),mixVal);
	
	//ambient
	vec3 ambient = light.ambient * material.ambient;
	
	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);	
	
	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess * 128);
	vec3 specular = light.specular * (spec * material.specular);
	
	FragColor = vec4(vec3(ambient + diffuse + specular),1.0f);
}