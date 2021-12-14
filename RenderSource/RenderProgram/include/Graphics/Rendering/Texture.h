#ifndef TEXTURE_H
#define TEXTURE_H

#include "iostream"
#include "STB/stb_image.h"
#include "GLAD/glad.h"

class Texture {
public:

	Texture();
	Texture(const char* path, const char* name, bool defaultParameters = true);

	void Generate();
	void Load(bool flip = true);

	void SetFilters(GLenum all);
	void SetFilters(GLenum mag, GLenum min);

	void SetWrap(GLenum all);
	void SetWrap(GLenum s, GLenum t);

	void Bind();

	//texture object
	int id;
	unsigned int tex;
	const char* name;
private:
	static int currentId;
	const char* path;
	int width;
	int height;
	int nChannels;
};

#endif