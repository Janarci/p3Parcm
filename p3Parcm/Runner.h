#pragma once
#include <vector>

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define TINYOBJLOADER_IMPLEMENTATION


#include "tiny_obj_loader.h"

#include <iostream>
#include <chrono>
#include "Obj_mesh.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "skybox.h"

using namespace std;

class Runner
{
public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	Runner();
	void run();

	typedef std::chrono::high_resolution_clock Clock;

	static bool firstmouse = true;
	static GLfloat lastX = 0;
	static GLfloat lastY = 0;
	static GLfloat yaw = -90.0f;
	static GLfloat pitch = 0.0f;
	static glm::vec3 camFront;
	static glm::vec3 camSide;
	static glm::vec3 camUp;

	GLFWwindow* window;

	GLuint texture[8];
	GLuint multiTexture[8];
	GLfloat ObjOffset[] = { 0.0f, -0.5f, 0.0f };


	ObjData GaneshaObjData;
	ObjData SwordObjData;
	ObjData PedestalObjData;
	ObjData FloorObjData;
	ObjData EarthObjData;
	ObjData MoonObjData;
	ObjData SunObjData;
	ObjData SkullObjData;

	glm::mat4 projection;
	GLuint projectionLoc;
	GLuint cameraPosLoc;
	GLuint normalTransLoc;
	GLuint viewLoc;
	GLuint modelTransformLoc;

	SkyboxData skybox;
	GLuint skyboxShaderProgram;
	GLuint shaderProgram;
	GLuint colorLoc;
	GLuint multiTex;

	glm::mat4 transEarth, transMoon, transSun, transGanesha, transSword, transSkull, transPedestal, transFloor;



	glm::vec3 Up;
	glm::vec3 viewDirections;
	glm::vec3 position;
	float max_far = 2000.0f;
	float walkspeed = 0.5f;


private:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void load3dModel(GLuint texture[8], GLuint multiTexture[8], GLfloat objOffset[], ObjData& objModel, std::string filepath, int index);
	void render();
	void processEvents();
	void update();
};



