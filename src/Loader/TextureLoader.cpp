#include "TextureLoader.h"
#include "..\stb.h"
using namespace EMILY;
TextureLoader::TextureLoader(){}
TextureLoader::~TextureLoader(){}

GLuint genEmptyTex(GLuint &texture){
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//Setting texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texture;
}

Texture TextureLoader::load(const char* textureFileName, GLuint texN){
    GLuint texture;
    genEmptyTex(texture);
    //load and generate the texture
    int width, height, nrChannels;
    const char* filePath = textureFileName;
    std::cout << "FilePath: " << filePath << std::endl;
    unsigned char* data;
    try {
        data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);
    return Texture(texture, texN, width, height, nrChannels);
}

GLuint TextureLoader::loadFromData(unsigned char *pixels, int w, int h, int components){
	GLuint textureID;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, components, w, h, 0, (components==3)?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	return textureID;
}
