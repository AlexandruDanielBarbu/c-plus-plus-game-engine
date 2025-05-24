#include "stdafx.h"	
#include "Camera.h"
#include "Globals.h"

Camera::Camera() {
	position = Vector3(0, 0, -1);
	target = Vector3(0, 0, 0);
	up = Vector3(0, 1, 0);

	fov = 0.785398f; // expressed in radians
	nearPlane = .2f;
	farPlane = 10.0f;

	moveSpeed = 0.1f;
	rotateSpeed = 0.1f;

	updateWorldView();
	perspectiveMatrix.SetPerspective(fov, 16 / 9, nearPlane, farPlane);
}

Camera::Camera(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up,
	float moveSpeed,
	float rotateSpeed,
	float nearPlane,
	float farPlane,
	float fov) {
	
	//this->position = position;
	//: position(position),
	//	target(target),
	//	up(up),
	//	moveSpeed(moveSpeed),
	//	rotateSpeed(rotateSpeed),
	//	nearPlane(nearPlane),
	//	farPlane(farPlane),
	//	fov(fov)

}
	

Camera::~Camera() {

}
void Camera::updateAxes() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::moveOx(int sens) {
	Vector3 forward = xAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOy(int sens) {
	Vector3 forward = yAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOz(int sens) {
	Vector3 forward = zAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	
	updateWorldView();
}

void Camera::rotateOx(int sens) {
	// Compute rotation angle for my rotate matrix
	float unghiRotatie = sens * rotateSpeed * deltaTime;

	// Setup localUp and localTarget position
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);

	// Rotatate loclaUp and convert to world space
	Matrix mRotateOX;
	mRotateOX.SetRotationX(unghiRotatie);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	
	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();
	
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = (rotatedTarget * worldMatrix).toVector3();

	updateWorldView();
}

void Camera::rotateOy(int sens) {
	float unghiRotatie = sens * rotateSpeed * deltaTime;

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);

	Matrix mRotateOY;
	mRotateOY.SetRotationY(unghiRotatie);
	Vector4 rotatedTarget = localTarget * mRotateOY;

	target = (rotatedTarget * worldMatrix).toVector3();

	updateWorldView();
}

void Camera::rotateOz(int sens) {
	float unghiRotatie = sens * rotateSpeed * deltaTime;

	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);

	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(unghiRotatie);
	Vector4 rotatedLocalUp = localUp * mRotateOZ;

	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();

	updateWorldView();
}

void Camera::updateWorldView() {
	updateAxes();

	Matrix T, Tinvert, R;
	T.SetTranslation(position);
	Tinvert.SetTranslation(-position);

	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0;		 R.m[3][1] = 0		; R.m[3][2] = 0		 ; R.m[3][3] = 1;

	worldMatrix = R * T;

	viewMatrix = Tinvert * R.Transpose();	
}

void Camera::setDeltaTime(GLfloat newDeltaTime) {
	this->deltaTime = newDeltaTime;
}