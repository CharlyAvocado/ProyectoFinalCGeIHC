#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	tipoCamara = TerceraPersona;

	update();
}

//Camara 3era persona
void Camera::setVistaTerceraPersona(glm::vec3 bobPosition, GLfloat distanceBehind, GLfloat height, GLfloat yaw)
{
	tipoCamara = TerceraPersona;
	this->yaw = yaw;

	front.x = cos(glm::radians(yaw));
	front.z = sin(glm::radians(yaw));
	front = glm::normalize(front);

	position = bobPosition - front * distanceBehind; // Coloca la cámara detrás de Bob
	position.y += height;                            // Ajusta la altura
	update();
}

glm::vec3 Camera::getPosition() const {
	return position;
}

// Cámara aérea ortogonal
void Camera::setVistaAerea(GLfloat height)
{
	tipoCamara = Aerea;

	// Si la cámara aérea se activó anteriormente, se usará la posición guardada
	if (ultimaPosicionAerea.y != height) {
		ultimaPosicionAerea = glm::vec3(position.x, height, position.z);
	}

	position = ultimaPosicionAerea;  // Usa la última posición guardada
	yaw = -90.0f;  // Mirando hacia abajo
	pitch = -90.0f;
	update();
}

// Cámara isométrica estática
void Camera::setVistaIsometrica(glm::vec3 position, GLfloat yawAngle, GLfloat pitchAngle)
{
	tipoCamara = Isometrica;
	this->position = position;
	yaw = yawAngle;
	pitch = pitchAngle;
	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	if (tipoCamara != Aerea) {
		return;
	}
	GLfloat velocity = moveSpeed * deltaTime;

		// Movimiento sólo en X y Z en vista aérea
		if (keys[GLFW_KEY_S]) position.z -= velocity;
		if (keys[GLFW_KEY_W]) position.z += velocity;
		if (keys[GLFW_KEY_D]) position.x -= velocity;
		if (keys[GLFW_KEY_A]) position.x += velocity;






	//if (keys[GLFW_KEY_W])
	//{
	//	position += front * velocity;
	//}

	//if (keys[GLFW_KEY_S])
	//{
	//	position -= front * velocity;
	//}

	//if (keys[GLFW_KEY_A])
	//{
	//	position -= right * velocity;
	//}

	//if (keys[GLFW_KEY_D])
	//{
	//	position += right * velocity;
	//}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	//if (tipoCamara != Aerea) {
	//	return;
	//}
	//xChange *= turnSpeed;
	//yChange *= turnSpeed;

	//yaw += xChange;
	//pitch += yChange;

	//if (pitch > 89.0f)
	//{
	//	pitch = 89.0f;
	//}

	//if (pitch < -89.0f)
	//{
	//	pitch = -89.0f;
	//}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
