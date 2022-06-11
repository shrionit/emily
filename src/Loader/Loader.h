/*
 * Loader.h
 *
 *  Created on: 03-Jun-2022
 *      Author: shripc
 */

#ifndef LOADER_H
#define LOADER_H
#include "glad\glad.h"
#include "TextureLoader.h"
#include <vector>
#include <iostream>
#include "..\Entity\Entity.h"
#include "VAO.h"
#pragma once
using namespace EMILY;
class Loader {
	public:
		static VAO loadRawMode(RawData<float> vertices, RawData<float> texCoords, RawData<GLuint> indices, int vertexDim=3){
			VAO vao;
			loadToVBO(vertices.data, vertices.size);
			vao.bindToVertexAttribLocation(0, vertexDim);
			loadToVBO(texCoords.data, texCoords.size);
			vao.bindToVertexAttribLocation(1, 2);
			loadToIBO(indices.data, indices.size);
			vao.setHasIndices(true);
			vao.setIndicesCount(indices.size/sizeof(int));
			vao.setVertexCount(vertices.size/(sizeof(float)*vertexDim));
			vao.unBind();
			return vao;
		}
		static Entity loadRawModeToEntity(Texture& texture, RawData<float> vertices, RawData<float> texCoords, RawData<GLuint> indices, int vertexDim=3){
			VAO vao;
			loadToVBO(vertices.data, vertices.size);
			vao.bindToVertexAttribLocation(0, vertexDim);
			loadToVBO(texCoords.data, texCoords.size);
			vao.bindToVertexAttribLocation(1, 2);
			loadToIBO(indices.data, indices.size);
			vao.setHasIndices(true);
			vao.setIndicesCount(indices.size/sizeof(int));
			vao.setVertexCount(vertices.size/(sizeof(float)*vertexDim));
			vao.unBind();

			return Entity(vao, texture);
		}
		static void loadToVBO(const float data[], std::size_t n){
			GLuint id;
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, n, data, GL_STATIC_DRAW);
		}

		template<typename T>
		static void loadToVBO(std::vector<T> data){
			GLuint id;
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(T), &data[0], GL_STATIC_DRAW);
		}

		static void loadToIBO(const GLuint data[], std::size_t n){
			GLuint id;
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, data, GL_STATIC_DRAW);
		}

		static void loadToIBO(std::vector<GLuint> data){
			GLuint id;
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size()*sizeof(GLuint), &data[0], GL_STATIC_DRAW);
		}

		static GLuint createVAO(){
			GLuint id;
			glGenVertexArrays(1, &id);
			glBindVertexArray(id);
			return id;
		}

		static void bindToVertexAttribLocation(int loc, int dim){
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, dim, GL_FLOAT, GL_FALSE, dim * sizeof(float), (void*)0);
		}

		static void bindToVertexAttribLocation(int loc, int dim, int size, const GLvoid *stride=(void*)0){
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, dim, GL_FLOAT, GL_FALSE, size, stride);
		}
};


#endif
