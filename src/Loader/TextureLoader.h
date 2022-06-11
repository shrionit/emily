#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <iostream>
#include <string>
#include "glad\glad.h"
#pragma once

namespace EMILY {
        class Texture {
            public:
                GLuint ID;
                std::string type;
                std::string path;
                GLenum activeTexture;
                int width;
                int height;
                int nrChannels;
                Texture(){
                	ID = 0;
                	activeTexture = GL_TEXTURE0;
                	width = 0;
                	height = 0;
                	nrChannels = 0;
                }
                Texture(GLuint id, GLenum activeTextureNumber, int textureW, int textureH, int nrChannel){
                    ID = id;
                    activeTexture = activeTextureNumber;
                    width = textureW;
                    height = textureH;
                    nrChannels = nrChannel;
                };
                void bind(){
                    glActiveTexture(activeTexture);
                    glBindTexture(GL_TEXTURE_2D, ID);
                }
                void unbind(){
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
        };

        class TextureLoader {
            public:
                TextureLoader();
                ~TextureLoader();
                static Texture load(const char* textureFileName, GLuint texN=GL_TEXTURE0);
                static GLuint loadFromData(unsigned char *pixels, int w, int h, int components);

            private:
                static const std::string TEXBASEPATH;

        };
}

#endif
