#pragma once
#include<memory>
#include"GameObject.h"
#include"CollisionDetection\CollidableModel.h"
#include"MD2Model\md2model.h"
#include"EulerCamera\EulerCamera.h"
#include"ThirdPersonCamera.h"
class Hero : public GameObject,public CMD2Model
{
	KeyFrameAnimationShader *mShader;
	animState_t animationState;
	void initialize();
	glm::vec3 initialCamera;
	void Move(glm::vec3 fDirection);
public:
	std::unique_ptr<ThirdPersonCamera> camera;
	Hero(KeyFrameAnimationShader *fShader);
	Hero(KeyFrameAnimationShader *fShader,glm::vec3 fPosition, glm::vec3 fDirection, bool fIsDestroyed);
	~Hero();
	virtual void Collided(ObjectType fType);
	void UpdataAnimation(float deltatime);
	void Render(glm::mat4 VP);
	void Walk(float dist);
	void Strafe(float dist);
	
};

