#include "GameObject.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
GameObject::GameObject()
{
	mPosition = glm::vec3(0.0f, 0.0f, 48.0f);
	mDirection = glm::vec3(1.0f,0.0f,0.0f);
	mDirectionAngle = 0;
	mModelMatrix = glm::mat4(1);
	isDestroyed = false;
}
GameObject::GameObject(glm::vec3 fPosition, glm::vec3 fDirection, bool fIsDestroyed)
{
	mPosition = fPosition;
	mDirection = fDirection;
	isDestroyed = fIsDestroyed;
	mDirectionAngle = atan2(mDirection.z,mDirection.x);
	UpdateModelMatrix();
}
GameObject::~GameObject()
{
}
void GameObject::setDirection(glm::vec3 fDirection)
{
	mDirection = fDirection;
	mDirectionAngle = atan2(mDirection.z , mDirection.x) * 180.0 / 3.14159265359;
}
glm::vec3 GameObject::getDirection()
{
	return mDirection;
}
void GameObject::setPosition(glm::vec3 fPosition)
{
	mPosition = fPosition;
}

glm::vec3 GameObject::getPosition()
{
	return mPosition;
}
void GameObject::UpdateModelMatrix()
{
	mModelMatrix =glm::translate(mPosition)* glm::rotate(mDirectionAngle,0.0f,1.0f,0.0f) * minitialTransformation;
}