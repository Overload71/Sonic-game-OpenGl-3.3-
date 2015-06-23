#include "Cube.h"

#include <glm\gtx\transform.hpp>


Cube::Cube(ShaderProgram *fShader)
{
	mShader = fShader;
}
Cube::~Cube(void)
{
}

void Cube::Initialize()
{

	mSquare = Model();
	mSquare.VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	//we want a gray cube cube.
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	//first.riangle.
	mSquare.IndicesData.push_back(0);
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(3);
	//secon.triangle.
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(2);
	mSquare.IndicesData.push_back(3);

	mSquare.UVData.push_back((glm::vec2(0.0f, 0.0f)));
	mSquare.UVData.push_back((glm::vec2(1.0f, 0.0f)));
	mSquare.UVData.push_back((glm::vec2(0.0f, 1.0f)));
	mSquare.UVData.push_back((glm::vec2(1.0f, 1.0f)));
	mSquare.Initialize();



	int numberOfFaces = 6;
	mFacesModelMatrices.resize(numberOfFaces);

	//bottom
	mFacesModelMatrices[0] = glm::translate(0.0f, -1.0f, 0.0f)*glm::rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//top
	mFacesModelMatrices[1] = glm::translate(0.0f, 1.0f, 0.0f)*glm::rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//front
	mFacesModelMatrices[2] = glm::translate(0.0f, 0.0f, 1.0f);
	//back
	mFacesModelMatrices[3] = glm::translate(0.0f, 0.0f, -1.0f);
	//left
	mFacesModelMatrices[4] = glm::translate(-1.0f, 0.0f, 0.0f)*glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//right
	mFacesModelMatrices[5] = glm::translate(1.0f, 0.0f, 0.0f)*glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	//this transformation is applied on the whole cube!!!
	CubeModelMatrix = glm::scale(50.0f, 50.0f, 50.0f);


	skyboxTextures[0] = std::unique_ptr<Texture>(new Texture("down.jpg", 1));
	skyboxTextures[1] = std::unique_ptr<Texture>(new Texture("up.jpg", 1));
	skyboxTextures[2] = std::unique_ptr<Texture>(new Texture("front.jpg", 1));
	skyboxTextures[3] = std::unique_ptr<Texture>(new Texture("back.jpg", 1));
	skyboxTextures[4] = std::unique_ptr<Texture>(new Texture("left.jpg", 1));
	skyboxTextures[5] = std::unique_ptr<Texture>(new Texture("right.jpg", 1));
}

void Cube::Draw(glm::mat4 VP)
{
	
	for (int i = 0; i < mFacesModelMatrices.size(); i++)
	{
		mShader->UseProgram();
		mShader->BindVPMatrix(&VP[0][0]);
		glm::mat4 mvp = CubeModelMatrix * mFacesModelMatrices[i];
		mShader->BindModelMatrix(&mvp[0][0]);
		skyboxTextures[i]->Bind();
		mSquare.Draw();
	}
}
