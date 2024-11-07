/*Proyecto Monopoly GO! 
Laboratorio de computacion grafica e interaccion humano-computadora

 UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO

FACULTAD DE INGENIERÍA

DIVISIÓN DE INGENIERÍA ELÉCTRICA

INGENIERÍA EN COMPUTACIÓN

DESARROLLADORES: 
Gomez Vazquez Juan Pablo -> Nº de Cuenta: 317210743
Martinez Miranda Juan Carlos -> Nº de Cuenta: 318145042

GRUPO DE LABORATORIO: 11

GRUPO DE TEORÍA: 04

SEMESTRE 2025-1
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include "time.h"

//para iluminacion
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animaci�n
//letrero
bool enEspera;
bool moviendoHaciaArriba;
float tiempoTotal;
float tiempoEspera;
float posModeloY;
float anguloRotacion;
float duracionFase;
float alturaMin;
float alturaMax;
float velocidadRotacion;
float velocidadMovimiento;
bool cicloCompleto;
//Movimiento de objetos alrededor del tablero
float movObjX;
float movObjZ;
float movObjX_bote = 0.0f;
float movObjZ_bote = 0.0f;
float rotacion_bote = 0.0f;
float rotllanta = 0.0f;
float rotllantaOffset = 5.0f;
bool a_b_bote = true;
bool b_c_bote = false;
bool c_d_bote = false;
bool d_e_bote = false;
float rotacion;
float movOffset;
float rotacionCuerpos;
float rotacionCuerposOffset;
bool avanza;
bool a_b;
bool b_c;
bool c_d;
bool d_e;
float variacionAngulo = 0.0f;


//Dados
float randRotX; 
float randRotY;
float randRotZ;
float movOffsetDado; 
float movDado = 0.0f;
float rotacionDado = 0.0f;

float randomRotationX;
float randomRotationY;
float randomRotationZ;

bool DadoRot;
float tope;

int caraDado8; 
int caraDado4; 
int sumaDados;
//variables para keyframes
float reproduciranimacion, habilitaranimacion;



Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture TableroTexture;
//Arreglos de modelos
Model modelos[40];
Model modelosCooked[40];

//Modelos Varios
Model Postes_M;
Model Letrero_M;
Model Monopoly_M;
Model MonopolyNoche_M;
Model Dado8;
Model Dado4;
Model Ciudad_M;
Model Reflector_M;
Model CuerpoChorizard_M;
Model AlaD_M;
Model AlaI_M;
Model EscupiSalty_M;
Model Puff_M;
Model CasaBalde;
Model Mofle1_M;
Model Mofle2_M;
Model SenalBus_M;
////////////////////////////////////////////////////////////////////////////////////////////////
//Modelos Bob Esponja
Model Bob;
Model BobCuerpo;
Model BobPD;
Model BobPI;
Model BobBD;
Model BobBI;
Model Patricio;
Model Calamardo;
Model Plankton;
Model Gary;
Model CasaBob;
Model CasaPatricio;
Model CasaCalamardo;
Model Kelp;
Model Arbol;
Model Flor;
Model Medusa;
Model Pez;
Model Crustaceo;
Model Burbuja;
Model Ostra;
Model Coral;
Model Pez2;

//Modelos Pokemon
Model RedCabeza_M;
Model RedTorso_M;
Model RedBI_M;
Model RedBD_M;
Model RedPI_M;
Model RedPD_M;
Model Lapras_M;
Model Charmander_M;
Model Jenny_M;
Model Joy_M;
Model James_M;
Model Jessie_M;
Model EdificioPoke_M;
Model GymPalace_M;
Model Giovanni_M;
Model Weezing_M;
Model Lechonk_M;
Model Azumarill_M;
Model Electrode_M;
Model ColorfulPlant_M;
Model BerryTree_M;
Model CentroPoke_M;
Model PineTree_M;
Model CasaPlayer_M;
Model PokeMart_M;
Model Pikachu_M;
Model TreeOfLife_M;
Model Rhydon_M;
Model Voltorb_M;
/////////////////////////////////////////////////////////////////////////////////////////////////
//Modelos Base iluminacion
Model BobBase;
Model PatricioBase;
Model CalamardoBase;
Model PlanktonBase;
Model GaryBase;
Model CasaBobBase;
Model CasaPatricioBase;
Model CasaCalamardoBase;
Model KelpBase;
Model ArbolBase;
Model FlorBase;
Model MedusaBase;
Model PezBase;
Model CrustaceoBase;
Model BurbujaBase;
Model OstraBase;
Model CoralBase;
Model Pez2Base;

//Pokemon
Model RedCabeza_MBase;
Model RedTorso_MBase;
Model RedBI_MBase;
Model RedBD_MBase;
Model RedPI_MBase;
Model RedPD_MBase;
Model Lapras_MBase;
Model Charmander_MBase;
Model Jenny_MBase;
Model Joy_MBase;
Model James_MBase;
Model Jessie_MBase;
Model EdificioPoke_MBase;
Model GymPalace_MBase;
Model Giovanni_MBase;
Model Weezing_MBase;
Model Lechonk_MBase;
Model Azumarill_MBase;
Model Electrode_MBase;
Model ColorfulPlant_MBase;
Model BerryTree_MBase;
Model CentroPoke_MBase;
Model PineTree_MBase;
Model CasaPlayer_MBase;
Model PokeMart_MBase;
Model Pikachu_MBase;
Model TreeOfLife_MBase;
Model Rhydon_MBase;

////////////////////////////////////////////////////////////////////////////////////////////////////
//Modelos Cocinados
Model BobCocinado;
Model PatricioCocinado;
Model CalamardoCocinado;
Model PlanktonCocinado;
Model GaryCocinado;
Model CasaBobCocinado;
Model CasaPatricioCocinado;
Model CasaCalamardoCocinado;
Model KelpCocinado;
Model ArbolCocinado;
Model FlorCocinado;
Model MedusaCocinado;
Model PezCocinado;
Model CrustaceoCocinado;
Model BurbujaCocinado;
Model OstraCocinado;
Model CoralCocinado;
Model Pez2Cocinado;
//Pokemon
Model RedCabeza_MCocinado;
Model RedTorso_MCocinado;
Model RedBI_MCocinado;
Model RedBD_MCocinado;
Model RedPI_MCocinado;
Model RedPD_MCocinado;
Model Lapras_MCocinado;
Model Charmander_MCocinado;
Model Jenny_MCocinado;
Model Joy_MCocinado;
Model James_MCocinado;
Model Jessie_MCocinado;
Model EdificioPoke_MCocinado;
Model GymPalace_MCocinado;
Model Giovanni_MCocinado;
Model Weezing_MCocinado;
Model Lechonk_MCocinado;
Model Azumarill_MCocinado;
Model Electrode_MCocinado;
Model ColorfulPlant_MCocinado;
Model BerryTree_MCocinado;
Model CentroPoke_MCocinado;
Model PineTree_MCocinado;
Model CasaPlayer_MCocinado;
Model PokeMart_MCocinado;
Model Pikachu_MCocinado;
Model TreeOfLife_MCocinado;
Model Rhydon_MCocinado;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//Modelos Base Noche
Model BobNoche;
Model PatricioNoche;
Model CalamardoNoche;
Model PlanktonNoche;
Model GaryNoche;
Model CasaBobNoche;
Model CasaPatricioNoche;
Model CasaCalamardoNoche;
Model KelpNoche;
Model ArbolNoche;
Model FlorNoche;
Model MedusaNoche;
Model PezNoche;
Model CrustaceoNoche;
Model BurbujaNoche;
Model OstraNoche;
Model CoralNoche;
Model Pez2Noche;
//Pokemon
Model Lapras_MNoche;
Model Charmander_MNoche;
Model Jenny_MNoche;
Model Joy_MNoche;
Model James_MNoche;
Model Jessie_MNoche;
Model EdificioPoke_MNoche;
Model GymPalace_MNoche;
Model Giovanni_MNoche;
Model Weezing_MNoche;
Model Lechonk_MNoche;
Model Azumarill_MNoche;
Model Electrode_MNoche;
Model ColorfulPlant_MNoche;
Model BerryTree_MNoche;
Model CentroPoke_MNoche;
Model PineTree_MNoche;
Model CasaPlayer_MNoche;
Model PokeMart_MNoche;
Model Pikachu_MNoche;
Model TreeOfLife_MNoche;
Model Rhydon_MNoche;
////////////////////////
//Modelo Carrerin
Model FlashB;
Model PieIzq;
Model PieDer;
Model ManoIzq;
Model ManoDer;

//Modelo Bote
Model Bote;
Model LlantaDerecha;
Model LlantaIzquierda;
Model LlantaDelantera;
Model Cartel;

//////////////////////////////////////////////////////////////////////////////////////////////////
//Posicion Bob
float movZ = 0.0f;
float movX = 0.0f;
glm::vec3 bobPosition = glm::vec3(-90.0f + movZ, 1.0f, 95.0f+ movX);
GLfloat yawBob = 0.0f;
GLfloat distanceBehind = 30.0f;
GLfloat height = 5.0f;
bool avanzaZ = true;
bool avanzaX = false;
float rotacionB = 0.0f;
float rotacionBob = 0.0f;
const int TOTAL_CASILLAS = 40;
int casillaActual = 0;
bool banderas[TOTAL_CASILLAS] = { false };
int estado = 0;
const float DISTANCIA_POR_CASILLA = 19.0f; 
int casillaObjetivo = 0;
float anguloBrazoDerecho = 0.0f;
float anguloBrazoIzquierdo = 0.0f;
float anguloPiernaDerecha = 0.0f;
float anguloPiernaIzquierda = 0.0f;
float velocidadMovimientoBob = 3.0f; 
bool moviendoAdelante = true;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";




//funcion de calculo de normales por promedio de v�rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

///////////////////////////////KEYFRAMESJP//////////////////////////////////////////////////////////////////////////////////
float posXavion = 2.0f, posYavion = 5.0f, posZavion = -3.0f;
float movAvion_x = 0.0f, movAvion_y = 0.0f;
float giroAvion = 0.0f;

#define MAX_FRAMES_AVION 100
int i_max_steps_avion = 90;
int i_curr_steps_avion = 0;

typedef struct _frame_avion {
	float movAvion_x;     // Variable para Posici�n X del Avi�n
	float movAvion_y;     // Variable para Posici�n Y del Avi�n
	float movAvion_xInc;  // Incremento en X para interpolaci�n
	float movAvion_yInc;  // Incremento en Y para interpolaci�n
	float giroAvion;      // �ngulo de giro del Avi�n
	float giroAvionInc;   // Incremento de �ngulo para interpolaci�n
} FRAME_Avion;

FRAME_Avion KeyFrameAvion[MAX_FRAMES_AVION];
int FrameIndexAvion = 0;
bool playAvion = true;
int playIndexAvion = 0;
FILE* archivoAvion;


void leerFramesAvion() {
	FILE* archivoLectura;
	fopen_s(&archivoLectura, "KeyFrameDataAvion.txt", "r");
	if (archivoLectura == NULL) {
		printf("Error al abrir KeyFrameDataAvion.txt para lectura\n");
		return;
	}

	char line[256];
	FrameIndexAvion = 0;
	int index = 0;

	while (fgets(line, sizeof(line), archivoLectura)) {
		float mov_x, mov_y, giro;

		if (sscanf_s(line, "KeyFrameAvion[%d].movAvion_x = %f;", &index, &mov_x) == 2) {
			KeyFrameAvion[FrameIndexAvion].movAvion_x = mov_x;
		}
		if (fgets(line, sizeof(line), archivoLectura) && sscanf_s(line, "KeyFrameAvion[%d].movAvion_y = %f;", &index, &mov_y) == 2) {
			KeyFrameAvion[FrameIndexAvion].movAvion_y = mov_y;
		}
		if (fgets(line, sizeof(line), archivoLectura) && sscanf_s(line, "KeyFrameAvion[%d].giroAvion = %f;", &index, &giro) == 2) {
			KeyFrameAvion[FrameIndexAvion].giroAvion = giro;
			FrameIndexAvion++;
		}
	}
	fclose(archivoLectura);
	//printf("Datos de KeyFrame del carrerin leidos desde KeyFrameDataAvion.txt\n");
}

void interpolationAvion() {
	// Calcula el incremento en X para el avi�n
	KeyFrameAvion[playIndexAvion].movAvion_xInc =
		(KeyFrameAvion[playIndexAvion + 1].movAvion_x - KeyFrameAvion[playIndexAvion].movAvion_x) / i_max_steps_avion;

	// Calcula el incremento en Y para el avi�n
	KeyFrameAvion[playIndexAvion].movAvion_yInc =
		(KeyFrameAvion[playIndexAvion + 1].movAvion_y - KeyFrameAvion[playIndexAvion].movAvion_y) / i_max_steps_avion;

	// Calcula el incremento de giro para el avi�n
	KeyFrameAvion[playIndexAvion].giroAvionInc =
		(KeyFrameAvion[playIndexAvion + 1].giroAvion - KeyFrameAvion[playIndexAvion].giroAvion) / i_max_steps_avion;
}

void resetElementsAvion() {
	// Restablece la posici�n y rotaci�n del avi�n al primer keyframe
	movAvion_x = KeyFrameAvion[0].movAvion_x;
	movAvion_y = KeyFrameAvion[0].movAvion_y;
	giroAvion = KeyFrameAvion[0].giroAvion;
}

void abrirArchivoAvion() {
	fopen_s(&archivoAvion, "KeyFrameDataAvion.txt", "r");
	if (archivoAvion == NULL) {
		printf("Error al abrir el archivo KeyFrameDataAvion.txt para lectura\n");
	}
}

void cerrarArchivoAvion() {
	if (archivoAvion != NULL) {
		fclose(archivoAvion);
		printf("Archivo KeyFrameDataAvion.txt cerrado\n");
		archivoAvion = NULL;  // Aseg�rate de resetear el puntero para evitar problemas futuros
	}
}

void animateAvion() {
	if (playAvion) {
		if (i_curr_steps_avion >= i_max_steps_avion) {  // fin de la animaci�n entre frames?
			playIndexAvion++;
			//printf("playIndexAvion: %d\n", playIndexAvion);  // Imprime el �ndice de animaci�n actual
			if (playIndexAvion > FrameIndexAvion - 2) {  // Fin de toda la animaci�n con el �ltimo frame?
				//printf("FrameIndexAvion = %d\n", FrameIndexAvion);
				//printf("Termin� la animaci�n del avi�n\n");  // Mensaje final cuando acaba la animaci�n
				playIndexAvion = 0;
				resetElementsAvion();
				interpolationAvion();
				playAvion = true;
				
			}
			else {
				i_curr_steps_avion = 0;  // Resetea el contador
				interpolationAvion();
			}
		}
		else {
			// Dibujar Animaci�n
			movAvion_x += KeyFrameAvion[playIndexAvion].movAvion_xInc;
			movAvion_y += KeyFrameAvion[playIndexAvion].movAvion_yInc;
			giroAvion += KeyFrameAvion[playIndexAvion].giroAvionInc;
			i_curr_steps_avion++;
		}
	}
}

///////////////////////////////KEYFRAMES/////////////////////////////////////////////////////////////////////////////////
bool animacion = false;
float posXModelo = 60.0, posYModelo = 2.70, posZModelo = -30.0;
float	moxModelo_X = 0.0f, moxModelo_Y = 0.0f;
float giroModelo = 0;
glm::vec3 posModelo = glm::vec3(2.0f, 0.0f, 0.0f);

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float moxModelo_X;		//Variable para PosicionX
	float moxModelo_Y;		//Variable para PosicionY
	float moxModelo_XInc;		//Variable para IncrementoX
	float moxModelo_YInc;		//Variable para IncrementoY
	float giroModelo;
	float giroModeloInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
int contadorRalentizador = 0;
bool play = false;
int playIndex = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funciones lectura de keyframes con archivos de texto
void ReadKeyFramesFile() {
	FILE* ReadFile;
	fopen_s(&ReadFile, "ValoresKeyFrameVoltorb.txt", "r"); //Apertura del archivo en modo de solo lectura
	if (ReadFile == NULL) {
		printf("Error: No fue posible abrir el archivo en modo lectura\n");
		return;
	}
	char line[256]; //Buffer para almacenar l�neas le�das
	FrameIndex = 0; //Reinicia el indice al comienzo de la lectura
	//Lectura del archivo l�nea por l�nea
	while (fgets(line, sizeof(line), ReadFile)) {
		int index;
		float mov_x, mov_y, giro;

		//Lectura de los datos de moxModelo_X
		if (sscanf_s(line, "KeyFrame[%d].moxModelo_X = %f;", &index, &mov_x) == 2) {
			KeyFrame[FrameIndex].moxModelo_X = mov_x;
		}


		//Lectura de los datos de moxModelo_Y
		if (fgets(line, sizeof(line), ReadFile) && sscanf_s(line, "KeyFrame[%d].moxModelo_Y = %f;", &index, &mov_y) == 2) {
			KeyFrame[FrameIndex].moxModelo_Y = mov_y;
		}


		//Lectura de los datos de giroModelo
		if (fgets(line, sizeof(line), ReadFile) && sscanf_s(line, "KeyFrame[%d].giroModelo = %f;", &index, &giro) == 2) {
			KeyFrame[FrameIndex].giroModelo = giro;
			/*printf("-------------------------------------------------------------------------------------------------------------------\n");
			printf("Indice KeyFrame %d leido: moxModelo_X = %.2f, moxModelo_Y = %.2f, giroModelo = %.2f\n", FrameIndex, mov_x, mov_y, giro);
			printf("-------------------------------------------------------------------------------------------------------------------\n");*/
			FrameIndex++; // Incrementa el �ndice para el pr�ximo frame
		}

	}
	fclose(ReadFile);
	/*printf("--------------------------------------------------------------------------------------------------------------------------- ");
	printf("Se termino la lectura del archivo ValoresKeyFrame.txt\n");*/
}

void resetElements(void)
{
	moxModelo_X = KeyFrame[0].moxModelo_X;
	moxModelo_Y = KeyFrame[0].moxModelo_Y;
	giroModelo = KeyFrame[0].giroModelo;
}

void interpolation(void)
{
	KeyFrame[playIndex].moxModelo_XInc = (KeyFrame[playIndex + 1].moxModelo_X - KeyFrame[playIndex].moxModelo_X) / i_max_steps;
	KeyFrame[playIndex].moxModelo_YInc = (KeyFrame[playIndex + 1].moxModelo_Y - KeyFrame[playIndex].moxModelo_Y) / i_max_steps;
	KeyFrame[playIndex].giroModeloInc = (KeyFrame[playIndex + 1].giroModelo - KeyFrame[playIndex].giroModelo) / i_max_steps;

}
void iniciarAnimacion() {
	if (reproduciranimacion < 1) {
		if (!play && (FrameIndex > 1)) {
			resetElements();
			interpolation();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
			reproduciranimacion++;
			habilitaranimacion = 0;
			//printf("\n Iniciando animaci�n en ciclo.\n");
		}
	}
}

void reiniciarAnimacion() {
	if (habilitaranimacion < 1 && reproduciranimacion > 0) {
		//printf("Reiniciando animaci�n.\n");
		reproduciranimacion = 0;
		habilitaranimacion++;
	}
}
void animate() {
	if (play) {
		if (i_curr_steps >= i_max_steps) { // fin de interpolaci�n entre frames
			playIndex++;
			if (playIndex > FrameIndex - 2) { // fin de toda la animaci�n
				playIndex = 0;
				play = false;
				reiniciarAnimacion();
				iniciarAnimacion();  // Inicia de nuevo la animaci�n
			}
			else { // interpolaci�n al siguiente cuadro
				i_curr_steps = 0;
				interpolation();
			}
		}
		else {
			// Dibujar Animaci�n
			moxModelo_X += KeyFrame[playIndex].moxModelo_XInc;
			moxModelo_Y += KeyFrame[playIndex].moxModelo_YInc;
			giroModelo += KeyFrame[playIndex].giroModeloInc;
			i_curr_steps++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TipoCamara camaraActual = Isometrica;

void cambiarVistaCamara(Camera& camera) {


	if (camaraActual == TerceraPersona) {
		camaraActual = Aerea;
		camera.setVistaAerea(70.0f);
	}
	else if (camaraActual == Aerea) {
		camera.ultimaPosicionAerea = camera.getPosition();
		camaraActual = Isometrica; 
	}
	else {
		camaraActual = TerceraPersona;
		camera.setVistaTerceraPersona(bobPosition, distanceBehind, height, yawBob);
	}
}


int obtenercasilla(float movZ, float movX) {

	int casilla = 0;
	int intMovX = movX;
	int intMovZ = movZ;


	if (intMovX == 0 && intMovZ <= 180) {
		casilla = (movZ * 10) / 180;
	}
	else if (intMovZ > 180 && intMovX >= -180) {
		casilla = 10 + ((-movX * 10) / 180) -0.5;
	}
	else if (intMovX < -180 && intMovZ > 10) {
		casilla = 30 + (-movZ * 10) / 180;
	}
	else if (intMovZ < 10 && intMovX <= -10) {
		casilla = 40 + (movX * 10) / 180;
	}
	//printf("casillaActual \n %d", casillaActual);

	return casilla;

}

int nuevaCasilla;
void moverJugador(float deltaTime) {
	// Calcular la posici�n total en Z
	//float posicionZ = movZ;

	// Actualizamos casillaActual directamente usando obtenercasilla()
	 nuevaCasilla = obtenercasilla(movZ, movX);


	// Verificar si hemos cambiado de casilla
	if (nuevaCasilla != casillaActual) {
		if (nuevaCasilla < TOTAL_CASILLAS) {
			//printf("Casilla %d activada\n", nuevaCasilla);
		}
		if (casillaActual < TOTAL_CASILLAS) {
			//printf("Casilla %d desactivada\n", casillaActual);
		}
		casillaActual = nuevaCasilla;  // Actualiza la casilla actual
	}

	// Verificar en qu� casilla se encuentra el jugador
	if (casillaActual < TOTAL_CASILLAS) {
		

		// Detener el movimiento si alcanzamos la casilla objetivo
		if (casillaActual == casillaObjetivo) {
			// Detenemos el movimiento
			cicloCompleto = false;
			movZ = movZ; // O simplemente no hacer nada
			movX = movX; // O simplemente no hacer nada
			anguloBrazoDerecho = 0.0f;
			anguloBrazoIzquierdo = 0.0f;
			anguloPiernaDerecha = 0.0f;
			anguloPiernaIzquierda = 0.0f;
			return; // Salir de la funci�n si se ha alcanzado la casilla objetivo
		}
		else 
		{
			cicloCompleto = true;
		}

		float limiteInferior = (casillaActual / 10) * 190;
		float limiteSuperior = ((casillaActual / 10) + 1) * 190;


		if (estado == 0) { // avanzar adelante
			if (movZ <= 190.0f) {
				movZ += movOffset * deltaTime;
				//printf("avanza Adelante %f \n", movZ);
			}
			else {
				rotacionBob = 90.0f; // Rotar a la izquierda
				yawBob = -90.0f;
				estado = 1;
			}
		}

		if (estado == 1) { // avanzar izquierda
			if (movX >= -190.0f) {
				movX -= movOffset * deltaTime;
				//printf("avanza Izquierda %f \n", movX);
			}
			else {
				rotacionBob = 180.0f; // Rotar hacia atr�s
				yawBob = -180.0f;
				estado = 2;
			}
		}

		if (estado == 2) { // avanzar atr�s
			if (movZ >= -5.0f) {
				movZ -= movOffset * deltaTime;
				//printf("retrocede  %f \n", movZ);
			}
			else {
				rotacionBob = 270.0f; // Rotar a la derecha
				yawBob = -270.0f;
				estado = 3;
			}
		}

		if (estado == 3) { // avanzar derecha
			if (movX <= 0.0f) {
				movX += movOffset * deltaTime;
				//printf("retrocede  %f \n", movX);
			}
			else {
				rotacionBob = 0.0f; // Rotar hacia adelante
				yawBob = 0.0f;
				estado = 0; // Reiniciar ciclo
			}
		}
	}

	// Manejar la situaci�n cuando se supera el total de casillas
	if (casillaActual >= TOTAL_CASILLAS) {
		casillaActual = 0;
		movZ = 0;
		movX = 0;
	}
}

void verificarCasillas() {
	for (int i = 1; i < TOTAL_CASILLAS; i++) {
		if (banderas[i]) {
			//printf("Casilla %d: PASADA\n", i);
		}
		else if (casillaActual == i) {
			//printf("Casilla %d: ACTUAL (no pasada)\n", i);
		}
		else {
			//printf("Casilla %d: NO PASADA\n", i);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables para el ciclo dia/noche
float sunAngle = 0.0f; // angulo inicial
float dayNightSpeed = 0.00075f; // Velocidad del ciclo
bool isNight = true; // Banderas para indicar dia/noche
void UpdateSunDirection() {
	// Incrementar el angulo del sol para simular el paso del tiempo
	sunAngle += dayNightSpeed;

	// Reset del ciclo cada 360 grados
	if (sunAngle >= 360.0f) {
		sunAngle -= 360.0f;
	}

	// Calcular la direcci�n de la luz usando trigonometr�a
	float sunX = cos(sunAngle); // Movimiento horizontal de este a oeste
	float sunY = sin(sunAngle); // Movimiento vertical para simular el arco del sol
	float sunZ = -1.0f; // Mantener la luz en direcci�n negativa en Z

	// Actualizar la direcci�n de la luz principal
	mainLight.setDirection(glm::vec3(sunX, sunY, sunZ));

	// Actualizar la bandera de d�a/noche
	if (sunY > 0) {
		isNight = true;  // D�a
	}
	else {
		isNight = false; // Noche
	}
	if (isNight == true) {
		//printf("Es de noche\n");
	}
	else if (isNight == false) {
		//printf("Es de dia\n");

	}
	// Pasar la luz al shader
	shaderList[0].SetDirectionalLight(&mainLight);
}
std::vector<std::string> skyboxFaces;
bool lastIsNight = false; // Variable para rastrear el �ltimo estado
// Inicializacion de la skybox
void InitializeSkybox() {
	if (isNight) {
		skyboxFaces = {
			"Textures/Skybox/vz_sinister_ocean_right.png",
			"Textures/Skybox/vz_sinister_ocean_left.png",
			"Textures/Skybox/vz_sinister_ocean_down.png",
			"Textures/Skybox/vz_sinister_ocean_up.png",
			"Textures/Skybox/vz_sinister_ocean_back.png",
			"Textures/Skybox/vz_sinister_ocean_front.png"
		};
	}
	else {
		skyboxFaces = {
			"Textures/Skybox/vz_clear_ocean_right.png",
			"Textures/Skybox/vz_clear_ocean_left.png",
			"Textures/Skybox/vz_clear_ocean_down.png",
			"Textures/Skybox/vz_clear_ocean_up.png",
			"Textures/Skybox/vz_clear_ocean_back.png",
			"Textures/Skybox/vz_clear_ocean_front.png"
		};
	}

	skybox = Skybox(skyboxFaces); // Crea la skybox al inicio
}



int main()
{
	srand(time(NULL)); // Inicializa la semilla aleatoria
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();
	CreateObjects();
	CreateShaders();

	//KeyFrames Voltorb
	ReadKeyFramesFile();
	iniciarAnimacion();
	
	//KEYFRAME JP
	abrirArchivoAvion();
	leerFramesAvion();
	resetElementsAvion();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	//Modelos varios
	Postes_M = Model();
	Postes_M.LoadModel("Models/Postes.obj");
	Letrero_M = Model();
	Letrero_M.LoadModel("Models/letrerov3.obj");
	Monopoly_M = Model();
	Monopoly_M.LoadModel("Models/monopolyv4.obj");
	Ciudad_M = Model();
	Ciudad_M.LoadModel("Models/Ciudad.obj");
	Dado8 = Model();
	Dado8.LoadModel("Models/Dado8.obj");
	Dado4 = Model();
	Dado4.LoadModel("Models/Dado4.obj");
	Reflector_M = Model();
	Reflector_M.LoadModel("Models/Spotlight.obj");
	CuerpoChorizard_M = Model();
	CuerpoChorizard_M.LoadModel("Models/CuerpoChorizard.obj");
	AlaD_M = Model();
	AlaD_M.LoadModel("Models/CharAlaDer.obj");
	AlaI_M = Model();
	AlaI_M.LoadModel("Models/CharAlaIzq.obj");
	EscupiSalty_M = Model();
	EscupiSalty_M.LoadModel("Models/LaEscupideraDeSalty.obj");
	Puff_M = Model();
	Puff_M.LoadModel("Models/CasaPuff.obj");
	Mofle1_M = Model();
	Mofle1_M.LoadModel("Models/EdificioMofle.obj");
	Mofle2_M = Model();
	Mofle2_M.LoadModel("Models/EdificioMofleAlt.obj");
	SenalBus_M = Model();
	SenalBus_M.LoadModel("Models/CartelAutobus.obj");
	CasaBalde = Model();
	CasaBalde.LoadModel("Models/CasaBalde.obj");

	//Modelos Bob Espoonja 
	Bob = Model();
	Bob.LoadModel("Models/BobCompleto.obj");
	BobCuerpo = Model();
	BobCuerpo.LoadModel("Models/BobCuerpo.obj");
	BobBD = Model();
	BobBD.LoadModel("Models/BobBD.obj");
	BobBI = Model();
	BobBI.LoadModel("Models/BobBI.obj");
	BobPD = Model();
	BobPD.LoadModel("Models/BobPD.obj");
	BobPD.LoadModel("Models/BobPD.obj");
	BobPI = Model();
	BobPI.LoadModel("Models/BobPI.obj");
	Patricio = Model();
	Patricio.LoadModel("Models/Patricio.obj");
	Calamardo = Model();
	Calamardo.LoadModel("Models/Calamardo.obj");
	Plankton = Model();
	Plankton.LoadModel("Models/Plankton.obj");
	Arbol = Model();
	Arbol.LoadModel("Models/Arbol.obj");
	Kelp = Model();
	Kelp.LoadModel("Models/Kelp.obj");
	Flor = Model();
	Flor.LoadModel("Models/Flor.obj");
	Gary = Model();
	Gary.LoadModel("Models/Gary.obj");
	Medusa = Model();
	Medusa.LoadModel("Models/Medusa.obj");
	Pez = Model();
	Pez.LoadModel("Models/Pez.obj");
	CasaBob = Model();
	CasaBob.LoadModel("Models/CasaBob.obj");
	CasaPatricio = Model();
	CasaPatricio.LoadModel("Models/CasaPatricio.obj");
	CasaCalamardo = Model();
	CasaCalamardo.LoadModel("Models/CasaCalamardo.obj");
	Pez2 = Model();
	Pez2.LoadModel("Models/Pez2.obj");
	Crustaceo = Model();
	Crustaceo.LoadModel("Models/Crustaceo.obj");
	Burbuja = Model();
	Burbuja.LoadModel("Models/Burbuja.obj");
	Ostra = Model();
	Ostra.LoadModel("Models/Ostra.obj");
	Coral = Model();
	Coral.LoadModel("Models/Coral.obj");

	//Modelos Pokemon
	RedCabeza_M = Model();
	RedCabeza_M.LoadModel("Models/CabezaRed.obj");
	RedTorso_M = Model();
	RedTorso_M.LoadModel("Models/TorsoRed.obj");
	RedBI_M = Model();
	RedBI_M.LoadModel("Models/BrazoIzqRed.obj");
	RedBD_M = Model();
	RedBD_M.LoadModel("Models/BrazoDerRed.obj");
	RedPI_M = Model();
	RedPI_M.LoadModel("Models/PiernaIzqRed.obj");
	RedPD_M = Model();
	RedPD_M.LoadModel("Models/PiernaDerRed.obj");
	Lapras_M = Model();
	Lapras_M.LoadModel("Models/Lapras.obj");
	Charmander_M = Model();
	Charmander_M.LoadModel("Models/Charmander.obj");
	Jenny_M = Model();
	Jenny_M.LoadModel("Models/Jenny.obj");
	Joy_M = Model();
	Joy_M.LoadModel("Models/Joy.obj");
	James_M = Model();
	James_M.LoadModel("Models/James.obj");
	Jessie_M = Model();
	Jessie_M.LoadModel("Models/Jessie.obj");
	EdificioPoke_M = Model();
	EdificioPoke_M.LoadModel("Models/EdificioPoke.obj");
	GymPalace_M = Model();
	GymPalace_M.LoadModel("Models/GymPalace.obj");
	Giovanni_M = Model();
	Giovanni_M.LoadModel("Models/GiovanniSus.obj");
	Weezing_M = Model();
	Weezing_M.LoadModel("Models/Weezing.obj");
	Lechonk_M = Model();
	Lechonk_M.LoadModel("Models/Lechonky.obj");
	Azumarill_M = Model();
	Azumarill_M.LoadModel("Models/azumarill.obj");
	Electrode_M = Model();
	Electrode_M.LoadModel("Models/Electrode.obj");
	ColorfulPlant_M = Model();
	ColorfulPlant_M.LoadModel("Models/colorfulplant.obj");
	BerryTree_M = Model();
	BerryTree_M.LoadModel("Models/berrytree.obj");
	CentroPoke_M = Model();
	CentroPoke_M.LoadModel("Models/CentroPoke.obj");
	PineTree_M = Model();
	PineTree_M.LoadModel("Models/pinetree.obj");
	CasaPlayer_M = Model();
	CasaPlayer_M.LoadModel("Models/casaalbedo.obj");
	PokeMart_M = Model();
	PokeMart_M.LoadModel("Models/PokeMartV1.obj");
	Pikachu_M = Model();
	Pikachu_M.LoadModel("Models/Pikachu_A.obj");
	TreeOfLife_M = Model();
	TreeOfLife_M.LoadModel("Models/Tree Of Life.obj");
	Rhydon_M = Model();
	Rhydon_M.LoadModel("Models/Rhydon.obj");

	Voltorb_M = Model();
	Voltorb_M.LoadModel("Models/Voltorb.obj");

	////////////////////////////////////////////////////////////
	//Modelos Noche
	MonopolyNoche_M = Model();
	MonopolyNoche_M.LoadModel("Models/TableroNoche.obj");
	BobNoche = Model();
	BobNoche.LoadModel("Models/BobNoche.obj");
	PatricioNoche = Model();
	PatricioNoche.LoadModel("Models/PatricioNoche.obj");
	CalamardoNoche = Model();
	CalamardoNoche.LoadModel("Models/CalamardoNoche.obj");
	PlanktonNoche = Model();
	PlanktonNoche.LoadModel("Models/PlanktonNoche.obj");
	ArbolNoche = Model();
	ArbolNoche.LoadModel("Models/ArbolNoche.obj");
	KelpNoche = Model();
	KelpNoche.LoadModel("Models/KelpNoche.obj");
	FlorNoche = Model();
	FlorNoche.LoadModel("Models/FlorNoche.obj");
	GaryNoche = Model();
	GaryNoche.LoadModel("Models/GaryNoche.obj");
	MedusaNoche = Model();
	MedusaNoche.LoadModel("Models/MedusaNoche.obj");
	PezNoche = Model();
	PezNoche.LoadModel("Models/Pez1Noche.obj");
	CasaBobNoche = Model();
	CasaBobNoche.LoadModel("Models/CasaBobNoche.obj");
	CasaPatricioNoche = Model();
	CasaPatricioNoche.LoadModel("Models/CasaPatricioNoche.obj");
	CasaCalamardoNoche = Model();
	CasaCalamardoNoche.LoadModel("Models/CasaCalamardoNoche.obj");
	Pez2Noche = Model();
	Pez2Noche.LoadModel("Models/Pez2Noche.obj");
	CrustaceoNoche = Model();
	CrustaceoNoche.LoadModel("Models/CrustaceoNoche.obj");
	BurbujaNoche = Model();
	BurbujaNoche.LoadModel("Models/BurbujaNoche.obj");
	OstraNoche = Model();
	OstraNoche.LoadModel("Models/OstraNoche.obj");
	CoralNoche = Model();
	CoralNoche.LoadModel("Models/CoralNoche.obj");
	//Pokemon
	Lapras_MNoche = Model();
	Lapras_MNoche.LoadModel("Models/LaprasNoche.obj");
	Charmander_MNoche = Model();
	Charmander_MNoche.LoadModel("Models/CharmanderNoche.obj");
	Jenny_MNoche = Model();
	Jenny_MNoche.LoadModel("Models/JennyNoche.obj");
	Joy_MNoche = Model();
	Joy_MNoche.LoadModel("Models/JoyNoche.obj");
	James_MNoche = Model();
	James_MNoche.LoadModel("Models/JamesNoche.obj");
	Jessie_MNoche = Model();
	Jessie_MNoche.LoadModel("Models/JessieNoche.obj");
	EdificioPoke_MNoche = Model();
	EdificioPoke_MNoche.LoadModel("Models/CiudadNoche.obj");//
	GymPalace_MNoche = Model();
	GymPalace_MNoche.LoadModel("Models/GimnasioNoche.obj");
	Giovanni_MNoche = Model();
	Giovanni_MNoche.LoadModel("Models/GiovanniNoche.obj");
	Weezing_MNoche = Model();
	Weezing_MNoche.LoadModel("Models/WeezingNoche.obj");
	Lechonk_MNoche = Model();
	Lechonk_MNoche.LoadModel("Models/LechonkNoche.obj");
	Azumarill_MNoche = Model();
	Azumarill_MNoche.LoadModel("Models/AzumarillNoche.obj");
	Electrode_MNoche = Model();
	Electrode_MNoche.LoadModel("Models/ElectrodeNoche.obj");
	ColorfulPlant_MNoche = Model();
	ColorfulPlant_MNoche.LoadModel("Models/ArbustoNoche.obj");
	BerryTree_MNoche = Model();
	BerryTree_MNoche.LoadModel("Models/BayasNoche.obj");
	Pikachu_MNoche = Model();
	Pikachu_MNoche.LoadModel("Models/PikachuNoche.obj");
	TreeOfLife_MNoche = Model();
	TreeOfLife_MNoche.LoadModel("Models/VidaNoche.obj");
	PineTree_MNoche = Model();
	PineTree_MNoche.LoadModel("Models/PinoNoche.obj");
	BerryTree_MNoche = Model();
	BerryTree_MNoche.LoadModel("Models/BayasNoche.obj");
	CasaPlayer_MNoche = Model();
	CasaPlayer_MNoche.LoadModel("Models/CasaNoche.obj");
	PokeMart_MNoche = Model();
	PokeMart_MNoche.LoadModel("Models/TiendaNoche.obj");
	CentroPoke_MNoche = Model();
	CentroPoke_MNoche.LoadModel("Models/CentroNoche.obj");
	Rhydon_MNoche = Model();
	Rhydon_MNoche.LoadModel("Models/GoNoche.obj");
	////////////////////////////////////////////////////////////
	//Modelo Flash
	FlashB = Model();
	FlashB.LoadModel("Models/flash.obj");
	PieIzq = Model();
	PieIzq.LoadModel("Models/PieIzq.obj");
	PieDer = Model();
	PieDer.LoadModel("Models/PieDer.obj");
	ManoIzq = Model();
	ManoIzq.LoadModel("Models/ManoIzq.obj");
	ManoDer = Model();
	ManoDer.LoadModel("Models/ManoDer.obj");

	//Modelo Bote
	Bote = Model();
	Bote.LoadModel("Models/Bote.obj");
	LlantaIzquierda = Model();
	LlantaIzquierda.LoadModel("Models/LlantaIzquierda.obj");
	LlantaDelantera = Model();
	LlantaDelantera.LoadModel("Models/LlantaDelantera.obj");
	LlantaDerecha = Model();
	LlantaDerecha.LoadModel("Models/LlantaDerecha.obj");

	Cartel = Model();
	Cartel.LoadModel("Models/Cartel.obj");


	////////////////////////////////////////////////////////////////////////////////
	modelos[0] = Rhydon_M;
	modelos[1] = Bob;
	modelos[2] = Arbol;
	modelos[3] = Gary;
	modelos[4] = CasaBob;
	modelos[5] = Patricio;
	modelos[6] = Kelp;
	modelos[7] = Medusa;
	modelos[8] = CasaCalamardo;
	modelos[9] = Calamardo;
	modelos[10] = Flor;
	modelos[11] = Pez;
	modelos[12] = CasaPatricio;
	modelos[13] = Plankton;
	modelos[14] = Burbuja;
	modelos[15] = Crustaceo;
	modelos[16] = Pikachu_M;
	modelos[17] = Coral;
	modelos[18] = Pez2;
	modelos[19] = EdificioPoke_M;
	modelos[20] = Lapras_M;
	modelos[21] = Ostra;
	modelos[22] = Jessie_M;
	modelos[23] = GymPalace_M;
	modelos[24] = Charmander_M;
	modelos[25] = TreeOfLife_M;
	modelos[26] = James_M;
	modelos[27] = Electrode_M;
	modelos[28] = PineTree_M;
	modelos[29] = Giovanni_M;
	modelos[30] = CasaPlayer_M;
	modelos[31] = Weezing_M;
	modelos[32] = ColorfulPlant_M;
	modelos[33] = Jenny_M;
	modelos[34] = PokeMart_M;
	modelos[35] = Lechonk_M;
	modelos[36] = BerryTree_M;
	modelos[37] = Joy_M;
	modelos[38] = CentroPoke_M;
	modelos[39] = Azumarill_M;



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//Modelos Base Iluminacion
	BobBase = Model();
	BobBase.LoadModel("Models/BobEsponjaBase.obj");
	PatricioBase = Model();
	PatricioBase.LoadModel("Models/PatricioBase.obj");
	CalamardoBase = Model();
	CalamardoBase.LoadModel("Models/CalamardoBase.obj");
	PlanktonBase = Model();
	PlanktonBase.LoadModel("Models/PlanktonBase.obj");
	ArbolBase = Model();
	ArbolBase.LoadModel("Models/ArbolBase.obj");
	KelpBase = Model();
	KelpBase.LoadModel("Models/KelpBase.obj");
	FlorBase = Model();
	FlorBase.LoadModel("Models/FlorBase.obj");
	GaryBase = Model();
	GaryBase.LoadModel("Models/GaryBase.obj");
	MedusaBase = Model();
	MedusaBase.LoadModel("Models/MedusaBase.obj");
	PezBase = Model();
	PezBase.LoadModel("Models/Pez1Base.obj");
	CasaBobBase = Model();
	CasaBobBase.LoadModel("Models/CasaBobBase.obj");
	CasaPatricioBase = Model();
	CasaPatricioBase.LoadModel("Models/CasaPatricioBase.obj");
	CasaCalamardoBase = Model();
	CasaCalamardoBase.LoadModel("Models/CasaCalamardoBase.obj");
	Pez2Base = Model();
	Pez2Base.LoadModel("Models/Pez2Base.obj");
	CrustaceoBase = Model();
	CrustaceoBase.LoadModel("Models/CrustaceoBase.obj");
	BurbujaBase = Model();
	BurbujaBase.LoadModel("Models/BurbujaBase.obj");
	OstraBase = Model();
	OstraBase.LoadModel("Models/OstraBase.obj");
	CoralBase = Model();
	CoralBase.LoadModel("Models/CoralBase.obj");
	//Pokemon
	Lapras_MBase = Model();
	Lapras_MBase.LoadModel("Models/LaprasBase.obj");
	Charmander_MBase = Model();
	Charmander_MBase.LoadModel("Models/CharmanderBase.obj");
	Jenny_MBase = Model();
	Jenny_MBase.LoadModel("Models/JennyBase.obj");
	Joy_MBase = Model();
	Joy_MBase.LoadModel("Models/JoyBase.obj");
	James_MBase = Model();
	James_MBase.LoadModel("Models/JamesBase.obj");
	Jessie_MBase = Model();
	Jessie_MBase.LoadModel("Models/JessieBase.obj");
	EdificioPoke_MBase = Model();
	EdificioPoke_MBase.LoadModel("Models/CiudadBase.obj");//
	GymPalace_MBase = Model();
	GymPalace_MBase.LoadModel("Models/GimnasioBase.obj");
	Giovanni_MBase = Model();
	Giovanni_MBase.LoadModel("Models/GiovanniBase.obj");
	Weezing_MBase = Model();
	Weezing_MBase.LoadModel("Models/WeezingBase.obj");
	Lechonk_MBase = Model();
	Lechonk_MBase.LoadModel("Models/LechonkBase.obj");
	Azumarill_MBase = Model();
	Azumarill_MBase.LoadModel("Models/AzumarillBase.obj");
	Electrode_MBase = Model();
	Electrode_MBase.LoadModel("Models/ElectrodeBase.obj");
	ColorfulPlant_MBase = Model();
	ColorfulPlant_MBase.LoadModel("Models/ArbustoBase.obj");
	BerryTree_MBase = Model();
	BerryTree_MBase.LoadModel("Models/BayasBase.obj");
	CentroPoke_MBase = Model();
	CentroPoke_MBase.LoadModel("Models/CentroBase.obj");
	PineTree_MBase = Model();
	PineTree_MBase.LoadModel("Models/PinoBase.obj");
	CasaPlayer_MBase = Model();
	CasaPlayer_MBase.LoadModel("Models/CasaBase.obj");
	PokeMart_MBase = Model();
	PokeMart_MBase.LoadModel("Models/TiendaBase.obj");
	Pikachu_MBase = Model();
	Pikachu_MBase.LoadModel("Models/PikachuBase.obj");
	TreeOfLife_MBase = Model();
	TreeOfLife_MBase.LoadModel("Models/VidaBase.obj");
	Rhydon_MBase = Model();
	Rhydon_MBase.LoadModel("Models/GoBase.obj");

	//Modelos Cocinados
	BobCocinado = Model();
	BobCocinado.LoadModel("Models/BobCocinado.obj");
	PatricioCocinado = Model();
	PatricioCocinado.LoadModel("Models/PatricioCocinado.obj");
	CalamardoCocinado = Model();
	CalamardoCocinado.LoadModel("Models/CalamardoCocinado.obj");
	PlanktonCocinado = Model();
	PlanktonCocinado.LoadModel("Models/PlanktonCocinado.obj");
	ArbolCocinado = Model();
	ArbolCocinado.LoadModel("Models/ArbolCocinado.obj");
	KelpCocinado = Model();
	KelpCocinado.LoadModel("Models/KelpCocinado.obj");
	FlorCocinado = Model();
	FlorCocinado.LoadModel("Models/FlorCocinado.obj");
	GaryCocinado = Model();
	GaryCocinado.LoadModel("Models/GaryCocinado.obj");
	MedusaCocinado = Model();
	MedusaCocinado.LoadModel("Models/MedusaCocinado.obj");
	PezCocinado = Model();
	PezCocinado.LoadModel("Models/Pez1Cocinado.obj");
	CasaBobCocinado = Model();
	CasaBobCocinado.LoadModel("Models/CasaBobCocinado.obj");
	CasaPatricioCocinado = Model();
	CasaPatricioCocinado.LoadModel("Models/CasaPatricioCocinado.obj");
	CasaCalamardoCocinado = Model();
	CasaCalamardoCocinado.LoadModel("Models/CasaCalamardoCocinado.obj");
	Pez2Cocinado = Model();
	Pez2Cocinado.LoadModel("Models/Pez2Cocinado.obj");
	CrustaceoCocinado = Model();
	CrustaceoCocinado.LoadModel("Models/CrustaceoCocinado.obj");
	BurbujaCocinado = Model();
	BurbujaCocinado.LoadModel("Models/BurbujaCocinado.obj");
	OstraCocinado = Model();
	OstraCocinado.LoadModel("Models/OstraCocinado.obj");
	CoralCocinado = Model();
	CoralCocinado.LoadModel("Models/CoralCocinado.obj");
	//Pokemon
	Lapras_MCocinado = Model();
	Lapras_MCocinado.LoadModel("Models/LaprasCocinado.obj");
	Charmander_MCocinado = Model();
	Charmander_MCocinado.LoadModel("Models/CharmanderCocinado.obj");
	Jenny_MCocinado = Model();
	Jenny_MCocinado.LoadModel("Models/JennyCocinado.obj");
	Joy_MCocinado = Model();
	Joy_MCocinado.LoadModel("Models/JoyCocinado.obj");
	James_MCocinado = Model();
	James_MCocinado.LoadModel("Models/JamesCocinado.obj");
	Jessie_MCocinado = Model();
	Jessie_MCocinado.LoadModel("Models/JessieCocinado.obj");
	EdificioPoke_MCocinado = Model();
	EdificioPoke_MCocinado.LoadModel("Models/CiudadCocinado.obj");//
	GymPalace_MCocinado = Model();
	GymPalace_MCocinado.LoadModel("Models/GimnasioCocinado.obj");
	Giovanni_MCocinado = Model();
	Giovanni_MCocinado.LoadModel("Models/GiovanniCocinado.obj");
	Weezing_MCocinado = Model();
	Weezing_MCocinado.LoadModel("Models/WeezingCocinado.obj");
	Lechonk_MCocinado = Model();
	Lechonk_MCocinado.LoadModel("Models/LechonkCocinado.obj");
	Azumarill_MCocinado = Model();
	Azumarill_MCocinado.LoadModel("Models/AzumarillCocinado.obj");
	Electrode_MCocinado = Model();
	Electrode_MCocinado.LoadModel("Models/ElectrodeCocinado.obj");
	ColorfulPlant_MCocinado = Model();
	ColorfulPlant_MCocinado.LoadModel("Models/ArbustoCocinado.obj");
	BerryTree_MCocinado = Model();
	BerryTree_MCocinado.LoadModel("Models/BayasCocinado.obj");
	Pikachu_MCocinado = Model();
	Pikachu_MCocinado.LoadModel("Models/PikachuCocinado.obj");
	TreeOfLife_MCocinado = Model();
	TreeOfLife_MCocinado.LoadModel("Models/VidaCocinado.obj");
	PineTree_MCocinado = Model();
	PineTree_MCocinado.LoadModel("Models/PinoCocinado.obj");
	BerryTree_MCocinado = Model();
	BerryTree_MCocinado.LoadModel("Models/BayasCocinado.obj");
	CasaPlayer_MCocinado = Model();
	CasaPlayer_MCocinado.LoadModel("Models/CasaCocinado.obj");
	PokeMart_MCocinado = Model();
	PokeMart_MCocinado.LoadModel("Models/TiendaCocinado.obj");
	CentroPoke_MCocinado = Model();
	CentroPoke_MCocinado.LoadModel("Models/CentroCocinado.obj");
	Rhydon_MCocinado = Model();
	Rhydon_MCocinado.LoadModel("Models/GoCocinado.obj");
	////////////////////////////////////////////////////////////////////////////////////////
	modelosCooked[0] = Rhydon_MCocinado;
	modelosCooked[1] = BobCocinado;
	modelosCooked[2] = ArbolCocinado;
	modelosCooked[3] = GaryCocinado;
	modelosCooked[4] = CasaBobCocinado;
	modelosCooked[5] = PatricioCocinado;
	modelosCooked[6] = KelpCocinado;
	modelosCooked[7] = MedusaCocinado;
	modelosCooked[8] = CasaCalamardoCocinado;
	modelosCooked[9] = CalamardoCocinado;
	modelosCooked[10] = FlorCocinado;
	modelosCooked[11] = PezCocinado;
	modelosCooked[12] = CasaPatricioCocinado;
	modelosCooked[13] = PlanktonCocinado;
	modelosCooked[14] = BurbujaCocinado;
	modelosCooked[15] = CrustaceoCocinado;
	modelosCooked[16] = Pikachu_MCocinado;
	modelosCooked[17] = CoralCocinado;
	modelosCooked[18] = Pez2Cocinado;
	modelosCooked[19] = EdificioPoke_MCocinado;
	modelosCooked[20] = Lapras_MCocinado;
	modelosCooked[21] = OstraCocinado;
	modelosCooked[22] = Jessie_MCocinado;
	modelosCooked[23] = GymPalace_MCocinado;
	modelosCooked[24] = Charmander_MCocinado;
	modelosCooked[25] = TreeOfLife_MCocinado;
	modelosCooked[26] = James_MCocinado;
	modelosCooked[27] = Electrode_MCocinado;
	modelosCooked[28] = PineTree_MCocinado;
	modelosCooked[29] = Giovanni_MCocinado;
	modelosCooked[30] = CasaPlayer_MCocinado;
	modelosCooked[31] = Weezing_MCocinado;
	modelosCooked[32] = ColorfulPlant_MCocinado;
	modelosCooked[33] = Jenny_MCocinado;
	modelosCooked[34] = PokeMart_MCocinado;
	modelosCooked[35] = Lechonk_MCocinado;
	modelosCooked[36] = BerryTree_MCocinado;
	modelosCooked[37] = Joy_MCocinado;
	modelosCooked[38] = CentroPoke_MCocinado;
	modelosCooked[39] = Azumarill_MCocinado;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Luces
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.2f, 0.4f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//PointLight Bob
	pointLights[0] = PointLight(1.0f, 1.0f, 0.0f,  
		0.5f, 1.0f,   
		bobPosition.x, bobPosition.y + 2.0f, bobPosition.z, 
		0.1f, 0.05f, 0.01f); 
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//EsqFlor
	spotLights[0] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		110.0f, 1.5f, 110.0f,	
		-1.0f, -0.25f, -1.0f,
		1.0f, 0.001f, 0.002f,
		40.0f);
	spotLightCount++;
	//EsqRhydon
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		-110.0f, 1.5f, 110.0f,
		1.0f, -0.25f, -1.0f,
		1.0f, 0.001f, 0.002f,
		40.0f);
	spotLightCount++;
	//EsqCasa
	spotLights[2] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		-110.0f, 1.5f, -110.0f,
		1.0f, -0.25f, 1.0f,
		1.0f, 0.001f, 0.002f,
		40.0f);
	spotLightCount++;
	//EsqLapras
	spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		110.0f, 1.5f, -110.0f,
		-1.0f, -0.25f, 1.0f,
		1.0f, 0.001f, 0.002f,
		40.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rotacion de modelos
	enEspera = false;  // Control para saber si esta en espera
	moviendoHaciaArriba = true;  // Direccion inicial
	posModeloY = 0.0f;  // Posicion inicial del modelo
	tiempoEspera = 0.0f;  // Tiempo de espera
	anguloRotacion = 0.0f;  // Angulo de rotacion del modelo
	duracionFase = 3.0f;  // Duracion de cada etapa 
	alturaMin = 0.0f;  // Posicion Y mas baja
	alturaMax = -19.0f;  // Posicion Y mas alta
	velocidadRotacion = 360.0f;  // Grados por segundo
	velocidadMovimiento = 0.40f;  // Velocidad de desplazamiento vertical
	cicloCompleto = false;     // Variable de control para ciclo de movimiento unico

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Valores de transformaciones para las instancias
	//Traslacion
	glm::vec3 posiciones[TOTAL_CASILLAS] = {
		glm::vec3(-125.0f, -19.0f, 97.0f), //C0
		glm::vec3(-70.0f, -17.0f, 125.0f), //C1
		glm::vec3(-53.0f, -19.0f, 125.0f), //C2
		glm::vec3(-35.0f, -19.0f, 120.0f), //C3
		glm::vec3(-19.0f, -19.0f, 125.0f), //C4
		glm::vec3(0.0f, -19.0f, 120.0f), //C5
		glm::vec3(18.0f, -19.0f, 120.0f), //C6
		glm::vec3(35.0f, -19.0f, 120.0f), //C7
		glm::vec3(53.0f, -19.0f, 120.0f), //C8
		glm::vec3(71.0f, -19.0f, 120.0f), //C9
		glm::vec3(96.0f, -19.0f, 120.0f), //C10
		glm::vec3(123.0f, -19.0f, 76.0f), //C11
		glm::vec3(123.0f, -19.0f, 59.0f), //C12
		glm::vec3(123.0f, -19.0f, 41.0f), //C13
		glm::vec3(117.0f, -17.0f, 23.0f), //C14
		glm::vec3(125.0f, -19.0f, 5.0f),//C15
		glm::vec3(125.0f, -19.0f, -13.0f),//C16
		glm::vec3(123.0f, -19.0f, -31.0f),//C17
		glm::vec3(123.0f, -19.0f, -46.0f),//C18
		glm::vec3(123.0f, -19.0f, -67.0f),//C19
		glm::vec3(123.0f, -19.0f, -90.0f),//C20
		glm::vec3(73.0f, -19.0f, -120.0f),//C21
		glm::vec3(53.0f, -19.0f, -120.0f),//C22
		glm::vec3(35.0f, -19.0f, -120.0f),//C23
		glm::vec3(18.0f, -19.0f, -120.0f),//C24
		glm::vec3(0.0f, -19.0f, -120.0f),//C25
		glm::vec3(-19.0f, -19.0f, -120.0f),//C26
		glm::vec3(-35.0f, -17.0f, -120.0f),//C27
		glm::vec3(-53.0f, -19.0f, -120.0f),//C28
		glm::vec3(-70.0f, -19.0f, -120.0f),//C29
		glm::vec3(-125.0f, -19.0f, -90.0f),//C30
		glm::vec3(-125.0f, -19.0f, -67.0f),//C31
		glm::vec3(-125.0f, -19.0f, -50.0f),//C32
		glm::vec3(-125.0f, -19.0f, -31.0f),//C33
		glm::vec3(-125.0f, -19.0f, -13.0f),//C34
		glm::vec3(-125.0f, -19.0f, 5.0f),//C35
		glm::vec3(-125.0f, -19.0f, 23.0f),//C36
		glm::vec3(-125.0f, -19.0f, 40.0f),//C37
		glm::vec3(-125.0f, -19.0f, 59.0f),//C38
		glm::vec3(-125.0f, -19.0f, 76.0f),//C39
	};
	//Escala
	glm::vec3 escalas[TOTAL_CASILLAS] = {
	glm::vec3(12.0f, 12.0f, 12.0f),//C0
	glm::vec3(40.0f, 40.0f, 40.0f),//C1
	glm::vec3(2.0f, 2.0f, 2.0f),//C2
	glm::vec3(3.0f, 3.0f, 3.0f),//C3
	glm::vec3(3.0f, 3.0f, 3.0f),//C4
	glm::vec3(5.0f, 5.0f, 5.0f),//C5
	glm::vec3(6.0f, 6.0f, 6.0f),//C6
	glm::vec3(1.0f, 1.0f, 1.0f),//C7
	glm::vec3(4.0f, 4.0f, 4.0f),//C8
	glm::vec3(1.5f, 1.5f, 1.5f),//C9
	glm::vec3(1.5f, 1.5f, 1.5f),//C10
	glm::vec3(0.25f, 0.25f, 0.25f),//C11
	glm::vec3(4.5f, 4.5f, 4.5f),//C12
	glm::vec3(1.5f, 1.5f, 1.5f),//C13
	glm::vec3(0.75f, 0.75f, 0.75f),//C14
	glm::vec3(0.4f, 0.4f, 0.4f),//C15
	glm::vec3(8.0f, 8.0f, 8.0f),//C16
	glm::vec3(0.5f, 0.5f, 0.5f),//C17
	glm::vec3(0.75f, 0.75f, 0.75f),//C18
	glm::vec3(2.75f, 2.75f, 2.75f),//C19
	glm::vec3(12.0f, 12.0f, 12.0f),//C20
	glm::vec3(0.5f, 0.5f, 0.5f),//C21
	glm::vec3(0.5f, 0.5f, 0.5f),//C22
	glm::vec3(5.0f, 5.0f, 5.0f),//C23
	glm::vec3(6.0f, 6.0f, 6.0f),//C24
	glm::vec3(5.0f, 5.0f, 5.0f),//C25
	glm::vec3(0.8f, 0.8f, 0.8f),//C26
	glm::vec3(1.0f, 1.0f, 1.0f),//C27
	glm::vec3(1.0f, 1.0f, 1.0f),//C28
	glm::vec3(0.5f, 0.5f, 0.5f),//C29
	glm::vec3(1.0f, 1.0f, 1.0f),//C30
	glm::vec3(8.0f, 8.0f, 8.0f),//C31
	glm::vec3(2.75f, 2.75f, 2.75f),//C32
	glm::vec3(0.5f, 0.5f, 0.5f),//C33
	glm::vec3(1.0f, 1.0f, 1.0f),//C34
	glm::vec3(0.2f, 0.2f, 0.2f),//C35
	glm::vec3(0.5f, 0.5f, 0.5f),//C36
	glm::vec3(0.8f, 0.8f, 0.8f),//C37
	glm::vec3(1.0f, 1.0f, 1.0f),//C38
	glm::vec3(0.15f, 0.15f, 0.15f),//C39

	};
	float rotaciones[TOTAL_CASILLAS] = {
	90.0f, //C0
	90.0f, //C1
	0.0f,  //C2
	180.0f, //C3
	180.0f, //C4
	180.0f, //C5
	0.0f,  //C6
	0.0f,  //C7
	180.0f, //C8
	180.0f, //C9
	0.0f,  //C10
	-90.0f,  //C11
	90.0f,  //C12
	-90.0f,  //C13
	90.0f,  //C14
	-90.0f,  //C15
	-90.0f,  //C16
	-90.0f,  //C17
	-90.0f,  //C18
	0.0f,  //C19
	-90.0f,  //C20
	0.0f,  //C21
	0.0f,  //C22
	-90.0f,  //C23
	0.0f,  //C24
	0.0f,  //C25
	0.0f,  //C26
	0.0f,  //C27
	0.0f,  //C28
	-90.0f,  //C29
	0.0f,  //C30
	90.0f,  //C31
	90.0f,  //C32
	90.0f,  //C33
	90.0f,  //C34
	90.0f,  //C35
	90.0f,  //C36
	90.0f,  //C37
	90.0f,  //C38
	90.0f,  //C39

	};
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Modelos alrededor del tablero
	movObjX = 0.0f; //Movimiento en X del modelo
	movOffset = 0.5f; //Velocidad del desplazamiento
	rotacionCuerpos = 0.0f; //Rotacion de los modelos
	rotacionCuerposOffset = 20.0f; //Velocidad de la rotacion de los modelos
	a_b = true; //Bandera de posicion
	b_c = false; //Bandera de posicion
	c_d = false;//Bandera de posicion
	d_e = false; //Bandera de posicion
	rotacion = 0.0f; //Variable para la rotacion en cada esquina
	movObjZ = 0.0f;//Variable para el desplazamiento en Z del modelo

	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Dado
	movDado = 0.0f;
	randRotX = 0.0f; //Variable para guardar la rotacion en X
	randRotY = 0.0f;//Variable para guardar la rotacion en Y
	randRotZ = 0.0f;//Variable para guardar la rotacion en Z
	movOffsetDado = 1.0f; //Velocidad del dado

	randomRotationX = 0.0f;
	randomRotationY = 0.0f;
	randomRotationZ = 0.0f;
	DadoRot = true;
	tope = 0.01;

	caraDado8 = 0; // Para el dado de 8 caras
	caraDado4 = 0; // Para el dado de 4 caras
	sumaDados = 0;
	// Arreglo con las rotaciones posibles (X, Y, Z) para cada cara del decaedro
	struct Rotation {
		float x, y, z;
	};
	Rotation orientacionesDado4[4] = {
	{0.0f, 0.0f, 0.0f},   // Orientacion para la cara 1
	{-15.0f, 0.0f, 110.0f},  // Orientacion para la cara 2
	{65.0f, 0.0f, 225.0f}, // Orientacion para la cara 3
	{-135.0f, 0.0f, -295.0f}, // Orientacion para la cara 4


	};
	Rotation orientacionesDado8[8] = {
	{-55.0f, -45.0f, 0.0f},   // Orientacion para la cara 1

	{60.0f, -45.0f, -90.0f},  // Orientacion para la cara 2

	{60.0f, 45.0f, 90.0f}, // Orientacion para la cara 3

	{55.0f, 45.0f, 0.0f}, // Orientacion para la cara 4

	{55.0f, -45.0f, 0.0f}, // Orientacion para la cara 5

	{-60.0f, -45.0f, 90.0f}, // Orientacion para la cara 6

	{-60.0f, 45.0f, -90.0f}, // Orientacion para la cara 7

	{55.0f, 45.0f, 0.0f}, // Orientacion para la cara 8

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		UpdateSunDirection();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SkyBox
		if (isNight != lastIsNight) { // Si ha cambiado el estado de dia/noche
			InitializeSkybox(); // Reinicia la skybox
			lastIsNight = isNight; // Actualiza el estado anterior
		}
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);


		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		variacionAngulo += 0.5f * deltaTime;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bobPosition = glm::vec3(-90.0f + movZ, 1.0f, 95.0f + movX);
		//Camaras
		if (mainWindow.getsKeys()[GLFW_KEY_C]) {
			cambiarVistaCamara(camera);
			mainWindow.getsKeys()[GLFW_KEY_C] = false;
		}

		if (camaraActual == Aerea) {
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
		}
		else if (camaraActual == TerceraPersona) {
			GLfloat distanceBehind = 10.0f; 
			GLfloat height = 4.0f;         
			camera.setVistaTerceraPersona(bobPosition, distanceBehind, height, yawBob);
		}
		else if (camaraActual == Isometrica) {
			//camera.setVistaIsometrica(glm::vec3(-170.0f, 150.0f, 0.0f), 0.0f, -40.0f);
			float yawAngleI = -45.0f;
			float yawPitchI = -40.0f;
			camera.setVistaIsometrica(glm::vec3(-150.0f, 120.0f, 150.0f), yawAngleI, yawPitchI);
		
		}

		// Actualiza el control de la camara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);

		//Bob desplazamiento tablero
		if (mainWindow.getarrancar() == true) {

			//Movimiento animacion
			if (anguloBrazoDerecho >= 90.0f || anguloBrazoDerecho <= -20.0f) {
			moviendoAdelante = !moviendoAdelante;
		}

		float incremento = (moviendoAdelante ? 1 : -1) * (velocidadMovimientoBob * deltaTime);

		// Actualizar �ngulos con l�mites espec�ficos para brazos y piernas
		// Brazo derecho y pierna izquierda (mismo incremento)
		if (moviendoAdelante) {
			// L�mite superior del brazo derecho y pierna izquierda en movimiento hacia adelante
			anguloBrazoDerecho = std::min(anguloBrazoDerecho + incremento, 90.0f);
			anguloPiernaIzquierda = std::min(anguloPiernaIzquierda + incremento, 45.0f);
		}
		else {
			// L�mite inferior del brazo derecho y pierna izquierda en movimiento hacia atr�s
			anguloBrazoDerecho = std::max(anguloBrazoDerecho + incremento, -20.0f);
			anguloPiernaIzquierda = std::max(anguloPiernaIzquierda + incremento, -10.0f);
		}

		// Brazo izquierdo y pierna derecha (incremento en direcci�n opuesta)
		if (moviendoAdelante) {
			// L�mite superior del brazo izquierdo y pierna derecha en movimiento hacia adelante
			anguloBrazoIzquierdo = std::min(anguloBrazoIzquierdo - incremento, 90.0f);
			anguloPiernaDerecha = std::min(anguloPiernaDerecha - incremento, 45.0f);
		}
		else {
			// L�mite inferior del brazo izquierdo y pierna derecha en movimiento hacia atr�s
			anguloBrazoIzquierdo = std::max(anguloBrazoIzquierdo - incremento, -20.0f);
			anguloPiernaDerecha = std::max(anguloPiernaDerecha - incremento, -10.0f);
		}



			moverJugador(deltaTime);
			int casilla = obtenercasilla(movZ, movX);
			verificarCasillas();
			// Movimiento hacia adelante en Z
			

		}
		//PointLight Bob
			pointLights[0].SetPosition(bobPosition.x, bobPosition.y + 5.0f, bobPosition.z);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Dados

		int contador = mainWindow.getcontador();
		if (mainWindow.getcaer() == true && DadoRot == true && contador == 1) {
			movDado -= movOffsetDado * deltaTime;

			int indiceAleatorio = rand() % 8; //Dado de 8 caras
			int indiceAleatorio2 = rand() % 4;//Dado de 4 caras
			
			
			Rotation rotSelect = orientacionesDado8[indiceAleatorio];//8
			Rotation rotSelect2 = orientacionesDado4[indiceAleatorio2];//4

			// Asignar la rotacion predefinida
			//Dado de 8 caras
			randRotX = rotSelect.x;
			randRotY = rotSelect.y;
			randRotZ = rotSelect.z;
			//Dado de 4 caras
			randomRotationX = rotSelect2.x;
			randomRotationY = rotSelect2.y;
			randomRotationZ = rotSelect2.z;

			

			//Tirada
			if (mainWindow.getcaer() == true && movDado <= -52.0f)
			{
				caraDado4 = indiceAleatorio2 + 1; //Valor de la cara del dado de 4 caras
				caraDado8 = indiceAleatorio + 1; //Valor de la cara del dado de 8 caras
				printf("El dado d4 cayo: %i\n ", caraDado4);
				printf("El dado d8 cayo: %i\n", caraDado8);
				sumaDados = caraDado8 + caraDado4; //Suma de las caras de los dados que es la cantidad de casillas a recorrer
				printf("Recorre %i casillas\n ", sumaDados);
				if (casillaObjetivo + sumaDados <= 39) { //Si el valor de la cantidad de casillas a recorrer es menor a 39
					casillaObjetivo =casillaObjetivo + sumaDados; //Se hace la suma acumulativa de casillas
					printf("Ve a la casilla: %i\n", casillaObjetivo);
				}
				else {
					// Si excede 39, reiniciamos la variable casilla objetivo y sumamos las casillas pendientes a recorrer
					casillaObjetivo = ((casillaObjetivo + sumaDados) % 40);
					printf("CasillaObjetivo: %i\n", casillaObjetivo);

				}
			}
			else
			{
				//Se reinician los valores de las caras de los dados para que no se acumule aqui
				caraDado4 = 0;
				caraDado8 = 0;
			}
		

			if (movDado <= -52.0f) {
				movDado = -52.0f; //El dado llega a su posici�n final
				DadoRot = false; //La bandera de rotacion se desactiva
				mainWindow.setcaer(false); //Se deshabilita la caida
			}
		}
		if (mainWindow.getcaer() == false && DadoRot == false && contador == 0) {
			movDado += movOffsetDado * deltaTime;
			if (movDado < tope) {
				movDado = 0.0f; //El dado regresa a su posici�n inicial
				DadoRot = true; //La bandera de rotacion se activa
				mainWindow.setcaer(true);//Se habilita la caida


			}
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Movimiento de los modelos del tablero

		if (mainWindow.getarrancar() == true) {
			if (enEspera == false) {
				if (moviendoHaciaArriba) {
					// Mover hacia arriba
					if (posModeloY > alturaMax&&cicloCompleto==false) {
						posModeloY -= velocidadMovimiento * deltaTime;
						anguloRotacion += velocidadRotacion + 3.0 * deltaTime;
						if (anguloRotacion >= 360.0f) {
							anguloRotacion -= 360.0f;  // Mantener el angulo entre 0 y 360
						}
					}
					else {
						//Cuando llega a la posicion mas alta
						moviendoHaciaArriba = false;
						enEspera = true;
						tiempoEspera = now;
						anguloRotacion = 0.0f;
					}
				}
				else if (!moviendoHaciaArriba) {
					// Mover hacia abajo
					if (posModeloY < alturaMin) {
						posModeloY += velocidadMovimiento * deltaTime;
						anguloRotacion += velocidadRotacion + 3.0 * deltaTime;
						if (anguloRotacion >= 360.0f) {
							anguloRotacion -= 360.0f;  // Mantener el angulo entre 0 y 360
						}
					}
					else {
						// Cuando llega a la posicion mas baja
						cicloCompleto = true;
						enEspera = true;
						tiempoEspera = now;
						anguloRotacion = 0.0f;

					}
				}
			}
			else {
				// En espera
				if (now - tiempoEspera > duracionFase) {
					enEspera = false;
				}
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Movimiento de Charizard alrededeor del tablero
			if (a_b == true) {
				if (movObjX > -320.0f) {
					movObjX -= movOffset * deltaTime;  // Avanza de X a -X
				}
				else {
					a_b = false;
					b_c = true;
					rotacion += 270.0f;
				}
			}
			else if (b_c == true) {
				if (movObjZ > -320.0f) {
					movObjZ -= movOffset * deltaTime;  // Avanza de Z a -Z
				}
				else {
					b_c = false;
					c_d = true;
					rotacion += 270.0f;
				}
			}
			else if (c_d == true) {
				if (movObjX < -3.0f) {
					movObjX += movOffset * deltaTime;  // Avanza de -X a X
				}
				else {
					c_d = false;
					d_e = true;
					rotacion += 270.0f;
				}
			}
			else if (d_e == true) {
				if (movObjZ < 3.0f) {

					movObjZ += movOffset * deltaTime;  //Avanza de -Z 
				}
				else {
					d_e = false;
					a_b = true;
					rotacion += 270.0f;
				}
			}
			else if (a_b == true) {
				a_b = true;
				b_c = false;
				c_d = false;
				d_e = false;
				movObjX = 0.0f;  // Reset de la posicion
				movObjZ = 0.0f;
				rotacion = 0.0f;   // Reset de la rotacion
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Movimiento del Bote alrededor del tablero
			if (a_b_bote == true) {
				if (movObjX_bote < 3.0f) {
					movObjX_bote += movOffset * deltaTime;  // Avanza de inferior derecha a inferior izquierda
					rotllanta += rotllantaOffset * deltaTime;

				}
				else {
					a_b_bote = false;
					b_c_bote = true;
					rotacion_bote = -180.0f;
				}
			}
			else if (b_c_bote == true) {
				if (movObjZ_bote < 3.0f) {
					movObjZ_bote += movOffset * deltaTime;  // Avanza de inferior izquierda a superior izquierda
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					b_c_bote = false;
					c_d_bote = true;
					rotacion_bote = -270.0f;
				}
			}
			else if (c_d_bote == true) {
				if (movObjX_bote > -300.0f) {
					movObjX_bote -= movOffset * deltaTime;  // Avanza de superior izquierda a superior derecha
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					c_d_bote = false;
					d_e_bote = true;
					rotacion_bote = 0.0f;
				}
			}
			else if (d_e_bote == true) {
				if (movObjZ_bote > -320.0f) {
					movObjZ_bote -= movOffset * deltaTime;  // Avanza de superior derecha a inferior derecha
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					d_e_bote = false;
					a_b_bote = true;
					rotacion_bote = -90.0f;
				}
			}
			else if (a_b_bote == true) {
				a_b_bote = true;
				b_c_bote = false;
				c_d_bote = false;
				d_e_bote = false;
				movObjX_bote = -320.0f;  // Reset de la posicion a inferior derecha
				movObjZ_bote = -320.0f;
				rotacion_bote = -180.0f;    // Reset de la rotacion
			}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bob
		 if (camaraActual == TerceraPersona) {    
        camera.setVistaTerceraPersona(bobPosition, distanceBehind, height, yawBob);
    }
		
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//KEYFRAMES
		animate();
		animateAvion();
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//informacion en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//informacion al shader de fuentes de iluminacion
		shaderList[0].SetDirectionalLight(&mainLight);
		if (isNight == true) {//Es de noche, entonces mandamos las luces al shader
			// Activar solo la spotlight correspondiente según las casillas de las esquinas
			if (casillaObjetivo == 0 && nuevaCasilla == 0) {
				// Envía spotlight[2]
				shaderList[0].SetSpotLights(&spotLights[1], 1);
				//printf("Activando spotlight[2]\n");
			}
			else if (casillaObjetivo == 10 && nuevaCasilla == 10) {
				// Envía spotlight[1]
				shaderList[0].SetSpotLights(&spotLights[0], 1);
				//printf("Activando spotlight[1]\n");
			}
			else if (casillaObjetivo == 20 && nuevaCasilla == 20) {
				// Envía solo spotlight[4]
				shaderList[0].SetSpotLights(&spotLights[3], 1);
				//printf("Activando spotlight[4]\n");
			}
			else if (casillaObjetivo == 30 && nuevaCasilla == 30) {
				// Envía solo spotlight[3]
				shaderList[0].SetSpotLights(&spotLights[2], 1);
				//printf("Activando spotlight[3]\n");
			}

			// Envía las point lights al shader
			shaderList[0].SetPointLights(pointLights, pointLightCount);
			
		}
		else if (isNight == false) {
			//printf("No Luces\n");
			shaderList[0].SetPointLights(nullptr, 0); // No envia las point lights
			shaderList[0].SetSpotLights(nullptr, 0);  // No envia las spot lights
		}
		


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Instancias

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux1(1.0);
		glm::mat4 modelaux2(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//Dado de 8 caras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, movDado + 55.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		if (mainWindow.getcaer() == true || movDado <= -52.0f) {
			// Aplicar rotaciones aleatorias
			model = glm::rotate(model, glm::radians(randRotX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(randRotY), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(randRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado8.RenderModel();


		//Dado de 4 caras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, movDado + 55.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		if (mainWindow.getcaer() == true || movDado <= -52.0f) {
			// Aplicar rotaciones aleatorias
			model = glm::rotate(model, glm::radians(randomRotationX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(randomRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(randomRotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado4.RenderModel();

		//Ciudad
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(467.5f, -35.5f, 282.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ciudad_M.RenderModel();

		model = glm::mat4(1.0);
		posModelo = glm::vec3(posXModelo + moxModelo_X, posYModelo + moxModelo_Y, posZModelo);
		model = glm::translate(model, posModelo);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, giroModelo * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Voltorb_M.RenderModel();

		//Flash Bob esponja
		//Flash
		glm::mat4 modelFlash = glm::mat4(1.0);
		modelFlash = glm::translate(modelFlash, glm::vec3(-50.0f, 4.0f, (60.0f + movAvion_x - movAvion_y)));
		modelFlash = glm::scale(modelFlash, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelFlash));
		FlashB.RenderModel();

		//Flash Mano Derecha
		glm::mat4 modelManoDerecha = modelFlash;
		modelManoDerecha = glm::translate(modelManoDerecha, glm::vec3(0.1f, 0.3f, -0.05f));
		modelManoDerecha = glm::rotate(modelManoDerecha, giroAvion * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelManoDerecha));
		ManoDer.RenderModel();

		//Flash Mano Izquierda
		glm::mat4 modelManoIzquierda = modelFlash;
		modelManoIzquierda = glm::translate(modelManoIzquierda, glm::vec3(-0.15f, 0.32f, -0.05f));
		modelManoIzquierda = glm::rotate(modelManoIzquierda, giroAvion * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelManoIzquierda));
		ManoIzq.RenderModel();

		//Flash Pie Izquierdo
		glm::mat4 modelPieIzquierdo = modelFlash;
		modelPieIzquierdo = glm::translate(modelPieIzquierdo, glm::vec3(-0.1f, 0.15f, -0.02f));
		modelPieIzquierdo = glm::rotate(modelPieIzquierdo, giroAvion * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPieIzquierdo));
		PieIzq.RenderModel();

		//Flash Pie Derecho
		glm::mat4 modelPieDerecho = modelFlash;
		modelPieDerecho = glm::translate(modelPieDerecho, glm::vec3(0.02f, 0.12f, 0.0f));
		modelPieDerecho = glm::rotate(modelPieDerecho, giroAvion * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPieDerecho));
		PieDer.RenderModel();




		//Reflectores
		//EsqFlor
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(110.0f, 1.5f, 110.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector_M.RenderModel();
		//EsqRhydon
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 1.5f, 110.0f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector_M.RenderModel();
		//EsqCasa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 1.5f, -110.0f));
		model = glm::rotate(model, -225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector_M.RenderModel();
		//EsqLapras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(110.0f, 1.5f, -110.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector_M.RenderModel();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (isNight == false) {
			//Tablero
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Monopoly_M.RenderModel();

			//Creacion Casillas Tablero
			//Go
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Rhydon_MBase.RenderModel();

			//Bob Esponja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BobBase.RenderModel();

			//Arbol
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolBase.RenderModel();

			//Gary
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GaryBase.RenderModel();

			//Casa Bob Esponja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaBobBase.RenderModel();

			//Patricio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PatricioBase.RenderModel();

			//Kelp
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			KelpBase.RenderModel();

			//Medusa
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MedusaBase.RenderModel();

			//Casa Calamardo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaCalamardoBase.RenderModel();

			//Calamardo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CalamardoBase.RenderModel();

			//Flor
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			FlorBase.RenderModel();

			//Pez1
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PezBase.RenderModel();

			//Casa Patricio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaPatricioBase.RenderModel();

			//Plankton
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PlanktonBase.RenderModel();

			//Burbuja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BurbujaBase.RenderModel();

			//Crustaceo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CrustaceoBase.RenderModel();

			//Pikachu
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pikachu_MBase.RenderModel();

			//Coral
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CoralBase.RenderModel();

			//Pez2
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pez2Base.RenderModel();

			//Ciudad
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EdificioPoke_MBase.RenderModel();

			//Lapras
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Lapras_MBase.RenderModel();

			//Ostra
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			OstraBase.RenderModel();

			//Jessie
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Jessie_MBase.RenderModel();

			//Gimnasio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GymPalace_MBase.RenderModel();

			//Charmander
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Charmander_MBase.RenderModel();

			//Arbol Vida
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			TreeOfLife_MBase.RenderModel();

			//James
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			James_MBase.RenderModel();

			//Electrode
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Electrode_MBase.RenderModel();

			//Pino
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PineTree_MBase.RenderModel();

			//Giovanni
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Giovanni_MBase.RenderModel();

			//Casa
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaPlayer_MBase.RenderModel();

			//Weezing
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Weezing_MBase.RenderModel();

			//Arbusto
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ColorfulPlant_MBase.RenderModel();

			//Jenny
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Jenny_MBase.RenderModel();

			//Tienda
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PokeMart_MBase.RenderModel();

			//Lechonk
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Lechonk_MBase.RenderModel();

			//Bayas
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BerryTree_MBase.RenderModel();

			//Joy
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Joy_MBase.RenderModel();

			//Centro
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CentroPoke_MBase.RenderModel();

			//Azumarill
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Azumarill_MBase.RenderModel();
		}
		else if (isNight == true) {
			//Tablero
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MonopolyNoche_M.RenderModel();

			//Creacion Casillas Tablero
			//Go
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Rhydon_MNoche.RenderModel();

			//Bob Esponja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BobNoche.RenderModel();

			//Arbol
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolNoche.RenderModel();

			//Gary
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GaryNoche.RenderModel();

			//Casa Bob Esponja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaBobNoche.RenderModel();

			//Patricio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PatricioNoche.RenderModel();

			//Kelp
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			KelpNoche.RenderModel();

			//Medusa
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MedusaNoche.RenderModel();

			//Casa Calamardo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaCalamardoNoche.RenderModel();

			//Calamardo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CalamardoNoche.RenderModel();

			//Flor
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			FlorNoche.RenderModel();

			//Pez1
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PezNoche.RenderModel();

			//Casa Patricio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaPatricioNoche.RenderModel();

			//Plankton
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PlanktonNoche.RenderModel();

			//Burbuja
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BurbujaNoche.RenderModel();

			//Crustaceo
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CrustaceoNoche.RenderModel();

			//Pikachu
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pikachu_MNoche.RenderModel();

			//Coral
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CoralNoche.RenderModel();

			//Pez2
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pez2Noche.RenderModel();

			//Ciudad
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EdificioPoke_MNoche.RenderModel();

			//Lapras
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Lapras_MNoche.RenderModel();

			//Ostra
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			OstraNoche.RenderModel();

			//Jessie
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Jessie_MNoche.RenderModel();

			//Gimnasio
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GymPalace_MNoche.RenderModel();

			//Charmander
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Charmander_MNoche.RenderModel();

			//Arbol Vida
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			TreeOfLife_MNoche.RenderModel();

			//James
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			James_MNoche.RenderModel();

			//Electrode
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Electrode_MNoche.RenderModel();

			//Pino
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PineTree_MNoche.RenderModel();

			//Giovanni
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Giovanni_MNoche.RenderModel();

			//Casa
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CasaPlayer_MNoche.RenderModel();

			//Weezing
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Weezing_MNoche.RenderModel();

			//Arbusto
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ColorfulPlant_MNoche.RenderModel();

			//Jenny
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Jenny_MNoche.RenderModel();

			//Tienda
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PokeMart_MNoche.RenderModel();

			//Lechonk
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Lechonk_MNoche.RenderModel();

			//Bayas
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BerryTree_MNoche.RenderModel();

			//Joy
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Joy_MNoche.RenderModel();

			//Centro
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CentroPoke_MNoche.RenderModel();

			//Azumarill
			model = glm::mat4(1.0);
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Azumarill_MNoche.RenderModel();
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//MODELOS BOB ESPONJA
		// Cuerpo de Bob Esponja
		glm::mat4 modelCuerpo = glm::mat4(1.0);
		modelCuerpo = glm::translate(modelCuerpo, bobPosition); 
		modelCuerpo = glm::scale(modelCuerpo, glm::vec3(3.0f, 3.0f, 3.0f));
		if (!avanzaX || !avanzaZ) {
			modelCuerpo = glm::rotate(modelCuerpo, glm::radians(rotacionBob), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar sobre el eje X
		}
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCuerpo));
		BobCuerpo.RenderModel();

		// Brazo Derecho 
		glm::mat4 modelBrazoDerecho = modelCuerpo;
		modelBrazoDerecho = glm::translate(modelBrazoDerecho, glm::vec3(-1.082f, 1.476f, 0.548f));
		modelBrazoDerecho = glm::rotate(modelBrazoDerecho, glm::radians(anguloBrazoDerecho), glm::vec3(0.0f, 0.0f, 1.0f)); // Oscilacion del brazo
		modelBrazoDerecho = glm::scale(modelBrazoDerecho, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBrazoDerecho));
		BobBD.RenderModel();

		// Brazo Izquierdo 
		glm::mat4 modelBrazoIzquierdo = modelCuerpo;
		modelBrazoIzquierdo = glm::translate(modelBrazoIzquierdo, glm::vec3(-1.085f, 1.46f, -0.228f));
		modelBrazoIzquierdo = glm::rotate(modelBrazoIzquierdo, glm::radians(anguloBrazoIzquierdo), glm::vec3(0.0f, 0.0f, 1.0f)); // Oscilacion del brazo
		modelBrazoIzquierdo = glm::scale(modelBrazoIzquierdo, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBrazoIzquierdo));
		BobBI.RenderModel();

		// Pierna Derecha
		glm::mat4 modelPiernaDerecha = modelCuerpo;
		modelPiernaDerecha = glm::translate(modelPiernaDerecha, glm::vec3(-1.068f, 1.057f, 0.316f));
		modelPiernaDerecha = glm::rotate(modelPiernaDerecha, glm::radians(anguloPiernaDerecha), glm::vec3(0.0f, 0.0f, 1.0f)); // Oscilacion de la pierna
		modelPiernaDerecha = glm::scale(modelPiernaDerecha, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPiernaDerecha));
		BobPD.RenderModel();

		// Pierna Izquierda 
		glm::mat4 modelPiernaIzquierda = modelCuerpo;
		modelPiernaIzquierda = glm::translate(modelPiernaIzquierda, glm::vec3(-1.059f, 1.056f, 0.016f));
		modelPiernaIzquierda = glm::rotate(modelPiernaIzquierda, glm::radians(anguloPiernaIzquierda), glm::vec3(0.0f, 0.0f, 1.0f)); // Oscilacion de la pierna
		modelPiernaIzquierda = glm::scale(modelPiernaIzquierda, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPiernaIzquierda));
		BobPI.RenderModel();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//POKEMON
		//Red
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 5.0f, 130.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedTorso_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.2f, -2.8f, -0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedPD_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.84f, -2.6f, -0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedPI_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.051f, 1.75f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedBD_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.043f, 1.65f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedBI_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.35f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RedCabeza_M.RenderModel();

	

	
//////////////////////////MODELOS TABLERO/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static int casillaModelo = -1;
	for (int i = 0; i < TOTAL_CASILLAS; i++) {
		if (casillaObjetivo == i && nuevaCasilla==i) {
			if (casillaModelo != i) 
			{
				moviendoHaciaArriba = true;
				cicloCompleto = false;
				enEspera = false;
				casillaModelo = i;
			}
			model = glm::mat4(1.0);
			// Aplicar traslacion, escala y rotacion especificos para cada modelo
			model = glm::translate(model, posiciones[i] + glm::vec3(0.0f, -posModeloY, 0.0f));
			model = glm::scale(model, escalas[i]);
			model = glm::rotate(model, glm::radians(rotaciones[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (posModeloY < alturaMin || posModeloY > alturaMax) {
				model = glm::rotate(model, glm::radians(anguloRotacion), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotar sobre el eje X
			}
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			modelos[i].RenderModel();

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			modelosCooked[i].RenderModel();
	}
}		

	////////////////////////MODELOS ALREDEDOR DEL TABLERO///////////////////////////////////////////////////////////////////////////////////////////////////////
		//Cuerpo Charizard
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160, 5.0f - cos(glm::radians(variacionAngulo * 4)), 160.0));
		model = glm::translate(model, glm::vec3(movObjX, 0.0f, movObjZ));
		model = glm::rotate(model, glm::radians(rotacion), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoChorizard_M.RenderModel();
		//Ala derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.35f, 1.27f, 0.0f));
		model = glm::rotate(model, cos(glm::radians(variacionAngulo * 4)), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaD_M.RenderModel();
		//Ala izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.35f, 1.27f, 0.0f));
		model = glm::rotate(model, -cos(glm::radians(variacionAngulo * 4)), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaI_M.RenderModel();
		//Casa1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190, 1.5f, 90.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EscupiSalty_M.RenderModel();
		//Casa2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190, 1.5f, 30.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.6f, 2.6f, 2.6f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mofle2_M.RenderModel();
		//Casa3 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-190, 1.5f, 0.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasaBalde.RenderModel();

		//Senal bus
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, 1.5f, 130.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f,3.0f,3.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SenalBus_M.RenderModel();

		//Cartel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, -20.0f, -180.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cartel.RenderModel();

		//Bote
		glm::mat4 modelBote = glm::mat4(1.0);
		modelBote = glm::translate(modelBote, glm::vec3(150.0f + movObjX_bote, 3.0f, 160.0f + movObjZ_bote));
		modelBote = glm::scale(modelBote, glm::vec3(0.3f, 0.3f, 0.3f));
		modelBote = glm::rotate(modelBote, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelBote = glm::rotate(modelBote, glm::radians(rotacion_bote), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBote));
		Bote.RenderModel();

		//Llanta Derecha
		glm::mat4 modelLlantaDerecha = modelBote;
		modelLlantaDerecha = glm::translate(modelLlantaDerecha, glm::vec3(-15.0f, 1.5f, -10.0f));
		modelLlantaDerecha = glm::rotate(modelLlantaDerecha, giroAvion * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelLlantaDerecha = glm::scale(modelLlantaDerecha, glm::vec3(1.5f, 1.5f, 1.5f));
		modelLlantaDerecha = glm::rotate(modelLlantaDerecha, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelLlantaDerecha));
		LlantaDerecha.RenderModel();

		//Llanta Izquierda
		glm::mat4 modelLlantaIzquierda = modelBote;
		modelLlantaIzquierda = glm::translate(modelLlantaIzquierda, glm::vec3(5.0f, 1.5f, -10.0f));
		modelLlantaIzquierda = glm::rotate(modelLlantaIzquierda, giroAvion * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		modelLlantaIzquierda = glm::scale(modelLlantaIzquierda, glm::vec3(1.5f, 1.5f, 1.5f));
		modelLlantaIzquierda = glm::rotate(modelLlantaIzquierda, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelLlantaIzquierda));
		LlantaIzquierda.RenderModel();

		//Llanta Delantera
		glm::mat4 modelLlantaDelantera = modelBote;
		modelLlantaDelantera = glm::translate(modelLlantaDelantera, glm::vec3(-4.0f, 1.5f, 20.0f));
		modelLlantaDelantera = glm::rotate(modelLlantaDelantera, giroAvion * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelLlantaDelantera = glm::scale(modelLlantaDelantera, glm::vec3(1.5f, 1.5f, 1.5f));
		modelLlantaDelantera = glm::rotate(modelLlantaDelantera, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelLlantaDelantera));
		LlantaDelantera.RenderModel();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}

