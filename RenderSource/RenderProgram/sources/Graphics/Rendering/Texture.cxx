#include "Graphics/Rendering/Texture.h"

int Texture::currentId = 0;

Texture::Texture()
{
}

Texture::Texture(const char* path, const char* name, bool defaultParameters)
	: path(path), name(name), id(currentId++)
{
	Generate();

	if (defaultParameters)
	{
		SetFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		SetWrap(GL_REPEAT);
	}
}

void Texture::Generate()
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::Load(bool flip)
{
	stbi_set_flip_vertically_on_load(flip);

	unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);

	GLenum colorMode = GL_RGB;

	switch (nChannels)
	{
	case 1:
		colorMode = GL_RED;
		break;
	case 2:
		colorMode = GL_RG;
		break;
	case 3:
		colorMode = GL_RGB;
		break;
	case 4:
		colorMode = GL_RGBA;
		break;
	}

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Image not loaded at " << path << std::endl;
	}

	stbi_image_free(data);
}

void Texture::SetFilters(GLenum all)
{
	SetFilters(all, all);
}

void Texture::SetFilters(GLenum mag, GLenum min)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void Texture::SetWrap(GLenum all)
{
	SetWrap(all, all);
}

void Texture::SetWrap(GLenum s, GLenum t)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
