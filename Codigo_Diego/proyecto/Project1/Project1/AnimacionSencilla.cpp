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
Camera  camera(glm::vec3(50.0f, 25.0f, 0.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

bool active;

//traslacion de modelos
float EX = 55.583;
float EZ = 45.746;

float karla = 0.0;

//variables de animacion sencilla
float tiempo = 1.0f;
float speed = 1.0f;
float rot = 0;
bool anim = true;
float rot2 = 0;
bool anim2 = true;
float jelly_M = 0;
bool anim3 = true;

//variables de animacion compleja
float movKitX = 0.0;
float movKitZ = 0.0;
float rad = 12.0;

float movKitXt = 0.0;
float movKitZt = 0.0;
float rotKitt = 180.0;
float radt = 60.0;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = true;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;
//cangrejo keyframes

float range = 0.0f;
float rotC = -45.0f;
float UpC = 0.019;
float DownC = -0.023;
float Pinzas = 12;
float movCamera = 0.0f;


bool myanim = true;

//Recorrido pez globo
bool circuitoe = false;
bool recorridoe1 = true;
bool recorridoe2 = false;
bool recorridoe3 = true;
bool recorridoe4 = false;
bool recorridoe5 = false;
bool recorridoe6 = false;

bool recorridoe7 = false;
bool recorridoe8 = false;


float rotKit = 90.0;
float rotTapa = 0.0f;
float Abrir = 0.0f;
const float r = 9.0f;
const float Radio = (3.14159f) / 180.0f;

//Peces up and down
float movYe = 0.0;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightPos2(18.0f, 0.0f, -10.0f);
glm::vec3 lightPos3(0.0f, 0.0f, 7.0f);
glm::vec3 lightPos4(7.0f, 0.0f, 7.0f);
glm::vec3 PosIni(0.0f, 0.0f, 0.0f);



// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotDI1 = 0, rotDI2 = 0, rotDI3 = 0, rotDI4 = 0, rotHands = 0;
float Aletas = 0.0f;
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
	glm::vec3(20.0f,0.0f, 0.0f),
	glm::vec3(8.0f,0.0f, -29.0f),
	glm::vec3(10.0f,0.0f, 20.0f),
	glm::vec3(7.0f,0.0f, 7.0f)
};

glm::vec3 spotLightPosition[] = {
	glm::vec3(16.0f, 12.0f, -30.0f),
	glm::vec3(0.0f, 12.0f, -30.0f),
	glm::vec3(19.0f, 12.0f, 29.0f)
};
glm::vec3 spotLightDirection(0.0f, -30.0f, 0.0f);
glm::vec3 spotLightDirection2(-10.0f, -30.0f, 0.0f);

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


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

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Teoria", nullptr, nullptr);

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


	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp2.vs", "Shaders/lamp2.frag");
	Shader Anim("Shaders/anim.vs", "Shaders/anim.frag");
	Shader Anim2("Shaders/anim2.vs", "Shaders/anim.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");

	//acuario
	//Model Sea((char*)"Models/Sea/Sea.obj");
	Model CubeL((char*)"Models/Sea/Sea.obj");
	Model CubeR((char*)"Models/Sea/Sea.obj");
	Model CubeFr((char*)"Models/Sea/Sea.obj");
	Model CubeT((char*)"Models/Sea/Sea.obj");
	Model CubeB((char*)"Models/Sea/Sea.obj");
	Model CubeF((char*)"Models/Sea/SeaFloor.obj");
	//fish
	Model FishF((char*)"Models/Fish/bassFront.obj");
	Model FishT((char*)"Models/Fish/bassTail.obj");
	Model Fish((char*)"Models/Fish/bass.obj");
	//tortuga
	Model body((char*)"Models/Turtle/body.obj");
	Model front_left((char*)"Models/Turtle/front_left.obj");
	Model front_right((char*)"Models/Turtle/front_right.obj");
	Model rear_left((char*)"Models/Turtle/rear_left.obj");
	Model rear_right((char*)"Models/Turtle/rear_right.obj");
	//jelly
	Model Jelly((char*)"Models/Jelly/Jelly.obj");
	Model Jelly2((char*)"Models/Jelly/Jelly.obj");
	Model Jelly3((char*)"Models/Jelly/Jelly.obj");
	//Algae
	Model Algae((char*)"Models/Algae/Algae.obj");
	Model Algae1((char*)"Models/Algae/Algae.obj");

	Model Algae2((char*)"Models/Algae/Algae2.obj");
	Model Algae22((char*)"Models/Algae/Algae2.obj");

	Model Algae3((char*)"Models/Algae/Algae3.obj");
	Model Algae32((char*)"Models/Algae/Algae3.obj");
	//house
	Model House((char*)"Models/House/only_house.obj");
	//Model Shark((char*)"Models/House/shark.obj");
	Model Garden((char*)"Models/House/garden.obj");
	Model Lamp((char*)"Models/House/lamp.obj");
	Model Front((char*)"Models/House/front.obj");
	Model Roof((char*)"Models/House/roof.obj");

	Model Foco((char*)"Models/Foco/Foco.obj");
	

	Model DomoC((char*)"Models/Fachada_E/DomoCristal.obj");
	Model DomoM((char*)"Models/Fachada_E/DomoMetal.obj");
	Model DomoI((char*)"Models/Fachada_E/DomoIntCristal.obj");
	Model Puerta((char*)"Models/Fachada_E/Puerta.obj");
	Model PuertaC((char*)"Models/Fachada_E/PuertaCristal.obj");
	//Model Water((char*)"Models/Water/Water.obj");

	Model Arena((char*)"Models/Fachada_E/PisoArena.obj");

	Model PeceraC((char*)"Models/Pecera/PeceraCristal.obj");
	Model Pecera((char*)"Models/Pecera/Pecera.obj");


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


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

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
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		//Load Model
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.1f,0.1f,0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.7f, 0.7f, 0.7f);

		// Point light 1

		glm::vec3 lightColor;
		glm::vec3 lightColor2;
		glm::vec3 lightColor3;
		glm::vec3 lightColor4;

		lightColor.x = abs(sin(glfwGetTime() * Light1.x ));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);

		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = sin(glfwGetTime() * Light2.z );

		lightColor3.x = abs(sin(glfwGetTime() * Light3.x / 4));
		lightColor3.y = abs(sin(glfwGetTime() * Light3.y / 4));
		lightColor3.z = sin(glfwGetTime() * Light3.z / 4);

		lightColor4.x = abs(sin(glfwGetTime() * Light4.x / 4));
		lightColor4.y = abs(sin(glfwGetTime() * Light4.y / 4));
		lightColor4.z = sin(glfwGetTime() * Light4.z / 4);

		

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.5f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.02f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.0004f);



		// Point light 2

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.5f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.02f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0004f);

		// Point light 3


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.5f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.02f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0004f);

		// Point light 4


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.5f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.02f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0004f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].position"), spotLightPosition[0].x, spotLightPosition[0].y, spotLightPosition[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].direction"), spotLightDirection.x, spotLightDirection.y, spotLightDirection.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].linear"), 0.11f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].quadratic"), 0.0123f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].outerCutOff"), glm::cos(glm::radians(15.0f)));

		// SpotLight2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].position"), spotLightPosition[1].x, spotLightPosition[1].y, spotLightPosition[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].direction"), spotLightDirection.x, spotLightDirection.y, spotLightDirection.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].linear"), 0.11f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].quadratic"), 0.0123f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//spot3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].position"), spotLightPosition[2].x, spotLightPosition[2].y, spotLightPosition[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].direction"), spotLightDirection2.x, spotLightDirection2.y, spotLightDirection2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].linear"), 0.11f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].quadratic"), 0.0123f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

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

		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		glm::mat4 model(1);

		//TORTUGA---------------------------------------------
		 //Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
	    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		//animacion compleja
		model = glm::translate(model, PosIni + glm::vec3(0, movKitZt, movKitXt));
		model = glm::rotate(model, glm::radians(rotKitt), glm::vec3(0.0f, 1.0f, 0.0));
		//------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, glfwGetTime()));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		front_right.Draw(lampShader);

		model = glm::mat4(1);
		//animacion compleja
		model = glm::translate(model, PosIni + glm::vec3(0, movKitZt, movKitXt));
		model = glm::rotate(model, glm::radians(rotKitt), glm::vec3(0.0f, 1.0f, 0.0));
		//------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, glfwGetTime()));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		front_left.Draw(lampShader);

		model = glm::mat4(1);
		//animacion compleja
		model = glm::translate(model, PosIni + glm::vec3(0, movKitZt, movKitXt));
		model = glm::rotate(model, glm::radians(rotKitt), glm::vec3(0.0f, 1.0f, 0.0));
		//------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, glfwGetTime()));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		rear_left.Draw(lampShader);

		model = glm::mat4(1);
		//animacion compleja
		model = glm::translate(model, PosIni + glm::vec3(0, movKitZt, movKitXt));
		model = glm::rotate(model, glm::radians(rotKitt), glm::vec3(0.0f, 1.0f, 0.0));
		//------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, glfwGetTime()));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		rear_right.Draw(lampShader);

		model = glm::mat4(1);
		//animacion compleja
		model = glm::translate(model, PosIni + glm::vec3(0, movKitZt, movKitXt));
		model = glm::rotate(model, glm::radians(rotKitt), glm::vec3(0.0f, 1.0f, 0.0));
		//------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		body.Draw(lampShader);

	

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//SV.Draw(lampShader);
		//Sea.Draw(lampShader);
		glBindVertexArray(0);

		////	//Cangrejo
		lampShader.Use();

		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.137f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(sin(Radio * rotDI1) + cos(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Crabbody.Draw(lampShader);


		//Pies Derecho y izquierdo 1
			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI1, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio*rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieD1.Draw(lampShader);

			
		model = glm::translate(tmp, glm::vec3(-1.515f+EZ, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI1, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieI1.Draw(lampShader);
		
		//Pies Derecho y izquierdo 2
			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI2, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieD2.Draw(lampShader);

			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI2, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI2), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieI2.Draw(lampShader);

			//Pies Derecho y izquierdo 3
			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI3, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI3), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieD3.Draw(lampShader);

			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI3, posZ));
		model = glm::rotate(model, glm::radians(sin(Radio * rotDI1)+ cos(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI3), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieI3.Draw(lampShader);

			//Pies Derecho y izquierdo 4
			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY + rotDI4, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI4), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieD4.Draw(lampShader);

			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY - rotDI4, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotDI4), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		PieI4.Draw(lampShader);


		//pinzas
			
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotHands), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		CrabHandDer.Draw(lampShader);
					
		model = glm::translate(tmp, glm::vec3(-1.515f+EX, 0.0f, -9.087f+EZ));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(r * sin(Radio * rotDI1)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotHands), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		CrabHandIzq.Draw(lampShader);
		glBindVertexArray(0);

		//------------------------------------------------------------------------------------------------


		//HOUSE
		lightingShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -2.4, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activeTransparencia"), 0.0f);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		//glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//House.Draw(lampShader);
		House.Draw(lightingShader);
		glBindVertexArray(0);

		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -2.4, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Garden.Draw(lampShader);
		glBindVertexArray(0);

		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -2.4, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Roof.Draw(lampShader);
		glBindVertexArray(0);
		 
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -2.4, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Front.Draw(lampShader);
		glBindVertexArray(0);


		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(spotLightPosition[0]));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Lamp.Draw(lampShader);
		glBindVertexArray(0);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(spotLightPosition[1]));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Lamp.Draw(lampShader);
		glBindVertexArray(0);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(spotLightPosition[2]));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Lamp.Draw(lampShader);
		glBindVertexArray(0);


		//JELLY--------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, jelly_M /2, 5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Jelly.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, jelly_M, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Jelly2.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, jelly_M+4, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Jelly3.Draw(lampShader);
		glBindVertexArray(0);


		//fish
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.0f, 2.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		//animacion compleja
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		//---------------------
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Fish.Draw(lampShader);
		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.0f, 2.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		//animacion compleja
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		//---------------------
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Fish.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, 3.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishF.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, 3.0f, 5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishT.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 4.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishF.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 4.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishT.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.0f, 5.0f, 3.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishF.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.0f, 5.0f, 3.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		FishT.Draw(lampShader);
		glBindVertexArray(0);

		//-----------------------------------------------------------------------------------------------------
		//MODELOS ENRIQUE
		//-----------------------------------------------------------------------------------------------------
		/*lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + EX, -2.4f, 0.0f + EZ));
		model = glm::scale(model, glm::vec3(0.3f, 8.0f, 0.3f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lampShader);
		glBindVertexArray(0);*/
		
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(EX, 0.0f, EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//glUniform1f(glGetUniformLocation(lampShader.Program, "activTransparencia"), 0.0);
		//glUniform4f(glGetUniformLocation(lampShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Arena.Draw(lampShader);
		glBindVertexArray(0);

		// 
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(EX, 0.0f, EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		DomoM.Draw(lampShader);
		glBindVertexArray(0);
		

		lampShader.Use();//	
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(EX, 0.0f, EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Pecera.Draw(lampShader);
		glBindVertexArray(0);
		
		/*lampShader.Use();
		//	//1
	
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(-6.5f+EX, 0.0f, 0.3f+EZ));
		//	model = glm::rotate(model, glm::radians(-88.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	Brain.Draw(lampShader);
		//glBindVertexArray(0);
	
		//lampShader.Use();
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(-9.1f+EX, 0.1f, 0.0f+EZ));
		//	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);

		//lampShader.Use();
		////	2

		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(-1.139f+EX, 0.0f, 6.57f+EZ));
		//	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));

		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	Brain.Draw(lampShader);
		//glBindVertexArray(0);
		//lampShader.Use();
	
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(-0.115f+EX, 0.0f, 8.0f+EZ));
		//	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);
		//lampShader.Use();
		////	3
	
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(11.5f+EX, 0.0f, 0.3f+EZ));
		//	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	Brain.Draw(lampShader);
		//glBindVertexArray(0);

		//lampShader.Use();
	
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(11.1f+EX, 0.1f, 0.0f+EZ));
		//	model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);

		//lampShader.Use();
		//	//4
	
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(5.164f+EX, 0.0f, -10.0f+EZ));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	Brain.Draw(lampShader);
		//glBindVertexArray(0);

		//lampShader.Use();
		//	model = glm::mat4(1);
		//	model = glm::translate(model, glm::vec3(5.285f+EX, 0.2f, -8.272f+EZ));
		//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	model = glm::scale(model, glm::vec3(3.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);
		//	model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
		//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));;
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);
		//	model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
		//	//model = glm::rotate(model, glm::radians(-65.656f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		//	CHoja.Draw(lampShader);
		//glBindVertexArray(0);
			//
		*/

		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.763f+EX, 0.0f, -8.209+EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(4.832f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		Pared.Draw(lampShader);
		glBindVertexArray(0);

		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.173f+EX, 0.3f, -1.292f+EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		Roca.Draw(lampShader);
		glBindVertexArray(0);

			//Puffer
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f+EX, 0.0f, 0.0f+EZ));
		model = glm::translate(model, PosIni + glm::vec3(r*sin(Radio * movKitX), 0, r*cos(Radio * movKitZ)));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(-rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		Puffer.Draw(lampShader);
	
	
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + EX, 0.0f, 0.0f + EZ));
		model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		PufferD.Draw(lampShader);
	

	
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + EX, 0.0f, 0.0f + EZ));
		model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		PufferI.Draw(lampShader);

	
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + EX, 0.0f, 0.0f + EZ));
		model = glm::translate(model, PosIni + glm::vec3(r * sin(Radio * movKitX), 0, r * cos(Radio * movKitZ)));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, glm::radians(Aletas), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		PufferC.Draw(lampShader);
		glBindVertexArray(0);
		//peces
		//-----------------------------------------------------------------------
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-0.256f+EX, 5.323f, -0.016f+EZ));
	
		model = glm::scale(model, glm::vec3(4.5f));
		model = glm::translate(model, PosIni + glm::vec3(0, movYe/2, 0));
		glUniform1f(glGetUniformLocation(lampShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lampShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pez01.Draw(lampShader);
		glBindVertexArray(0);

		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.0f+EX, 5.323f, -1.094f+EZ));
		model = glm::rotate(model, glm::radians(11.922f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(4.5f));
		model = glm::translate(model, PosIni + glm::vec3(0, movYe*-1, 0));
		glUniform1f(glGetUniformLocation(lampShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lampShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pez02.Draw(lampShader);
		glBindVertexArray(0);
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-1.0f+EX, 5.323f, 0.0f+EZ));
		model = glm::rotate(model, glm::radians(181.046f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, PosIni + glm::vec3(0, movYe, 0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniform1f(glGetUniformLocation(lampShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lampShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pez03.Draw(lampShader);
		model = glm::scale(model, glm::vec3(-3.0f));
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.0f+EX, 5.323f, 1.094f+EZ));
		model = glm::rotate(model, glm::radians(-85.209f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, PosIni + glm::vec3(0, movYe*-1, 0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniform1f(glGetUniformLocation(lampShader.Program, "activTransparencia"), 1.0);
		glUniform4f(glGetUniformLocation(lampShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pez04.Draw(lampShader);
		glBindVertexArray(0);
//----------------------------------------------------------------------------------------------------------------
	//Pecera central
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + EX, 0.0f, 0.0f + EZ));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		Volcan.Draw(lampShader);
		glBindVertexArray(0);
		//cofre
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f+EX, 0.0f, 2.934f+EZ));
		model = glm::scale(model, glm::vec3(4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		Cofre.Draw(lampShader);
		glBindVertexArray(0);
		lampShader.Use();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f+EX,-0.012f, 2.934f+EZ));
		model = glm::scale(model, glm::vec3(4.5f));
		model = glm::rotate(model, glm::radians(rotTapa), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lampShader.Program, "transparencia"), 0.0);
		CofreT.Draw(lampShader);
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
		

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(PosIni.x +EX, PosIni.y + 0.0f, PosIni.z - 3.119f+EZ));
		//model = glm::scale(model, glm::vec3(0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		animacionPersonaje.Draw(animShader);
		glBindVertexArray(0);



		// ALGAES
		Anim.Use();
		
		//PECERA--------------------------------------------
	
		glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		tiempo = glfwGetTime() * speed;
		modelLoc = glGetUniformLocation(Anim.Program, "model");
		viewLoc = glGetUniformLocation(Anim.Program, "view");
		projLoc = glGetUniformLocation(Anim.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Suelo de la pecera con animacion pero sin transparencia
		model = glm::mat4(1);
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniform4f(glGetUniformLocation(Anim.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CubeF.Draw(Anim);

		//Algas con animacion

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -3.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae.Draw(Anim);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -4.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae22.Draw(Anim);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 3.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae2.Draw(Anim);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 3.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae1.Draw(Anim);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 3.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae3.Draw(Anim);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 3.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Algae32.Draw(Anim);

		//Partes de la pecera con animacion  y transparencia

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(-15.0f, 15.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniform4f(glGetUniformLocation(Anim.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.55f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CubeFr.Draw(Anim);

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(15.0f, 15.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CubeB.Draw(Anim);


		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 15.0f, -15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1f(glGetUniformLocation(Anim.Program,"time"),tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CubeL.Draw(Anim);

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CubeR.Draw(Anim);

		glDisable(GL_BLEND);

		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();

		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		for (GLuint i = 0; i < 3; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, spotLightPosition[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		


		
		glBindVertexArray(0);
		

		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

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


	//animaciones sencillas para las medusas, las aletas de la tortuga  y los peces
	if (anim)
	{
		if (rot < 20.0f)
			rot += 0.2;
		else if (rot >= 20.0f)
			anim = false;
	}
	else {
		if (rot > -20.0f)
			rot -= 0.2;
		else if (rot <= -20.0f)
			anim = true;
	}
	if (anim2)
	{

		if (rot2 > -20.0f)
			rot2 -= 0.2;
		else if (rot2 <= -20.0f)
			anim2 = false;
	}
	else {
		if (rot2 < 20.0f)
			rot2 += 0.2;
		else if (rot2 >= 20.0f)
			anim2 = true;
	}
	if (anim3)
	{

		if (jelly_M > -6.0f)
			jelly_M -= 0.05;
		else if (jelly_M <= -6.0f)
			anim3 = false;
	}
	else {
		if (jelly_M < 6.0f)
			jelly_M += 0.05;
		else if (jelly_M >= 6.0f)
			anim3 = true;
	}
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
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

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 0.5f, 1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
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

		if (keys[GLFW_KEY_I])
		{
			circuito = true;
		}

		if (keys[GLFW_KEY_O])
		{
			circuito = false;
		}
		
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

void animacion()
{
	int turnangle = 360 / 35;
	rotKit = -10.0;

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


	//Movimiento del pez
	//Formula de elipse se ocupa en esta seccion
	if (true)
	{
		if (recorrido1)
		{
			rotKit += 0.3;
			movKitX += 0.1f;
			if (movKitX <= rad) {
				movKitX += 0.01f;
			}
			else {
				recorrido1 = false;
				recorrido3 = true;
			}
			movKitZ = sqrt(pow(rad, 2) - pow(movKitX, 2));
		
		}
		if (recorrido2)
		{
			rotKit += 0.3;
			movKitX -= 0.1f;
			if (movKitX > -rad) {
				movKitX -= 0.01f;
			}
			else {
				recorrido2 = false;
				recorrido1 = true;
			}
			movKitZ = sqrt(pow(rad, 2) - pow(movKitX, 2));

			
		}

		if (recorrido3)
		{
			rotKit += 0.3;
			movKitX -= 0.1f;
			if (movKitX > -rad) {
				movKitX -= 0.01f;
			}
			else {
				recorrido3 = false;
				recorrido4 = true;
			}
			movKitZ = -sqrt(pow(rad, 2) - pow(movKitX, 2));
		}

		if (recorrido4)
		{
			rotKit += 0.3;
			movKitX -= 0.1f;
			if (movKitX > -rad) {
				movKitX -= 0.01f;
			}
			else {
				recorrido4 = false;
				recorrido2 = true;
			}
			movKitZ = -sqrt(pow(rad, 2) - pow(movKitX, 2));
		}

		//recorrido de tortuga con parabola
		if (recorrido5)
		{
			movKitXt += 0.001;
			
			//rotKitt += 180.0;
			if (movKitXt <= 3.14) {
				movKitXt += 0.01f;
			}
			else {
				recorrido5 = false;
				recorrido6 = true;
			}
			movKitZt = 5*sin(movKitXt);


			
		}
		if (recorrido6)
		{
			
			rotKitt += 0.3;
			if (rotKitt <= 180) {
				rotKitt += 0.01f;
			}
			else {
				recorrido6 = false;
				recorrido7 = true;
			}
		}
		if (recorrido7)
		{
			movKitXt -= 0.001;
			
			//rotKitt += 180.0;
			if (movKitXt > 0) {
				movKitXt -= 0.01f;
			}
			else {
				recorrido7 = false;
				recorrido8 = true;
			}
			movKitZt = 5*sin(movKitXt);
		}
		if (recorrido8)
		{
			
			rotKitt -= 0.3;
			if (rotKitt > 0) {
				rotKitt -= 0.01f;
			}
			else {
				recorrido8 = false;
				recorrido5 = true;
			}
		}

	}


	//Movimiento del personaje
	if (circuito)
	{
		if (circuito) {
			if (recorridoe1)
			{
				rotKit = (-1 * rotKit) - turnangle;
				movKitX += 0.2;
				movKitZ += 0.2;
				Aletas += 1.0;
				if (movKitZ > 165)
				{
					recorridoe1 = false;
					recorridoe2 = true;
				}

			}

			if (recorridoe2)
			{
				rotKit = (rotKit)-turnangle;
				movKitX -= 0.2;
				movKitZ -= 0.2;
				if (movKitZ < -179)
				{
					recorridoe1 = true;
					recorridoe2 = false;
				}

			}
			//up down peces
			if (recorridoe3)
			{
				movYe += 0.0001f;
				if (movYe > 0.1) {
					recorridoe3 = false;
					recorridoe4 = true;
				}

			}

			if (recorrido4)
			{
				movYe -= 0.00001f;
				if (movYe < 0.0) {
					recorridoe4 = false;
					recorridoe3 = true;
				}

			}

		}

	}
}