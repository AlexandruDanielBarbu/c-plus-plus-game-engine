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
	// might be wrong!!!
	deltaTime = Globals::frameTime;
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
}

void Camera::moveOy(int sens) {
	Vector3 forward = yAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
}

void Camera::moveOz(int sens) {
	Vector3 forward = zAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
}