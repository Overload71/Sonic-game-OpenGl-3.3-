#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"GraphicsDevice\ShaderProgram.h"
class GameObject
{

	glm::vec3 mDirection;
	glm::vec3 mPosition;
	float mDirectionAngle;
	bool isDestroyed;
protected:
	glm::mat4 mModelMatrix;
	glm::mat4 minitialTransformation;
public:
	void setDirection(glm::vec3 fDirection);
	glm::vec3 getDirection();
	void setPosition(glm::vec3 fPosition);
	glm::vec3 getPosition();
	void UpdateModelMatrix();
	GameObject();
	GameObject(glm::vec3 fPosition,glm::vec3 fDirection,bool fIsDestroyed);
	~GameObject();
};

