#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
class ThirdPersonCamera
{
	glm::vec3 mPosition;
	glm::vec3 mInitialPositionFromObject;
	glm::vec3 mRight;
	glm::vec3 mUp;
	glm::vec3 mDirection;
	glm::vec3 mCenter;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 GetLookDirection();
	double mAngleX, mAngleY;
public:
	ThirdPersonCamera();
	~ThirdPersonCamera();
	void UpdateViewMatrix();
	glm::mat4 GetViewMatrix();
	glm::vec3 GetEyePosition();
	void SetPerspectiveProjection(float FOV,float aspectRatio,float near,float far);
	glm::mat4 GetProjectionMatrix();
	void Reset(float eyeX,float eyeY,float eyez,float centerX,float centerY,float centerZ,float upX,float upY,float upZ);
	void Reset(glm::vec3 &eye,glm::vec3 &center,glm::vec3&up);
	glm::vec3 getDirection();
	glm::vec3 getRightDirection();
#pragma region Rotaions

	void Yaw(float angleDegrees);
	void Pitch(float angleDegrees);
	void Roll(float angleDegrees);

#pragma endregion

#pragma region Translations

	void Walk(float dist);
	void Strafe(float dist);
	void Fly(float dist);
#pragma endregion


	void Slide(float stepR,float stepU,float stepD);
};

