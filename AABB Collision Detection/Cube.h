#ifndef Cube_h__
#define Cube_h__

#include "Model\Model.h"
#include"GraphicsDevice\ShaderProgram.h"
#include"Texture\texture.h"
#include<memory>
class Cube
{
	Model mSquare;
	std::vector<glm::mat4> mFacesModelMatrices;
	ShaderProgram *mShader;
	std::unique_ptr<Texture> skyboxTextures[6];
public:
	Cube(ShaderProgram *fShader);
	~Cube(void);
	glm::mat4 CubeModelMatrix;
	void Initialize();
	void Draw(glm::mat4 VP);
	void Cleanup();
};

#endif // Cube_h__
