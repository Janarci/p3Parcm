#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "glm/glm.hpp"
#include <iostream>
#include <chrono>
#include "Obj_mesh.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "skybox.h"

//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//
//int main()
//{
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* window;
//	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glViewport(0, 0, 800, 600);
//
//
//    //initialize glew
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        fprintf(stderr, "Failed to initialize GLEW\n");
//        return -1;
//    }
//
//
//    // set bg color to green
//    glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
//    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//        //input
//        processInput(window);
//
//        //render
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //swap buffer
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//
//    return 0;
//}




typedef std::chrono::high_resolution_clock Clock;

bool firstmouse = true;
GLfloat lastX = 0;
GLfloat lastY = 0;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
glm::vec3 camFront;
glm::vec3 camSide;
glm::vec3 camUp;
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (firstmouse) {
		lastX = xpos;
		lastY = ypos;
		firstmouse = false;
	}

	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.4f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(front);



}

int main() {

#pragma region initialize


	//initialize glfw  
	if (glfwInit() != GLFW_TRUE) {
		fprintf(stderr, "Failed to initialized! \n");
		return -1;
	}

	// set opengl version to 3.3  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window   
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Khalil Jan Arcilla", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to load window! \n");
		return -1;
	}

	glfwMakeContextCurrent(window);

	//initialize glew  
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
#pragma endregion
	GLuint texture[8];
	GLuint multiTexture[8];
	glGenTextures(8, texture);
	glGenTextures(8, multiTexture);
#pragma region object
	GLfloat bunnyOffset[] = { 0.0f, -0.5f, 0.0f };

	Objtest GaneshaObjData;
	LoadObjFile(&GaneshaObjData, "Ganesha/Ganesha.obj");

	LoadObjToMemory(&GaneshaObjData, 5.0f, bunnyOffset, texture, multiTexture, 3);
	//LoadTextureData(&GaneshaObjData, "Ganesha1.png", texture, 3);

	//std::cout << GaneshaObjData.baseDir<<"\n";

	Objtest SkullObjData;
	LoadObjFile(&SkullObjData, "Skull/Skull.obj");
	LoadObjToMemory(&SkullObjData, 5.0f, bunnyOffset, texture, multiTexture, 4);
	//LoadTextureData(&SkullObjData, "skull_diffuse.jpg", texture, 4);

	Objtest SwordObjData;
	LoadObjFile(&SwordObjData, "Sword/moonlight.obj");
	LoadObjToMemory(&SwordObjData, 5.0f, bunnyOffset, texture, multiTexture, 5);
	//LoadTextureData(&SwordObjData, "Tex_0014_0.png", texture, 5);

	Objtest PedestalObjData;
	LoadObjFile(&PedestalObjData, "pedestal/10421_square_pedastal_iterations-2.obj");
	LoadObjToMemory(&PedestalObjData, 5.0f, bunnyOffset, texture, multiTexture, 6);
	//LoadTextureData(&PedestalObjData, "10421_square_pedastal_diffuse.jpg", texture, 6);

	Objtest FloorObjData;
	LoadObjFile(&FloorObjData, "Floor/CobbleStones2.obj");
	LoadObjToMemory(&FloorObjData, 5.0f, bunnyOffset, texture, multiTexture, 7);
	//LoadTextureData(&FloorObjData, "BrickRound0108_5_S.jpg", texture, 7);

	Objtest EarthObjData;
	LoadObjFile(&EarthObjData, "earth/Earth.obj");
	LoadObjToMemory(&EarthObjData, 5.0f, bunnyOffset, texture, multiTexture, 0);
	//LoadTextureData(&EarthObjData, "Earth.tga", texture, 0);

	Objtest MoonObjData;
	LoadObjFile(&MoonObjData, "earth/Earth.obj");
	LoadObjToMemory(&MoonObjData, 5.0f, bunnyOffset, texture, multiTexture, 1);
	//LoadTextureData(&MoonObjData, "Moon.tga", texture, 1);

	Objtest SunObjData;
	LoadObjFile(&SunObjData, "earth/Earth.obj");
	LoadObjToMemory(&SunObjData, 5.0f, bunnyOffset, texture, multiTexture, 2);
	//LoadTextureData(&SunObjData, "Sun.tga", texture, 2);


	/*
		//VAO
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		//VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

		GLuint colorVBO;
		glGenBuffers(1, &colorVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);


		//second array
		GLuint VAO2, VBO2, colorVBO2;
		glGenVertexArrays(1, &VAO2);
		glBindVertexArray(VAO2);

		glGenBuffers(1, &VBO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferDataFeatures), vertexBufferDataFeatures, GL_STATIC_DRAW);

		glGenBuffers(1, &colorVBO2);
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferDataFeatures), colorBufferDataFeatures, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		*/

#pragma endregion

#pragma region skybox
	std::vector<std::string> faces{
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"

	};
	SkyboxData skybox = loadSkyBox("Assets/Skybox", faces);
#pragma endregion


#pragma region shader
	//skybox shader
	GLuint skyboxShaderProgram = loadShaders("Shaders/skybox_vertex.shader", "Shaders/skybox_fragment.shader");

	//GLuint shaderProgram = loadShaders("Shaders/vertex.shader", "Shaders/fragment.shader");
	//GLuint shaderProgram = loadShaders("Shaders/goraud_vertex.shader", "Shaders/goraud_fragment.shader");
	//GLuint shaderProgram = loadShaders("Shaders/test_vertex.shader", "Shaders/test_fragment.shader");
	GLuint shaderProgram = loadShaders("Shaders/phong_vertex.shader", "Shaders/phong_fragment.shader");
	glUseProgram(shaderProgram);
	GLfloat red = 1.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "u_color");
	glUniform3f(colorLoc, 0.3f, 0.3f, 0.3f);

	GLuint modelTransformLoc = glGetUniformLocation(shaderProgram, "u_model");
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "u_view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "u_projection");

	//normal transformations
	GLuint normalTransLoc = glGetUniformLocation(shaderProgram, "u_normal");
	GLuint cameraPosLoc = glGetUniformLocation(shaderProgram, "u_camera_pos");
	GLuint ambientColorLoc = glGetUniformLocation(shaderProgram, "u_ambient_color");
	glUniform3f(ambientColorLoc, 0.8f, 0.8f, 0.8f);

	//light shading
	GLuint lightLoc = glGetUniformLocation(shaderProgram, "u_light_pos");
	GLuint diffuseLoc = glGetUniformLocation(shaderProgram, "texture_diffuse");
	GLuint diffuse2Loc = glGetUniformLocation(shaderProgram, "texture2_diffuse");
	glUniform3f(lightLoc, 3.0f, 3.0f, 2.0f);

	//set textures
	glUniform1i(diffuseLoc, 0);
	glUniform1i(diffuse2Loc, 1);

	//bool check
	//GLuint isSun = glGetUniformLocation(shaderProgram, "sun");
	GLuint multiTex = glGetUniformLocation(shaderProgram, "multi");

	//transformation matrix
	glm::mat4 trans = glm::mat4(1.0f); // identity
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));//change this for x y z positions
	//trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));// rotation by degrees on glm::radians
	trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));//scale
	//glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//define projection matrix
	glm::mat4 projection = glm::mat4(1.0f);// = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, -1.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 transEarth, transMoon, transSun, transGanesha, transSword, transSkull, transPedestal, transFloor;

	transMoon =
		transSun =
		transGanesha =
		transSword =
		transPedestal =
		transFloor =
		transSkull = glm::mat4(1.0f);

	transSun = glm::scale(transSun, glm::vec3(1.0f, 1.0f, 1.0f));
	transSun = glm::translate(transSun, glm::vec3(30.0f, 0.0f, -40.0f));

	transPedestal = glm::translate(transPedestal, glm::vec3(50.0f, 0.0f, -40.0f));

	transFloor = glm::translate(transFloor, glm::vec3(0.0f, 0.0f, -15.0f));

	transGanesha = glm::translate(transGanesha, glm::vec3(30.0f, 0.0f, -40.0f));
	transGanesha = glm::translate(transGanesha, glm::vec3(120.0f, 0.0f, 0.0f));
	transGanesha = glm::scale(transGanesha, glm::vec3(2.0f, 2.0f, 2.0f));//scale

	transGanesha = glm::rotate(transGanesha, glm::radians(220.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//transGanesha = glm::translate(transGanesha, glm::vec3(10.0f, 0.0f, 0.0f));

	transSword = glm::translate(transSword, glm::vec3(30.0f, 0.0f, -40.0f));
	transSword = glm::translate(transSword, glm::vec3(200.0f, 15.0f, 0.0f));
	transSword = glm::scale(transSword, glm::vec3(0.2f, 0.2f, 0.2f));//scale
	transSword = glm::scale(transSword, glm::vec3(0.5f, 0.5f, 0.5f));//scale
	transSword = glm::rotate(transSword, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//transSkull = glm::translate(transSkull, glm::vec3(40.0f, 0.0f, -20.0f));
	transSkull = glm::translate(transSkull, glm::vec3(50.0f, 0.0f, -40.0f));
	transSkull = glm::scale(transSkull, glm::vec3(4.0f, 4.0f, 4.0f));//scale



	GLfloat x = 0.0f, y = 0.0f, z = 0.0f;
	GLfloat xScale = 0.0f, yScale = 0.0f, zScale = 0.0f;
	GLfloat xRotate = 0.0f, YRotate = 0.0f, ZRotate = 0.0f;
	double prevxpos = 0.0f, prevypos = 0.0f;
	double xpos = 0.0f, ypos = 0.0f;
#pragma endregion


	float vertices[] =
	{
		0.0, 300, 300.0,
		300, 300, 300.0,
		300, 0.0, 300.0,
		0.0, 0.0, 300.0

	};
	GLfloat vertexBufferData[] = {
		-0.9f, -0.6f, 0.5f,
		-0.6f, -0.9f, 0.5f,
		0.0f, 0.0f, 0.5f,  //1
		0.6f, -0.9f, 0.5f,
		0.9f, -0.6f, 0.5f,
		0.9f, 0.6f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.6f, 0.9f, 0.5f,
		-0.6f, 0.9f, 0.5f,
		-0.9f, 0.6f, 0.5f,
		0.0f, 0.0f, 0.5f,
		-0.9f, -0.6f, 0.5f,

	};
	// set bg color to green  
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);

	float max_far = 2000.0f;
	float bunnear = -0.1f;
	float angle = 1.0f;
	float earthAngle = 1.0f;
	float walkspeed = 0.5f;

	glm::vec2 rotation;
	glm::vec2 newMouse;
	glm::vec2 oldMouse;
	glm::quat camera_orientation_;
	glm::mat4 normalTrans;

	glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Up = glm::vec3(0.0f, 0.0f, -1.0f);
	//projection = glm::ortho(-40.0f, 120.0f, -40.0f, 120.0f, 0.1f, max_far);

	position = glm::vec3(30.0f, 20.0f, 40.0f);
	viewDirections = glm::vec3(30.0f, 0.0f, 0.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);

	/*


		glm::vec3 position = glm::vec3(-20.0f, 0.0f, 30.0f);
		glm::vec3 viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		*//*
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		*/
	glEnable(GL_DEPTH_TEST);


	auto t1 = Clock::now();
	while (!glfwWindowShouldClose(window)) {
		glfwSetCursorPosCallback(window, mouse_callback);


		// for2d controlling
		/*
		if (glfwGetKey(window, GLFW_KEY_S)) {
			std::cout << "s click\n";
			glfwGetCursorPos(window, &xpos, &ypos);

			if (xpos == prevxpos) {

			}
			else if (xpos < prevxpos) {
				xScale -= 0.01f;

			}
			else if (xpos > prevxpos) {
				xScale += 0.01f;

			}
			if (ypos == prevypos) {

			}
			else if (ypos < prevypos) {
				yScale += 0.01f;

			}
			else if (ypos > prevypos) {
				yScale -= 0.01f;

			}

			prevxpos = xpos;
			prevypos = ypos;

		}
		else if (glfwGetKey(window, GLFW_KEY_T)) {
			std::cout << "T click\n";

			glfwGetCursorPos(window, &xpos, &ypos);

			if (xpos == prevxpos) {
				std::cout << "wewew";
			}
			else if (xpos < prevxpos) {
				x -= 0.01f;

			}
			else if (xpos > prevxpos) {
				x += 0.01f;

			}
			if (ypos == prevypos) {
				std::cout << "wewew";
			}
			else if (ypos < prevypos) {
				y += 0.01f;

			}
			else if (ypos > prevypos) {
				y -= 0.01f;

			}
			std::cout <<"prev "<< prevxpos << ", " << prevypos << "\n";
			std::cout << xpos << ", " << ypos<<"\n";

			prevxpos = xpos;
			prevypos = ypos;

		}
		else if (glfwGetKey(window, GLFW_KEY_R)) {
			std::cout << "R click\n";
			glfwGetCursorPos(window, &xpos, &ypos);

			if (xpos == prevxpos) {

			}
			else if (xpos < prevxpos) {
				ZRotate -= 1.0f;

			}
			else if (xpos > prevxpos) {
				ZRotate += 1.0f;

			}

			prevxpos = xpos;
			prevypos = ypos;
		}

		trans = glm::rotate(trans, glm::radians(ZRotate), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(1.0f + xScale, 1.0f + yScale, 1.0f));
		trans = glm::translate(trans, glm::vec3(x, y, z));
		*/
		//glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//for FPS
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
			walkspeed = 1.0f;
		}
		else {
			walkspeed = 0.5f;

		}
		if (true) {
			glm::vec3 strafeDir = glm::cross(camFront, Up);
			camUp = glm::cross(strafeDir, camFront);
			strafeDir = glm::cross(camFront, camUp);
			if (glfwGetKey(window, GLFW_KEY_D)) {
				position += walkspeed * strafeDir;
				//std::cout << glm::to_string(position) << std::endl;

			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				position -= walkspeed * strafeDir;
				//std::cout << glm::to_string(position) << std::endl;

			}
			if (glfwGetKey(window, GLFW_KEY_W)) {
				position += walkspeed * camFront;
				//std::cout << glm::to_string(position) << std::endl;

				//viewDirections.z += 0.1f;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				position -= walkspeed * camFront;
				//std::cout << glm::to_string(position) << std::endl;

				//viewDirections.z -= 0.1f;
			}
			if (glfwGetKey(window, GLFW_KEY_E)) {
				position += walkspeed * Up;
				//std::cout << glm::to_string(position) << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_Q)) {
				position -= walkspeed * Up;
				//std::cout << glm::to_string(position) << std::endl;
			}
			if (position.y < 40.0f || position.y > 40.0f) {
				position.y = 40.0f;
			}
		}

		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		/*
		test -= bunnear;
		if (test >= max_far - 1.0f) {
			bunnear *= -1;
		}
		else if (test <= bunnear) {
			bunnear *= -1;
		}
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, bunnear));*/

		if (glfwGetKey(window, GLFW_KEY_R)) {
			position = glm::vec3(30.0f, 20.0f, 40.0f);
			viewDirections = glm::vec3(30.0f, 0.0f, 0.0f);
			Up = glm::vec3(0.0f, 1.0f, 0.0f);
			//projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, max_far);
		}
		if (glfwGetKey(window, GLFW_KEY_T)) {
			position = glm::vec3(0.0f, 1.0f, 0.0f);
			viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
			Up = glm::vec3(0.0f, 0.0f, -1.0f);
			//projection = glm::mat4(1.0f);
			projection = glm::ortho(-40.0f, 120.0f, -40.0f, 120.0f, 0.1f, max_far);
		}
		projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, max_far);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

#pragma region View
		/*glm::mat4 view = glm::lookAt(
			position,
			viewDirections,
			Up
		);
*/
//for fps

		glm::mat4 view = glm::lookAt(
			position,
			position + camFront,
			Up
		);
		glUniform3f(cameraPosLoc, position.x, position.y, position.z);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

#pragma endregion
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#pragma region Draw
		//--- start drawing here ---

		drawSkyBox(skybox, skyboxShaderProgram, view, projection);
		glUseProgram(shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(multiTex, false);


		/*
		auto t2 = Clock::now();
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000000000 > 0.1f) {
			if (red == 1.0f) {
				red = 0.0f;
				green = 1.0f;
			}
			else if (green == 1.0f) {
				green = 0.0f;
				blue = 1.0f;
			}
			else {
				blue = 0.0f;
				red = 1.0f;

			}

			glUniform3f(colorLoc, red, green, blue);
			t1 = Clock::now();
			t2 = Clock::now();
		}

		glUniform3f(colorLoc, red, green, blue);
		glBindVertexArray(bunnyObjData.vaoId);
		*/
		/*
				glUniform1i(isSun, false);
				earthAngle += .08f;
				if (earthAngle >= 360) {
					earthAngle = 1;
				}
				transEarth = transSun;
				transEarth = glm::scale(transEarth, glm::vec3(0.7f, 0.7f, 0.7f));
				transEarth = glm::translate(transEarth, glm::vec3(60.0f, 0.0f, 0.0f));
				transEarth = glm::rotate(transEarth, glm::radians(earthAngle), glm::vec3(0.0f, 1.0f, 0.0f));

				glBindVertexArray(EarthObjData.vaoId);
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transEarth));
				glDrawElements(GL_TRIANGLES, EarthObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

				angle += .5;
				if (angle >= 360) {
					angle = 1;
				}
				transMoon = transEarth;
				transMoon = glm::scale(transMoon, glm::vec3(0.5f, 0.5f, 0.5f));
				transMoon = glm::translate(transMoon, glm::vec3(40.0f, 0.0f, 0.0f));
				transMoon = glm::translate(transMoon, glm::vec3(-40.0f, 0.0f, 0.0f));
				transMoon = glm::rotate(transMoon, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
				transMoon = glm::translate(transMoon, glm::vec3(40.0f, 0.0f, 0.0f));

				glBindVertexArray(MoonObjData.vaoId);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transMoon));
				glDrawElements(GL_TRIANGLES, MoonObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

				glUniform1i(multiTex, false);
				glBindVertexArray(SunObjData.vaoId);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture[2]);

				transSun = glm::rotate(transSun, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
				normalTrans = glm::transpose(glm::inverse(transSun));
				//glUniformMatrix4fv(normalTransLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transSun));
				//glUniform3f(lightLoc, 30.0f, 0.0f, -40.0f);6
				glDrawElements(GL_TRIANGLES, SunObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

				*/
				//glUniform1i(isSun, true);
		glUniform1i(multiTex, false);

		glBindVertexArray(SwordObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transSword));
		glDrawElements(GL_TRIANGLES, SwordObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(GaneshaObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transGanesha));
		glDrawElements(GL_TRIANGLES, GaneshaObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(SkullObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transSkull));
		glDrawElements(GL_TRIANGLES, SkullObjData.numFaces, GL_UNSIGNED_INT, (void*)0);


		glBindVertexArray(PedestalObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, multiTexture[7]);


		for (int i = 0; i < 3; i++) {
			glm::mat4 dupe = transPedestal;
			dupe = glm::translate(dupe, glm::vec3(i * 100.0f, 0.0f, 0.0f));
			dupe = glm::scale(dupe, glm::vec3(0.2f, 0.2f, 0.2f));//scale
			dupe = glm::rotate(dupe, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			if (i == 1)
				glUniform1i(multiTex, false);
			else
				glUniform1i(multiTex, true);
			glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
			glDrawElements(GL_TRIANGLES, PedestalObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
		}


		glUniform1i(multiTex, true);

		glBindVertexArray(FloorObjData.vaoId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, multiTexture[7]);


		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, j * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(-100.0f, 0.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}

		}
		glUniform1i(multiTex, false);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {//ceiling

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, 105.0f, j * 100.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(0.0f, -85.0f, i * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(-48.0f, 48.0f, -2.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(0.0f, -85.0f, i * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(348.0f, 48.0f, -2.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, 0.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, 44.0f, -48.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				if (i != 1) {
					dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, 0.0f));
					dupe = glm::translate(dupe, glm::vec3(0.0f, 44.0f, 350.0f));
					dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
					dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
					dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
					glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
					glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
				}
			}

		}
		//glUniform1i(isSun, true);


			//--- stop drawing here ---
#pragma endregion
		glfwSwapBuffers(window);

		//listen for glfw input events
		glfwPollEvents();
	}

	return 0;
}
