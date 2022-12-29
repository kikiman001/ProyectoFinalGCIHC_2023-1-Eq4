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
float rotKit = 90.0;
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


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightPos2(18.0f, 0.0f, -10.0f);
glm::vec3 lightPos3(0.0f, 0.0f, 7.0f);
glm::vec3 lightPos4(7.0f, 0.0f, 7.0f);
glm::vec3 PosIni(0.0f, 0.0f, 0.0f);
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

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Iluminacion 2", nullptr, nullptr);

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	//acuario
	Model Piso((char*)"Models/Sea/Sea.obj");
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
	Model Garden((char*)"Models/House/garden.obj");
	Model Lamp((char*)"Models/House/lamp.obj");
	Model Front((char*)"Models/House/front.obj");
	Model Roof((char*)"Models/House/roof.obj");

	Model Foco((char*)"Models/Foco/Foco.obj");
	

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

		glm::mat4 model(1);

		//TORTUGA---------------------------------------------
		// Also draw the lamp object, again binding the appropriate shader
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
		//Piso.Draw(lampShader);
		glBindVertexArray(0);

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
			Light1 = glm::vec3(1.0f, 0.2f,1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
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
}