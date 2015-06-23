#include "Hero.h"
#include<iostream>

Hero::Hero(KeyFrameAnimationShader *fShader) : GameObject()
{
	mShader = fShader;
	initialize();
}

Hero::Hero(KeyFrameAnimationShader *fShader,glm::vec3 fPosition, glm::vec3 fDirection, bool fIsDestroyed) : GameObject(fPosition, fDirection, fIsDestroyed)
{
	mShader = fShader;
	initialize();
	auto tempBoundingBox = CMD2Model::GetBoundingBox();
	tempBoundingBox.Translate(fPosition);
}

Hero::~Hero()
{
}
void Hero::UpdataAnimation(float deltatime)
{
	
	if (isAnimationFinished == true && animationState.type != animType_t::STAND)
	{
		animationState = CMD2Model::StartAnimation(animType_t::STAND);
	}
	CMD2Model::UpdateAnimation(&animationState, deltatime);
}
void Hero::initialize()
{
	objectType = CollidableModel::ObjectType::MD2Model;
	CMD2Model::LoadModel("data/models/SONIC/PLAY.md2");
	animationState = this->StartAnimation(animType_t::STAND);
	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	minitialTransformation = glm::rotate(-90.0f, 1.0f, 0.0f, 0.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	auto tempBoundingBox = CMD2Model::GetBoundingBox();
	tempBoundingBox.Scale(0.01f, 0.01f, 0.01f);
	tempBoundingBox.Rotate(-90.0f, 1.0f, 0.0f, 0.0f);
	CMD2Model::SetBoundingBox(tempBoundingBox);
	UpdateModelMatrix();
	initialCamera = glm::vec3(0.0f,1.0f,2.0f);
	camera = std::unique_ptr<ThirdPersonCamera>(new ThirdPersonCamera());
	auto position = GameObject::getPosition();
	camera->Reset(position+initialCamera,position,glm::vec3(0.0f,1.0f,0.0f));
	camera->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 200.0f);
}
void Hero::Render(glm::mat4 VP)
{
	mShader->UseProgram();
	mShader->BindVPMatrix(&VP[0][0]);
	mShader->BindModelMatrix(&mModelMatrix[0][0]);
	CMD2Model::RenderModel(&animationState,mShader);
}
void Hero::Collided(ObjectType fType)
{
	/*if(fType == ObjectType::Model3D)
	std::cout << "LOL" << std::endl;*/
}
void Hero::Move(glm::vec3 fDirection)
{
	//float stepSize = 0.05;
	//auto oldDirection = GameObject::getDirection();
	
	auto tempPostion = GameObject::getPosition();
	tempPostion = tempPostion + fDirection;
	GameObject::setPosition(tempPostion);
	fDirection.z *= -1;
	fDirection = glm::normalize(fDirection);
	GameObject::setDirection(fDirection);
	GameObject::UpdateModelMatrix();
	auto newBoundryBox = CollidableModel::GetBoundingBox();
	newBoundryBox.SetCenter(tempPostion);
	//animationState = CMD2Model::StartAnimation(animType_t::RUN);
	if (CMD2Model::isAnimationFinished == true || animationState.type != animType_t::RUN)
	{
		animationState = CMD2Model::StartAnimation(animType_t::RUN);
	}


	camera->Reset(tempPostion + initialCamera, tempPostion, glm::vec3(0.0f, 1.0f, 0.0f));
}
void Hero::Walk(float dist)
{
	auto cameraDirection = camera->getDirection();
	auto direction = glm::vec3(cameraDirection.x,0,cameraDirection.z);
	Hero::Move(dist *direction);
	camera->Walk(dist);
	camera->UpdateViewMatrix();
}
void Hero::Strafe(float dist)
{
	auto cameraRight = camera->getRightDirection();
	auto direction = glm::vec3(cameraRight.x, 0, cameraRight.z);
	Hero::Move(dist * direction);
	camera->Strafe(dist);
	camera->UpdateViewMatrix();
}