/*
 * VAO.h
 *
 *  Created on: 04-Jun-2022
 *      Author: shripc
 */

#ifndef SRC_LOADER_VAO_H_
#define SRC_LOADER_VAO_H_

#include "glad\glad.h"
#include <iostream>

#pragma once

template<typename T>
struct RawData {
	T* data;
	std::size_t size;
};

struct VAO {
	GLuint ID;
	bool hasIndices = true;
	int indicesCount = 0;
	int vertexCount = 0;
	VAO(){
		glGenVertexArrays(1, &ID);
		glBindVertexArray(ID);
	}
	void setVertexCount(int value){
		vertexCount = value;
	}
	int getVertexCount(){
		return vertexCount;
	}
	void setHasIndices(bool value){
		hasIndices = value;
	}
	void setIndicesCount(int value){
		indicesCount = value;
	}
	bool getHasIndices(){
		return hasIndices;
	}
	int getIndicesCount(){
		return indicesCount;
	}
	void bind(){
		glBindVertexArray(ID);
	}
	void unBind(){
		glBindVertexArray(0);
	}
	void bindToVertexAttribLocation(int loc, int dim, int rowlength=3, int stride=0, GLuint dtype=GL_FLOAT, GLuint normalized=GL_FALSE){
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, dim, dtype, normalized, dim * sizeof(float), (void*)(stride * sizeof(float)));
	}
};


#endif
