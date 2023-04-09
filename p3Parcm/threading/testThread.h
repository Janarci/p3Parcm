#pragma once
#include "IETThread.h"
#include <GL/glew.h>

struct ObjData;

class testThread : IETThread
{
public:
	testThread(GLuint texture[8], GLuint multiTexture[8], GLfloat objOffset[], ObjData& objModel, std::string filepath, int index);
	~testThread();
	void start();
	bool IsRunning() { return isRunning; };
protected:
	void run() override;
	bool isRunning = true;
	int size = 0;
	int startNumber = 0;
	int endNumber = 0;
};

