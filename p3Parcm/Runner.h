#pragma once
#include <iostream>
#include <vector>



#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "threading/IExecutionEvent.h"
#include "threading/PoolWorkerThread.h"

struct ObjData;
using namespace std;
class Runner: public IExecutionEvent
{
public:

	Runner();
	void run();
	
	GLFWwindow* window;
	GLuint texture[8];
	GLuint multiTexture[8];


	std::string GetBaseDir_(const std::string& filepath);
	bool FileExists_(const std::string& absFilename);
	void LoadTextureData_(ObjData* objData, GLuint* texture, GLuint* texture2, int num);
	void LoadObjFile_(ObjData* objData, std::string filename);
	void LoadObjToMemory_(ObjData* objData, GLfloat scaleFactor, GLfloat tOffset[], GLuint* texture, GLuint* texture2, int num);

private:
	std::vector<PoolWorkerThread*> threads;

	void render();
	void processEvents();
	void update();
	void onFinishedExecution() override;
	

};



