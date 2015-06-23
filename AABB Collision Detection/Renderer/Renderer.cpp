#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include "OBJLoader/objloader.hpp"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	//myCamera = std::unique_ptr<FPCamera>(new FPCamera());
	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());
	//////////////////////////////////////////////////////////////////////////
	//drawing a square.
	floor = std::unique_ptr<Model>(new Model());

	floor->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,0.0f));
	floor->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,0.0f));
	floor->VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,10.0f));
	floor->VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,10.0f));
	
	//first triangle.
	floor->IndicesData.push_back(0);
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(3);

	//second triangle.
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(2);
	floor->IndicesData.push_back(3);
	glm::vec3 squareNormal = glm::vec3(0.0,0.0,1.0);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->Initialize();

	floorTexture = std::unique_ptr<Texture>(new Texture("data/textures/rock.jpg",0));
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	//load model.
	
	for (int i = 0; i < 70; i++){
		ring[i] = std::unique_ptr < Rings >(new Rings(&staticModelShader)) ;
		ring[i]->initlalize();
		collisionManager->AddCollidableModel((CollidableModel*)ring[i].get());
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	house = std::unique_ptr<Model3D>(new Model3D());
	house->LoadFromFile("data/models/House/house.3ds");
	house->Initialize();
	house->SetBoundingBox(CollidableModel::CalculateBoundingBox(house->GetVertices(),-2.0f));
	collisionManager->AddCollidableModel((CollidableModel*) house.get());
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	// Create and compile our GLSL program from the shaders
	animatedModelShader.LoadProgram();
	staticModelShader.LoadProgram();
	//////////////////////////////////////////////////////////////////////////

	player = unique_ptr<Hero>(new Hero(&animatedModelShader));
	collisionManager->AddCollidableModel((CollidableModel*)player.get());



	myCube = std::unique_ptr<Cube>(new Cube(&staticModelShader));
	myCube->Initialize();
	//////////////////////////////////////////////////////////////////////////
	// Projection matrix : 
	

	
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	staticModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(staticModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(5.0,5.0,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(staticModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(1.0,1.0,1.0);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &player->camera->GetEyePosition()[0]);

	///////////////////////////////////////////////////
	//repeat the process for the animated models shader.
	animatedModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(animatedModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(1.0,8.25,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(animatedModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(1.0,1.0,1.0);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &player->camera->GetEyePosition()[0]);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//Setting the initaial transformations
	floorM =  glm::scale(1.0f,2.0f,50.0f)*glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	for (int i = 0; i <= 6; i++)
	{
		ringM[i] = glm::translate(0.5f, 0.25f, 30.0f + i)* glm::scale(0.03f, 0.03f, 0.03f);
		ring[i]->bx(glm::vec3(0.5f, 0.25f, 30.0f + i));
		ringM[7 + i] = glm::translate(-0.5f, 0.25f, 10.0f + i)  * glm::scale(0.03f, 0.03f, 0.03f);
		ring[7 + i]->bx(glm::vec3(-0.5f, 0.25f, 10.0f + i));
		ringM[14 + i] = glm::translate(0.0f, 0.25f,  20.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[14 + i]->bx(glm::vec3(0.0f, 0.25f, 20.0f + i));
		ringM[21 + i] = glm::translate(0.5f, 0.25f,   0.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[21 + i]->bx(glm::vec3(0.5f, 0.25f, 0.0f + i));
		ringM[28 + i] = glm::translate(-0.5f, 0.25f, -10.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[28 + i]->bx(glm::vec3(-0.5f, 0.25f, -10.0f + i));
		ringM[35 + i] = glm::translate(0.0f, 0.25f, -20.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[35 + i]->bx(glm::vec3(0.0f, 0.25f, -20.0f + i));
		ringM[42 + i] = glm::translate(0.5f, 0.25f, -30.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[42 + i]->bx(glm::vec3(0.5f, 0.25f, -30.0f + i));
		ringM[49 + i] = glm::translate(-0.5f, 0.25f, 40.0f + i) * glm::scale(0.03f, 0.03f, 0.03f);
		ring[49 + i]->bx(glm::vec3(-0.5f, 0.25f, 40.0f + i));
		ringM[56 + i] = glm::translate(0.0f, 0.25f, -40.0f + i)  * glm::scale(0.03f, 0.03f, 0.03f);
		ring[56 + i]->bx(glm::vec3(0.0f, 0.25f, -40.0f + i));
		ringM[63 + i] = glm::translate(0.0f, 0.25f, -48.0f + i) *  glm::scale(0.03f, 0.03f, 0.03f);
		ring[63 + i]->bx(glm::vec3(0.0f, 0.25f, -48.0f + i));
	}
	//we have to scale and translate the spider's bounding box to match the new position and size.
	houseM = glm::rotate(90.0f,1.0f,0.0f,0.0f) *glm::scale(0.1f,0.1f,0.1f);
	auto tempBox = house->GetBoundingBox();
	tempBox.Scale(0.1f,0.1f,0.1f);
	tempBox.Rotate(90.0f,1.0f,0.0f,0.0f);
	house->SetBoundingBox(tempBox);


	//////////////////////////////////////////////////////////////////////////

}

void Renderer::Draw()
{		

		//Bind the VP matrix (Camera matrices) to the current shader.
	glm::mat4 VP = player->camera->GetProjectionMatrix() * player->camera->GetViewMatrix();


		staticModelShader.UseProgram();
		staticModelShader.BindVPMatrix(&VP[0][0]);
		staticModelShader.BindModelMatrix(&floorM[0][0]);
		floorTexture->Bind();
		floor->Draw();


		myCube->Draw(VP);
		
		for (int i = 0; i < 70; i++){
			ring[i]->render(ringM[i]);
		}
		//house->Render(&staticModelShader,houseM);
		
		/*animatedModelShader.UseProgram();
		animatedModelShader.BindVPMatrix(&VP[0][0]);
		animatedModelShader.BindModelMatrix(&bladeM[0][0]);
		blade.RenderModel(&bladeAnimationState,&animatedModelShader)*/;


		player->Render(VP);
}

void Renderer::Cleanup()
{
}

void Renderer::Update(double deltaTime)
{
	double triangle1RotationSpeed = 0.1;
	double trianglesRotationAngle = triangle1RotationSpeed*deltaTime;
	glm::mat4 rotationMat = glm::rotate((float)trianglesRotationAngle, glm::vec3(0.0, 1.0, 0.0));
	for (int i = 0; i < 70; i++)
	ringM[i] = ringM[i] * rotationMat;
	collisionManager->UpdateCollisions();
	player->UpdataAnimation(deltaTime/1000);
}

void Renderer::HandleKeyboardInput(int key)
{
	
	//NOTE!!! 
	//this is the worst way possible for moving an object with the camera.
	// but it'll serve our purpose for now.

	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		
		player->Walk(0.2f);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		
		player->Walk(-0.2f);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		
		player->Strafe(0.05f);
		break;
		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		
		player->Strafe(-0.05f);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		

		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		
		
		break;
	default:
		break;
	}

	//Set the transformed bounding box again.
	

	//continue the remaining movements.
	

	//update the eye position uniform.
	staticModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID, 1, &player->camera->GetEyePosition()[0]);

	animatedModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID, 1, &player->camera->GetEyePosition()[0]);
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	float scaleAngle = 10.f;
	player->camera->Yaw(deltaX *scaleAngle);
	player->camera->Pitch(deltaY *scaleAngle);
	player->camera->UpdateViewMatrix();
}

