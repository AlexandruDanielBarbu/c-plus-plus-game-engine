#pragma once

#include "../Utilities/Math.h"

class Camera
{
  public:
	Camera();
	Camera(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,
		float moveSpeed = 5.0f,
		float rotateSpeed = 2.0f,
		float nearPlane = 0.1f,
		float farPlane = 100.0f,
		float fov = 45.0f
	);
	~Camera();

	void moveOx(int sens);
	void moveOy(int sens);
	void moveOz(int sens);

	void rotateOx(int sens);
	void rotateOy(int sens);
	void rotateOz(int sens);
	
	/** @brief Update camera axis (xAxis, yAxis, zAxis)
	 */
	void updateAxes();

	/** @brief Update axis first then World and View matrix
	 */
	void updateWorldView();

	void setDeltaTime(GLfloat newDeltaTime);

	Matrix viewMatrix;
	Matrix perspectiveMatrix;

  private:
	  Vector3 position;
	  Vector3 target;
	  Vector3 up;

	  GLfloat moveSpeed;
	  GLfloat rotateSpeed;

	  GLfloat nearPlane;
	  GLfloat farPlane;
	  GLfloat fov;

	  GLfloat deltaTime;

	  Vector3 xAxis;
	  Vector3 yAxis;
	  Vector3 zAxis;
	
	  Matrix worldMatrix;
};
