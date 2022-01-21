#include "Graphics/Rendering/Material.h"

// data obtained from http://devernay.free.fr/cours/opengl/materials.html

/*
    static instances of common materials
*/

LitMaterial LitMaterial::emerald = { glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6 };
LitMaterial LitMaterial::jade = { glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1 };
LitMaterial LitMaterial::obsidian = { glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3 };
LitMaterial LitMaterial::pearl = { glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088 };
LitMaterial LitMaterial::ruby = { glm::vec3(0.1745, 0.01175, 0.01175), glm::vec3(0.61424, 0.04136, 0.04136), glm::vec3(0.727811, 0.626959, 0.626959), 0.6 };
LitMaterial LitMaterial::turquoise = { glm::vec3(0.1, 0.18725, 0.1745), glm::vec3(0.396, 0.74151, 0.69102), glm::vec3(0.297254, 0.30829, 0.306678), 0.1 };
LitMaterial LitMaterial::brass = { glm::vec3(0.329412, 0.223529, 0.027451), glm::vec3(0.780392, 0.568627, 0.113725), glm::vec3(0.992157, 0.941176, 0.807843), 0.21794872 };
LitMaterial LitMaterial::bronze = { glm::vec3(0.2125, 0.1275, 0.054), glm::vec3(0.714, 0.4284, 0.18144), glm::vec3(0.393548, 0.271906, 0.166721), 0.2 };
LitMaterial LitMaterial::chrome = { glm::vec3(0.25, 0.25, 0.25), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.774597, 0.774597, 0.774597), 0.6 };
LitMaterial LitMaterial::copper = { glm::vec3(0.19125, 0.0735, 0.0225), glm::vec3(0.7038, 0.27048, 0.0828), glm::vec3(0.256777, 0.137622, 0.086014), 0.1 };
LitMaterial LitMaterial::gold = { glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 0.4 };
LitMaterial LitMaterial::silver = { glm::vec3(0.19225, 0.19225, 0.19225), glm::vec3(0.50754, 0.50754, 0.50754), glm::vec3(0.508273, 0.508273, 0.508273), 0.4 };
LitMaterial LitMaterial::black_plastic = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.50, 0.50, 0.50), .25 };
LitMaterial LitMaterial::cyan_plastic = { glm::vec3(0.0, 0.1, 0.06), glm::vec3(0.0, 0.50980392, 0.50980392), glm::vec3(0.50196078, 0.50196078, 0.50196078), .25 };
LitMaterial LitMaterial::green_plastic = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 0.35, 0.1), glm::vec3(0.45, 0.55, 0.45), .25 };
LitMaterial LitMaterial::red_plastic = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.5, 0.0, 0.0), glm::vec3(0.7, 0.6, 0.6), .25 };
LitMaterial LitMaterial::white_plastic = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.55, 0.55, 0.55), glm::vec3(0.70, 0.70, 0.70), .25 };
LitMaterial LitMaterial::yellow_plastic = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.60, 0.60, 0.50), .25 };
LitMaterial LitMaterial::black_rubber = { glm::vec3(0.02, 0.02, 0.02), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.4, 0.4, 0.4), .078125 };
LitMaterial LitMaterial::cyan_rubber = { glm::vec3(0.0, 0.05, 0.05), glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.04, 0.7, 0.7), .078125 };
LitMaterial LitMaterial::green_rubber = { glm::vec3(0.0, 0.05, 0.0), glm::vec3(0.4, 0.5, 0.4), glm::vec3(0.04, 0.7, 0.04), .078125 };
LitMaterial LitMaterial::red_rubber = { glm::vec3(0.05, 0.0, 0.0), glm::vec3(0.5, 0.4, 0.4), glm::vec3(0.7, 0.04, 0.04), .078125 };
LitMaterial LitMaterial::white_rubber = { glm::vec3(0.05, 0.05, 0.05), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 0.7), .078125 };
LitMaterial LitMaterial::yellow_rubber = { glm::vec3(0.05, 0.05, 0.0), glm::vec3(0.5, 0.5, 0.4), glm::vec3(0.7, 0.7, 0.04), .078125 };



LitMaterial::LitMaterial()
{
}

LitMaterial::LitMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) 
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

void LitMaterial::ConfigurationShader()
{
	shader.SetFloat("material.shininess", 0.5f);
	if (textures.size() == 0) {
		// materials
		shader.Set4Float("material.diffuse", glm::vec4(diffuse, 1));
		shader.Set4Float("material.specular", glm::vec4(specular, 1));
		shader.SetInt("noTex", 1);
	}
	else {
		// textures
		unsigned int diffuseIdx = 0;
		unsigned int specularIdx = 0;

		for (unsigned int i = 0; i < textures.size(); i++) {
			// activate texture
			glActiveTexture(GL_TEXTURE0 + i);

			// retrieve texture info
			std::string name;
			switch (textures[i].type)
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuseIdx++);
				break;
			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specularIdx++);
				break;
			}

			// set the shader value
			shader.SetInt(name, i);
			// bind texture
			textures[i].Bind();
		}
	}
}


// function to mix two materials with a proportion
LitMaterial LitMaterial::mix(LitMaterial m1, LitMaterial m2, float mix) {
    return {
        // set lighting values based on proportion
        m1.ambient * mix + m2.ambient * (1 - mix),
        m1.diffuse * mix + m2.diffuse * (1 - mix),
        m1.specular * mix + m2.specular * (1 - mix),
        m1.shininess * mix + m2.shininess * (1 - mix)
    };
}