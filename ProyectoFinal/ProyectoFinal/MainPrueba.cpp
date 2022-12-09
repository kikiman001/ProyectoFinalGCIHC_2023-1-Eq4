#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 4.0f, - 15.381f));

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float rotC = -45.0f;
float UpC = 0.019;
float DownC = -0.023;
float Pinzas = 12;
float movCamera = 0.0f;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(0.0f, 0.0f, 0.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;
bool myanim = true;

//Recorrido pez globo
bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = true;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;

bool recorrido7 = false;
bool recorrido8 = false;

float rotKit = 90.0;
float rotTapa = 0.0f;
float Abrir = 0.0f;
const float r= 9.0f;
const float Radio = (3.14159f) / 180.0f;

//Peces up and down
float movY = 0.0;
//Animacion agua
float tiempo = 1.0f;
float speed = 1.0f;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotDI1 = 0, rotDI2 = 0, rotDI3 = 0, rotDI4 = 0, rotHands = 0;
float Aletas =0.0f;
#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ

	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float rotDI1;
	float rotDI2;
	float rotDI3;
	float rotDI4;
	float rotHands;

	float rotInc;
	float rotInc2;//incremento para rotDer
	float rotInc3;
	float rotInc4;
	float rotInc5;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 9;
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(posX,posY,posZ),
	glm::vec3(-0.149f,3.317f, 0.0f),
	glm::vec3(0.0f,0.175f, 3.155f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

glm::vec3 LightP1;
glm::vec3 LightP2 = glm::vec3(0);
glm::vec3 LightP3 = glm::vec3(0);
glm::vec3 LightP4 = glm::vec3(0);


float movKitX = 0.0;
float movKitY = 0.0;
float movKitZ = 0.0;


void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotDI1 = KeyFrame[0].rotDI1;
	rotDI2 = KeyFrame[0].rotDI2;
	rotDI3 = KeyFrame[0].rotDI3;
	rotDI4 = KeyFrame[0].rotDI4;

	rotHands = KeyFrame[0].rotHands;
	rotC = 1.0;

}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotDI1 - KeyFrame[playIndex].rotDI1) / i_max_steps;

	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotDI2 - KeyFrame[playIndex].rotDI2) / i_max_steps;

	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotDI3 - KeyFrame[playIndex].rotDI3) / i_max_steps;

	KeyFrame[playIndex].rotInc5 = (KeyFrame[playIndex + 1].rotDI4 - KeyFrame[playIndex].rotDI4) / i_max_steps;

	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotHands - KeyFrame[playIndex].rotHands) / i_max_steps;

}




int main()
{
	// Init GLFW
	glfwInit();




	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader Anim2("Shaders/anim2.vs", "Shaders/anim2.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");


	Model DomoC((char*)"Models/Fachada_E/DomoCristal.obj");
	Model DomoM((char*)"Models/Fachada_E/DomoMetal.obj");
	Model DomoI((char*)"Models/Fachada_E/DomoIntCristal.obj");
	Model Puerta((char*)"Models/Fachada_E/Puerta.obj");
	Model PuertaC((char*)"Models/Fachada_E/PuertaCristal.obj");
	//Model Water((char*)"Models/Water/Water.obj");

	Model Arena((char*)"Models/Fachada_E/PisoArena.obj");

	Model PeceraC((char*)"Models/Pecera/PeceraCristal.obj");
	Model Pecera((char*)"Models/Pecera/Pecera.obj");
	Model Tank((char*)"Models/Pecera/Tank.obj");

	Model Piso((char*)"Models/Piso/Piso.obj");

	Model Brain((char*)"Models/Coral brain/coralBrain.obj");
	Model CHoja((char*)"Models/Coral hoja/CoralHoja.obj");
	Model Pared((char*)"Models/Pared/Pared.obj");
	Model Roca((char*)"Models/Roca/Roca.obj");

	Model Puffer((char*)"Models/Puffer/Puffer.obj");
	Model PufferD((char*)"Models/Puffer/PufferDer.obj");
	Model PufferI((char*)"Models/Puffer/PufferIzq.obj");
	Model PufferC((char*)"Models/Puffer/PufferCola.obj");

	Model Volcan((char*)"Models/Volcan/Volcan.obj");
	
	Model Cofre((char*)"Models/Cofre/CofreBox.obj");
	Model CofreT((char*)"Models/Cofre/CofreTapa.obj");

	Model Crabbody((char*)"Models/Cangrejo/CrabBody.obj");
	Model CrabHandDer((char*)"Models/Cangrejo/CrabHandDer.obj");
	Model CrabHandIzq((char*)"Models/Cangrejo/CrabHandIzq.obj");

	Model PieD1((char*)"Models/Cangrejo/CrabPie_1_Der.obj");
	Model PieD2((char*)"Models/Cangrejo/CrabPie_2_Der.obj");
	Model PieD3((char*)"Models/Cangrejo/CrabPie_3_Der.obj");
	Model PieD4((char*)"Models/Cangrejo/CrabPie_4_Der.obj");

	Model PieI1((char*)"Models/Cangrejo/CrabPie_1_Izq.obj");
	Model PieI2((char*)"Models/Cangrejo/CrabPie_2_Izq.obj");
	Model PieI3((char*)"Models/Cangrejo/CrabPie_3_Izq.obj");
	Model PieI4((char*)"Models/Cangrejo/CrabPie_4_Izq.obj");

	Model Pez01((char*)"Models/Fishes/Pez01.obj");
	Model Pez02((char*)"Models/Fishes/Pez02.obj");
	Model Pez03((char*)"Models/Fishes/Pez03.obj");
	Model Pez04((char*)"Models/Fishes/Pez04.obj");


	//Modelo de animación
	ModelAnim animacionPersonaje("Animacion/Personaje1/Angry.dae");
	animacionPersonaje.initShaders(animShader.Program);

	// Build and compile our shader program

	//Inicialización de KeyFrames
	
	
	KeyFrame[0].posX = -1.1;
	KeyFrame[0].posY = 0.0;
	KeyFrame[0].posZ = -0.50;
	KeyFrame[0].rotDI1 = UpC;
	KeyFrame[0].rotDI2 = UpC;
	KeyFrame[0].rotDI3 = UpC;
	KeyFrame[0].rotDI4 = .04;
	KeyFrame[0].rotHands = Pinzas;
	//A number: 1
	KeyFrame[1].posX = -3.10;
	KeyFrame[1].posY = 0.0;
	KeyFrame[1].posZ = 0.30;
	KeyFrame[1].rotDI1 = DownC;
	KeyFrame[1].rotDI2 = DownC;
	KeyFrame[1].rotDI3 = DownC;
	KeyFrame[1].rotDI4 = -.007;
	KeyFrame[1].rotHands = -Pinzas;
	//A number: 2
	KeyFrame[2].posX = -7.4;
	KeyFrame[2].posY = 0.0;
	KeyFrame[2].posZ = 4.5;
	KeyFrame[2].rotDI1 = UpC;
	KeyFrame[2].rotDI2 = UpC;
	KeyFrame[2].rotDI3 = UpC;
	KeyFrame[2].rotDI4 = 0.04;
	KeyFrame[2].rotHands = Pinzas;
	//A number: 3
	KeyFrame[3].posX = -8.5;
	KeyFrame[3].posY = 0.0;
	KeyFrame[3].posZ = 11.90;
	KeyFrame[3].rotDI1 = DownC;
	KeyFrame[3].rotDI2 = DownC;
	KeyFrame[3].rotDI3 = DownC;
	KeyFrame[3].rotDI4 = -.007;
	KeyFrame[3].rotHands = -Pinzas;
	//A number: 4
	KeyFrame[4].posX = -7.4;
	KeyFrame[4].posY = 0.0;
	KeyFrame[4].posZ = 4.50;
	KeyFrame[4].rotDI1 = UpC;
	KeyFrame[4].rotDI2 = UpC;
	KeyFrame[4].rotDI3 = UpC;
	KeyFrame[4].rotDI4 = 0.04;
	KeyFrame[4].rotHands = -Pinzas;
	//A number: 5
	KeyFrame[5].posX = -3.1;
	KeyFrame[5].posY = 0.0;
	KeyFrame[5].posZ = 0.3;
	KeyFrame[5].rotDI1 = DownC;
	KeyFrame[5].rotDI2 = DownC;
	KeyFrame[5].rotDI3 = DownC;
	KeyFrame[5].rotDI4 = -0.007;
	KeyFrame[5].rotHands = Pinzas;
	//A number: 6
	KeyFrame[6].posX = -1.1;
	KeyFrame[6].posY = -0.5;
	KeyFrame[6].posZ = 0.5;
	KeyFrame[6].rotDI1 = UpC;
	KeyFrame[6].rotDI2 = UpC;
	KeyFrame[6].rotDI3 = UpC;
	KeyFrame[6].rotDI4 = .03;
	KeyFrame[6].rotHands = -Pinzas;
	//A number: 7
	KeyFrame[7].posX = -1.1;
	KeyFrame[7].posY = -1.0;
	KeyFrame[7].posZ = 0.5;
	KeyFrame[7].rotDI1 = DownC;
	KeyFrame[7].rotDI2 = DownC;
	KeyFrame[7].rotDI3 = DownC;
	KeyFrame[7].rotDI4 = 0.007;
	KeyFrame[7].rotHands = 0.0;
	KeyFrame[7].rotHands = -Pinzas;
	//A number: 8
	KeyFrame[8].posX = -1.1;
	KeyFrame[8].posY = 0.0;
	KeyFrame[8].posZ = 0.3;
	KeyFrame[8].rotDI1 = UpC;
	KeyFrame[8].rotDI2 = UpC;
	KeyFrame[8].rotDI3 = UpC;
	KeyFrame[8].rotDI4 = .03;
	KeyFrame[8].rotHands = Pinzas;



	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  
		1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures

	

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.7f, 0.7f, 0.7f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.7f, 0.7f, 0.7f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		glm::vec3 lightColor{};
		lightColor.x = abs(sin(glfwGetTime() * LightP1.x));
		lightColor.y = abs(sin(glfwGetTime() * LightP1.y));
		lightColor.z = sin(glfwGetTime() * LightP1.z);

		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"),lightColor.x, lightColor.y, lightColor.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		lightColor.x = abs(sin(glfwGetTime() * LightP2.x));
		lightColor.y = abs(sin(glfwGetTime() * LightP2.y));
		lightColor.z = sin(glfwGetTime() * LightP2.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 1.8f);

		// Point light 3
		lightColor.x =  LightP3.x;
		lightColor.y =  LightP3.y;
		lightColor.z =  LightP3.z;
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 1.08f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		glm::mat4 model(1);


		//Carga de modelo 
		view = camera.GetViewMatrix();
		

		//------------------------------------------------------------------------------------------------
		//Cangrejo
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.137f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(sin(Radio * rotDI1) + cos(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Crabbody.Draw(lightingShader);


		//Pies Derecho y izquierdo 1
		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI1, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio*rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieD1.Draw(lightingShader);

		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI1, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieI1.Draw(lightingShader);

		//Pies Derecho y izquierdo 2
		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI2, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieD2.Draw(lightingShader);

		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI2, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI2), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieI2.Draw(lightingShader);

		//Pies Derecho y izquierdo 3
		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI3, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI3), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieD3.Draw(lightingShader);

		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI3, posZ));
		model = glm::rotate(model, glm::radians(sin(Radio * rotDI1)+ cos(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI3), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieI3.Draw(lightingShader);

		//Pies Derecho y izquierdo 4
		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI4, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI4), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieD4.Draw(lightingShader);

		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI4, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI4), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieI4.Draw(lightingShader);


		//pinzas
		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotHands), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CrabHandDer.Draw(lightingShader);

		
		model = glm::translate(tmp, glm::vec3(-1.515f, 0.0f, -9.087f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotHands), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CrabHandIzq.Draw(lightingShader);

		//------------------------------------------------------------------------------------------------

		
		model = glm::mat4(1);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		
		model = glm::mat4(1);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arena.Draw(lightingShader);

		 
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		DomoM.Draw(lightingShader);

		 
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		Puerta.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Pecera.Draw(lightingShader);
	//	
	//	//1
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(-6.5f, 0.0f, 0.3f));
	//	model = glm::rotate(model, glm::radians(-88.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Brain.Draw(lightingShader);
	//	view = camera.GetViewMatrix();

	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(-9.1f, 0.1f, 0.0f));
	//	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);


	////	2
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(-1.139f, 0.0f, 6.57f));
	//	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));
	//
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Brain.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(-0.115f, 0.0f, 8.0f));
	//	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);

	////	3
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(10.5f, 0.0f, 0.3f));
	//	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));

	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Brain.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(11.1f, 0.1f, 0.0f));
	//	model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));

	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);
	//	
	//	//4
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(5.164f, 0.0f, -10.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));

	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Brain.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(5.285f, 0.2f, -8.272f));
	//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(3.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);
	//	model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
	//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));;
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);
	//	model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
	//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	CHoja.Draw(lightingShader);

	//	//
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(4.763f, 0.0f, -8.209));
	//	model = glm::rotate(model, glm::radians(4.832f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Pared.Draw(lightingShader);



	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(8.173f, 0.3f, -1.292f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Roca.Draw(lightingShader);


	//	//Puffer
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(r*sin(Radio * movKitX), 0, r*cos(Radio * movKitZ)));
	//	model = glm::rotate(model, glm::radians(-rotKit), glm::vec3(0.0f, 1.0f, 0.0));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Puffer.Draw(lightingShader);
	//	
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
	//	//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	PufferD.Draw(lightingShader);
	//	

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
	//	//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	PufferI.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
	//	//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	PufferC.Draw(lightingShader);
	//	
	//	//peces
	//	//-----------------------------------------------------------------------
	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(tmp, glm::vec3(-0.256f, 3.323f, -0.016f));
	//	
	//	model = glm::scale(model, glm::vec3(3.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(0, movY/2, 0));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
	//	glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	Pez01.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(tmp, glm::vec3(0.0f, 3.323f, -1.094f));
	//	model = glm::rotate(model, glm::radians(11.922f), glm::vec3(0.0f, 1.0f, 0.0));
	//	model = glm::scale(model, glm::vec3(3.0f));
	//	model = glm::translate(model, PosIni + glm::vec3(0, movY*-1, 0));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
	//	glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	Pez02.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(tmp, glm::vec3(-1.572f, 3.323f, -1.094f));
	//	model = glm::rotate(model, glm::radians(181.046f), glm::vec3(0.0f, 1.0f, 0.0));
	//	model = glm::translate(model, PosIni + glm::vec3(0, movY, 0));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
	//	glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	Pez03.Draw(lightingShader);

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	model = glm::translate(tmp, glm::vec3(0.0f, 3.323f, 1.094f));
	//	model = glm::rotate(model, glm::radians(-85.209f), glm::vec3(0.0f, 1.0f, 0.0));
	//	
	//	model = glm::translate(model, PosIni + glm::vec3(0, movY*-1, 0));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "activTransparencia"), 1.0);
	//	glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	Pez04.Draw(lightingShader);
	//	//----------------------------------------------------------------------------------------------------------------

	//	view = camera.GetViewMatrix();
	//	model = glm::mat4(1);
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
	//	Volcan.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.934f));
		model = glm::scale(model, glm::vec3(3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		Cofre.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f,-0.012f, 2.934f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(rotTapa), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		CofreT.Draw(lightingShader);
	
		//Traslucidez

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		DomoC.Draw(lightingShader);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(0);

		//Traslucidez

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		PeceraC.Draw(lightingShader);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		DomoI.Draw(lightingShader);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(Abrir), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		PuertaC.Draw(lightingShader);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		/*_______________________________Personaje Animado___________________________*/
		animShader.Use();
		modelLoc = glGetUniformLocation(animShader.Program, "model");
		viewLoc = glGetUniformLocation(animShader.Program, "view");
		projLoc = glGetUniformLocation(animShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(animShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(animShader.Program, "material.shininess"), 32.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.direction"), 0.0f, -1.0f, -1.0f);
		view = camera.GetViewMatrix();

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(PosIni.x + 0.0f, PosIni.y + 0.0f, PosIni.z - 3.119f));
		model = glm::scale(model, glm::vec3(0.02f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		animacionPersonaje.Draw(animShader);
		glBindVertexArray(0);


		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

	/*
		lampShader.Use();
		//vamos a enviar el valor de tiempo al shader
		tiempo = glfwGetTime() * speed;


		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		//Aqui se envia el valor del tiempo
		glUniform1f(glGetUniformLocation(lampShader.Program, "time"), tiempo);
		//glUniform1f(glGetUniformLocation(Anim.Program, "time"), glfwGetTime() );

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		Water.Draw(lampShader);

		glBindVertexArray(0);
	*/

		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}
//ecuacion x^2+y^2=r^2

void animacion()
{
	int turnangle = 360 / 35;
	rotKit = -10.0;

	//Movimiento del personaje
	if (circuito)
	{
		if (circuito) {
			if (recorrido1)
			{
				rotKit = rotKit - turnangle;
				movKitX += 0.2;
				movKitZ += 0.2;
				Aletas += 1.0;
				if (movKitZ > 165)
				{
					recorrido1 = false;
					recorrido2 = true;
				}

			}

			if (recorrido2)
			{
				rotKit = rotKit - turnangle;
				movKitX -= 0.2;
				movKitZ -= 0.2;
				if (movKitZ < -179)
				{
					recorrido1 = true;
					recorrido2 = false;
				}

			}
			//up down peces
			if (recorrido3)
			{
				movY += 0.0001f;
				if (movY > 0.1) {
					recorrido3 = false;
					recorrido4 = true;
				}

			}

			if (recorrido4)
			{
				movY -= 0.00001f;
				if (movY < 0.0) {
					recorrido4 = false;
					recorrido3 = true;
				}

			}

			//cofre



		}

	}

	if (myanim)
	{
		LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
		LightP2 = glm::vec3(1.0f, 0.15f, 0.0f);
		LightP3 = glm::vec3(0.93f, 1.0f, 0.0f);
	}
	else
	{
		LightP1 = glm::vec3(0);
		LightP2 = glm::vec3(0);
		LightP3 = glm::vec3(0);
	}

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			rotC += 1;
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			//acumulacio de las transformacio/incrementos
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotDI1 += KeyFrame[playIndex].rotInc;
			rotDI2 += KeyFrame[playIndex].rotInc2;
			rotDI3 += KeyFrame[playIndex].rotInc3;
			rotDI4 += KeyFrame[playIndex].rotInc5;

			rotHands += KeyFrame[playIndex].rotInc4;

			i_curr_steps++;
		}

	}

	
		if (recorrido5) {
			rotTapa -= 1.0f;
			printf("tapa %.2f\n", rotTapa);
			if (rotTapa >= -21.0) {
				recorrido5 = false;
			}
		}
	
	if (recorrido6) {
		rotTapa += 1.0f;
		printf("tapa cerrar %.2f\n", rotTapa);
		if (rotTapa <= 0.0) {
			recorrido6 = false;
		}
	}

}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{
			printf("inicia anim\n");
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}



	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	if (keys[GLFW_KEY_I])
	{
		circuito = true;
	}
	
	if (keys[GLFW_KEY_O])
	{
		circuito = false;
	}
	if (keys[GLFW_KEY_C]) {
		recorrido5 = true;
		recorrido6 = false;
	}
	if (keys[GLFW_KEY_V]) {
		recorrido6 = true;
		recorrido5 = false;
	}

}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	if (keys[GLFW_KEY_Z])
	{
		
		movCamera = 0.01f;//Manda una velocidad de 0.01 a la camara automatica

	}

	if (keys[GLFW_KEY_0])
	{
		rot += 1;
	}

	if (keys[GLFW_KEY_1])
	{
		
		if (Abrir <= 90.0) {Abrir += 1;}
	}

	if (keys[GLFW_KEY_2])
	{
		if (Abrir >= 0.0) {
			Abrir -= 1;
		}
	}

	

	

	/*if (keys[GLFW_KEY_C])
	{
		if (rotTapa < 0.0f)
			rotTapa += 1.0f;

	}

	if (keys[GLFW_KEY_V])
	{
		if (rotTapa > -35.284)
			rotTapa -= 1.0f;

	}*/
	
	//up down peces
	if (keys[GLFW_KEY_8])
	{
		if (movY < 0.2)
			movY += 0.01f;

	}

	if (keys[GLFW_KEY_9])
	{
		if (movY > 0.1)
			movY -= 0.01f;

	}

	//Mov Personaje
	if (keys[GLFW_KEY_H])
	{
		posZ += 0.1f;
		
	}
	
	if (keys[GLFW_KEY_Y])
	{
		posZ -= 0.1f;
		
	}

	if (keys[GLFW_KEY_G])
	{
		posX -= 0.1f;
	}

	if (keys[GLFW_KEY_J])
	{
		posX += 0.1f;
	}


	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}