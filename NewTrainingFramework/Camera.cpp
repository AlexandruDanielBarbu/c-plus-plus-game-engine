#include "Camera.h"

Camera::Camera() {
	position = Vector3(0, 0, -1);
	target = Vector3(0, 0, 0);
	up = Vector3(0, 1, 0);

	fov = 0.785398f; // expressed in radians
	nearPlane = .2f;
	farPlane = 10.0f;

	moveSpeed = 0.1f;
	rotateSpeed = 0.1f;
}

