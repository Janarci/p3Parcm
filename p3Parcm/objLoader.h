#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "threading/IWorkerAction.h"


struct ObjData;
using namespace std;


class IExecutionEvent;
class objLoader : public IWorkerAction
{
public:

	objLoader(GLuint modelTransformLoc, IExecutionEvent* executionEvent);
	void run();

	GLuint texture[8];
	GLuint multiTexture[8];
	GLuint modelTransformLoc;

	glm::mat4 transSword;



	std::string GetBaseDir_(const std::string& filepath);
	bool FileExists_(const std::string& absFilename);
	void LoadTextureData_(ObjData* objData, GLuint* texture, GLuint* texture2, int num);
	void LoadObjFile_(ObjData* objData, std::string filename);
	void LoadObjToMemory_(ObjData* objData, GLfloat scaleFactor, GLfloat tOffset[], GLuint* texture, GLuint* texture2, int num);

	bool finishLoad = false;
private:
	
	void render();
	void processEvents();
	void update();

public:
	void onStartTask() override;
	IExecutionEvent* execEvent;

};
