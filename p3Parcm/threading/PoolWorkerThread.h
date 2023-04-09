#pragma once
#include "IETThread.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


struct ObjData;
class IWorkerAction;
class IFinishedTask;
/// <summary>
/// A pool worker thread that executes an action
/// </summary>
class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, GLuint modelTransformLoc);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);
	void run() override;
	void draw() ;

	std::string GetBaseDir_(const std::string& filepath);
	bool FileExists_(const std::string& absFilename);
	void LoadTextureData_(ObjData* objData, GLuint* texture, GLuint* texture2, int num);
	void LoadObjFile_(ObjData* objData, std::string filename);
	void LoadObjToMemory_(ObjData* objData, GLfloat scaleFactor, GLfloat tOffset[], GLuint* texture, GLuint* texture2, int num);

	GLuint texture[8];
	GLuint multiTexture[8];
	GLuint modelTransformLoc;
	glm::mat4 transSword;



private:

	int id = 0;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
};