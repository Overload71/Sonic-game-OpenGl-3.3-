#include "Rings.h"
#include<iostream>

Rings::Rings()
{

	isDestroyed = false;
}

Rings::Rings(ShaderProgram *fShader) : GameObject()
{
	//objectType = CollidableModel::ObjectType::Ring;
	mShader = fShader;
	isDestroyed = false;
}

void Rings::initlalize()
{
	Model3D::LoadFromFile("data/models/Rings/cmn_obj_ring_SD.obj", false);
	Model3D::Initialize();
	Model3D::SetBoundingBox(CollidableModel::CalculateBoundingBox(Model3D::GetVertices()));
	auto tempbouningBox = Model3D::GetBoundingBox();
	Model3D::SetBoundingBox(tempbouningBox);
}

void Rings::render(glm::mat4 trans)
{
//	if (isDestroyed == false)
		Model3D::Render(mShader,trans);
}

void Rings::bx(glm::vec3 vec)
{
	auto tempBox = Model3D::GetBoundingBox();
	tempBox.Scale(0.03f, 0.03f, 0.03f);
	tempBox.Translate(vec.x,vec.y,vec.z);
	Model3D::SetBoundingBox(tempBox);
}

void Rings::Collided(ObjectType fType)
{
	
	if (fType == ObjectType::MD2Model){
		isDestroyed = true;
	}
}

Rings::~Rings()
{
}
