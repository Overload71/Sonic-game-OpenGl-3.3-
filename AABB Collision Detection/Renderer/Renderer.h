#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


#include "Shaders/shader.hpp"
#include "Model/Model.h"
#include "EulerCamera/EulerCamera.h"
#include "Texture/texture.h"
#include "GraphicsDevice/ShaderProgram.h"
#include "Scene/Model3D.h"
#include "GraphicsDevice/KeyFrameAnimationShader.h"
#include "MD2Model/md2model.h"
#include "CollisionDetection/CollisionManager.h"
#include"Hero.h"
#include"Cube.h"
#include"Rings.h"
class Renderer
{


    KeyFrameAnimationShader animatedModelShader;
	ShaderProgram staticModelShader;
	// Transformation
	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;

	CMD2Model blade;
	animState_t bladeAnimationState;

	std::unique_ptr<Model> floor;
	std::unique_ptr<Texture> floorTexture;
	std::unique_ptr<Rings> ring[70];
	std::unique_ptr<Hero>player;
	std::unique_ptr<Cube>myCube;
	std::unique_ptr<Model3D> house;
	glm::mat4 houseM;


	glm::mat4 floorM;
	glm::mat4 ringM[100];
	glm::mat4 bladeM;
	glm::vec3 ambientLight;
	glm::vec3 lightPosition;

	std::unique_ptr<CollisionManager> collisionManager;

public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__

