#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

enum TipoCamara {
	TerceraPersona, Aerea, Isometrica
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	glm::vec3 getPosition() const;
	glm::vec3 ultimaPosicionAerea = glm::vec3(0.0f, 70.0f, 0.0f);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	//Cambio de camara
	void setVistaTerceraPersona(glm::vec3 bobPosition, GLfloat distanceBehindd, GLfloat height, GLfloat yaw);
	void setVistaAerea(GLfloat height);
	void setVistaIsometrica(glm::vec3 position, GLfloat yawAngle, GLfloat pitchAngle);

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	TipoCamara tipoCamara;

	void update();
};

