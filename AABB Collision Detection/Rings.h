#pragma once
#include"GameObject.h"
#include"CollisionDetection\CollidableModel.h"
#include"Scene\Model3D.h"
#include"GraphicsDevice\ShaderProgram.h"
class Rings : public GameObject,public CollidableModel,public Model3D
{
	
public:
	Rings();
	Rings(ShaderProgram *fshader);
	ShaderProgram *mShader;
	bool isDestroyed;
	void initlalize();
	void render(glm::mat4 trans);
	void bx(glm::vec3 vec);
	virtual void Collided(ObjectType fType);
	~Rings();
};

