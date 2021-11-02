#ifndef TEXTURE_H
#define TEXTURE_H

#include "iostream"
#include "STB/stb_image.h"
#include "glad.h"

class Texture {

public:
	unsigned int textureID;
	int width, height, nChannels;
	std::string imagePathS;

	Texture(std::string imagePathString, const unsigned int& channelCount);
};

#endif