#include "ThirdPersonCamera.h"
#include<iostream>

ThirdPersonCamera::ThirdPersonCamera()
{
	mAngleX = 0;
	mAngleY = 0;
	SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,200.0f);
}


ThirdPersonCamera::~ThirdPersonCamera()
{
}

glm::vec3 ThirdPersonCamera::GetLookDirection()
{
	return -mDirection;
}

void ThirdPersonCamera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}

void ThirdPersonCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (mAngleY + angleDegrees < 30 && mAngleY + angleDegrees >0)
		mAngleY += angleDegrees;
}

void ThirdPersonCamera::Walk(float dist)
{
	mPosition += dist * glm::vec3(mDirection.x,0,mDirection.z);
	mCenter += dist* glm::vec3(mDirection.x,0,mDirection.z);
}
void ThirdPersonCamera::Strafe(float dist)
{
	mPosition += dist * glm::vec3(mRight.x, 0, mRight.z);
	mCenter += dist* glm::vec3(mRight.x, 0, mRight.z);
}
void ThirdPersonCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR * mRight;
	mPosition += stepU * mUp;
	mPosition += stepD * mDirection;
}
void ThirdPersonCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV,aspectRatio,near,far);
}
glm::mat4 ThirdPersonCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}
glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void ThirdPersonCamera::UpdateViewMatrix()
{
	const float PI = 3.14f;
	auto yawRotation = glm::rotate((float)mAngleX,0.0f,1.0f,0.0f);
	auto pitchRotation = glm::rotate((float)mAngleY,mRight);
	auto newPosition = glm::vec3(/*pitchRotation * */yawRotation * glm::vec4(0,1,2,1));
	newPosition += mCenter;

	mDirection = mCenter - newPosition;
	mDirection = glm::normalize(mDirection);


	mRight = glm::cross(mDirection , glm::vec3(0,1,0));
	mRight = glm::normalize(mRight);

	mUp = glm::cross(mRight,mDirection);
	mUp = glm::normalize(mUp);


	mViewMatrix = glm::lookAt(newPosition,mCenter,mUp);
}
void ThirdPersonCamera::Reset(float eyeX, float eyeY, float eyez, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX,eyeY,eyez);
	glm::vec3 centerPt(centerX,centerY,centerZ);
	glm::vec3 upVec(upX,upY,upZ);
	Reset(eyePt,centerPt,upVec);
}
void ThirdPersonCamera::Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;
	mDirection = center - mPosition;
	mRight = glm::cross(mDirection,up);
	mUp = up;
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);
	mCenter = center;
	mViewMatrix = glm::lookAt(mPosition,center,mUp);
}
glm::vec3 ThirdPersonCamera::GetEyePosition()
{
	return mPosition;
}
glm::vec3 ThirdPersonCamera::getDirection()
{
	return mDirection;
}
glm::vec3 ThirdPersonCamera::getRightDirection()
{
	return mRight;
}