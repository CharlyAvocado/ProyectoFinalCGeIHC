#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	// M�todo para configurar la direcci�n de la luz para el ciclo de d�a y noche
	void setDirection(const glm::vec3& dir);
	~DirectionalLight();

public: //Se hace publico para poder realizar el ciclo de d�a y noche
	glm::vec3 direction;
};

