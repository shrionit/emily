/*
 * FrameBuffer.h
 *
 *  Created on: 04-Jun-2022
 *      Author: shripc
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "glad\glad.h"
#include "DisplayManager.h"
#include <iostream>
#include <vector>
#pragma once

class FrameBuffer {
	public:
		GLuint fboID = 0;
		GLuint dboID = 0;
		Window window;
		GLuint textureID = 0;
		GLuint depthTextureID = 0;
		FrameBuffer(Window &window){
			initFrameBuffer();
			fbos.push_back(fboID);
			this->window = window;
		}
		void bind(){
			glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
			glBindFramebuffer(GL_FRAMEBUFFER, fboID);
			glViewport(0, 0, window.width, window.height);
		}
		void unBind(){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void init(){
			bind();
			initFrameBufferTextureAttachment();
			initDepthBufferAttachment();
			initDepthTextureAttachment();
			unBind();
		}
		static void cleanUp(){
			for(auto fbo : fbos){
				glDeleteFramebuffers(1, &fbo);
			}
		}
	private:
		void initFrameBufferTextureAttachment(){
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
		}
		void initDepthTextureAttachment() {
			glGenTextures(1, &depthTextureID);
			glBindTexture(GL_TEXTURE_2D, depthTextureID);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, window.width, window.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureID, 0);
		}
		void initDepthBufferAttachment(){
			glGenRenderbuffers(1, &dboID);
			glBindRenderbuffer(GL_RENDERBUFFER, dboID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, window.width, window.height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dboID);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		void initFrameBuffer() {
			glGenFramebuffers(1, &fboID);
			glBindFramebuffer(GL_FRAMEBUFFER, fboID);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
		}
		static std::vector<GLuint> fbos;
};
std::vector<GLuint> FrameBuffer::fbos;

#endif
