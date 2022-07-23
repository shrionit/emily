#include "Entity.h"

namespace EMILY {
	GLuint Entity::count = 0;

	Entity::Entity(const char* modelPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale){
		ID = uuid::v4();
		this->model = Model(modelPath);
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->drawMode = GL_FILL;
		this->hasModel = true;
		setLabel();
	}

	Entity::Entity(VAO& vao, Texture& texture) {
		ID = uuid::v4();
		this->vao = vao;
		this->texture = texture;
		this->position = glm::vec3(0);
		this->rotation = glm::vec3(0);
		this->scale = glm::vec3(1);
		this->drawMode = GL_FILL;
		setLabel();
	}

	Entity::Entity(VAO& vao, Texture& texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale){
		ID = uuid::v4();
		this->vao = vao;
		this->texture = texture;
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->drawMode = GL_FILL;
		setLabel();
	}

	void Entity::bind(){
		if(!hasModel) vao.bind();
	}

	void Entity::unBind(){
		if(!hasModel) vao.unBind();
	}

	void Entity::render(){
		shader.use();
		shader.setMat4("model", GMath::transformationMatrix(position, rotation, scale));
		if(isVisible()){
			glPolygonMode(GL_FRONT_AND_BACK, getDrawMode());
			if(hasModel){
				model.Draw(shader);
			}else{
				texture.bind();
				if(vao.getHasIndices()){
					glDrawElements(GL_TRIANGLES, vao.getIndicesCount(), GL_UNSIGNED_INT, 0);
				}else{
					glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
				}
			}
		}
	}

	void Entity::render(Shader& s){
		s.use();
		s.setMat4("model", GMath::transformationMatrix(position, rotation, scale));
		if(isVisible()){
			glPolygonMode(GL_FRONT_AND_BACK, getDrawMode());
			if(hasModel){
				model.Draw(shader);
			}else{
				texture.bind();
				if(vao.getHasIndices()){
					glDrawElements(GL_TRIANGLES, vao.getIndicesCount(), GL_UNSIGNED_INT, 0);
				}else{
					glDrawArrays(GL_TRIANGLES, 0, vao.getVertexCount());
				}
			}
		}
	}

	const glm::vec3& Entity::getPosition() const {
		return position;
	}

	void Entity::setPosition(const glm::vec3 &position) {
		this->position = position;
	}

	const glm::vec3& Entity::getRotation() const {
		return rotation;
	}

	void Entity::setRotation(const glm::vec3 &rotation) {
		this->rotation = rotation;
	}

	const glm::vec3& Entity::getScale() const {
		return scale;
	}

	void Entity::setScale(const glm::vec3 &scale) {
		this->scale = scale;
	}

	const Shader& Entity::getShader() const {
		return shader;
	}

	void Entity::setShader(const Shader &shader) {
		this->shader = shader;
	}

	const Texture& Entity::getTexture() const {
		return texture;
	}

	void Entity::setTexture(const Texture &texture) {
		hasCustomTexture = true;
		this->texture = texture;
	}

	VAO Entity::getVao() const {
		return vao;
	}

	void Entity::setVao(VAO vao) {
		this->vao = vao;
	}

	bool Entity::isVisible() const {
		return visible;
	}

	void Entity::setVisible(bool visible) {
		this->visible = visible;
	}

	Entity::~Entity(){}

	GLuint Entity::getDrawMode() const {
		return drawMode;
	}

	void Entity::setDrawMode(GLuint dm) {
		this->drawMode = dm;
	}

	const Model& Entity::getModel() const {
		return model;
	}

	void Entity::setModel(const Model &model) {
		this->model = model;
	}

	void Entity::setLabel(std::string newLabel){
		if(newLabel == ""){
			label = string("Entity "+to_string(count));
			count++;
		}else{
			label = newLabel;
		}
	}

}
