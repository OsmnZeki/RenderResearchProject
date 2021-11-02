#include "Texture.h"

Texture::Texture(std::string imagePathString, const unsigned int& channelCount) {

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

    //TODO: opengl tutoriallerinde sadece 1 kez yazýlmýþtý araþtýr!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    imagePathS = imagePathString;
    const char* imagePath = imagePathS.c_str();
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &nChannels, 0);

    GLint format;
    switch (channelCount)
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    }

    if (imageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load image" << std::endl;
    }
    stbi_image_free(imageData);
}



