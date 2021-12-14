#version 330 core

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;

};

#define MAX_POINT_LIGHTS 20
struct PointLight{
	vec3 position;
	float k0;
	float k1;
	float k2;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform int numbPointLights;

struct DirectionalLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionalLight directionalLight;

#define MAX_SPOT_LIGHTS 5
struct SpotLight{
	vec3 direction;
	vec3 position;
	
	float k0;
	float k1;
	float k2;
	float cutOff;
	float outerCutOff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight spotLight[MAX_SPOT_LIGHTS];
uniform int numbSpotLights;

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform Material material;

uniform vec3 viewPos;

vec3 CalcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcDirectionalLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main(){
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 diffMap = vec3(texture(material.diffuse, texCoord));
	vec3 specMap = vec3(texture(material.specular, texCoord));
	
	//placeholder
	vec3 result;
	
	result = CalcDirectionalLight(norm, viewDir, diffMap, specMap);
	
	for(int i = 0; i < numbPointLights; i++) {
	
		result += CalcPointLight(i, norm, viewDir, diffMap, specMap);
	}
	
	for(int i = 0; i < numbSpotLights; i++) {
	
		result += CalcSpotLight(i, norm, viewDir, diffMap, specMap);
	}
	
	
	FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){
	
	//ambient
	vec3 ambient = pointLight[idx].ambient * diffMap;
	
	//diffuse
	vec3 lightDir = normalize(pointLight[idx].position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLight[idx].diffuse * (diff * diffMap);	
	
	//specular
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess * 128);
	vec3 specular = pointLight[idx].specular * (spec * specMap);	
	
	float distance = length(pointLight[idx].position - fragPos);
	float attenuation= 1.0 / (pointLight[idx].k0 + pointLight[idx].k1 * distance + pointLight[idx].k2 * (distance * distance));
	return vec3(ambient + diffuse + specular) * attenuation;
}

vec3 CalcDirectionalLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){
	
	//ambient
	vec3 ambient = directionalLight.ambient * diffMap;
	
	//diffuse
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = directionalLight.diffuse * (diff * diffMap);	
	
	//specular
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess * 128);
	vec3 specular = directionalLight.specular * (spec * specMap);	
	
	return vec3(ambient + diffuse + specular);
}

vec3 CalcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){
	
	//ambient
	vec3 ambient = spotLight[idx].ambient * diffMap;
	
	//diffuse
	vec3 lightDir = normalize(spotLight[idx].position - fragPos);
	float theta = dot(lightDir, normalize(-spotLight[idx].direction));
	
	if(theta > spotLight[idx].outerCutOff) {
		
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = spotLight[idx].diffuse * (diff * diffMap);	
		
		vec3 reflectDir = reflect(-lightDir,norm);
		float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess * 128);
		vec3 specular = spotLight[idx].specular * (spec * specMap);
		
		float intensity = (theta - spotLight[idx].outerCutOff) / (spotLight[idx].cutOff - spotLight[idx].outerCutOff);
		intensity = clamp(intensity, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity; 
		
		float distance = length(spotLight[idx].position - fragPos);
		float attenuation= 1.0 / (spotLight[idx].k0 + spotLight[idx].k1 * distance + spotLight[idx].k2 * (distance * distance));
	
		return vec3(ambient + diffuse + specular) * attenuation;
	}
	else {
	
		return ambient;
	}
	
}