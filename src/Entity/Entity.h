/*
 * Entity.h
 *
 *  Created on: 03-Jun-2022
 *      Author: shripc
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "glm\glm.hpp"
#include "glm\vec4.hpp"
#include <string>
#include "..\Shader\Shader.h"
#include "..\Utils\GMath.h"
#include "..\Utils\UUID.h"
#include "..\Loader\TextureLoader.h"
#include "..\Loader\VAO.h"
#include "Model.h"

#pragma once

namespace EMILY {

	class Entity {
		public:
			Entity() : ID(uuid::v4()){}
			Entity(const char* modelPath, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
			Entity(VAO &vao, Texture& texture);
			Entity(VAO &vao, Texture& texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
			void bind();
			void unBind();
			void render();
			void render(Shader& shader);
			const glm::vec3& getPosition() const;
			void setPosition(const glm::vec3 &position);
			const glm::vec3& getRotation() const;
			void setRotation(const glm::vec3 &rotation);
			const glm::vec3& getScale() const;
			void setScale(const glm::vec3 &scale);
			const Shader& getShader() const;
			void setShader(const Shader &shader);
			const Texture& getTexture() const;
			void setTexture(const Texture &texture);

			VAO getVao() const;
			void setVao(VAO vao);
			bool isVisible() const;
			void setVisible(bool visible);
			GLuint getDrawMode() const;
			void setDrawMode(GLuint dm);
			const Model& getModel() const;
			void setModel(const Model &model);
			const std::string& getID(){
				return ID;
			}

			void setLabel(std::string newLabel="");

			std::string getLabel(){
				return label;
			}

			~Entity();
		private:
			static GLuint count;
			std::string ID;
			std::string label;
			VAO vao;
			Model model;
			bool hasModel = false;
			bool hasCustomTexture = false;
			bool visible = true;
			GLuint drawMode;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			Shader shader;
			Texture texture;
	};

}

#endif
