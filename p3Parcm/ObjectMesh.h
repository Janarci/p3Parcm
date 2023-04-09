#pragma once

#include <iostream>
#include <GL/glew.h>


struct ObjData;

class ObjectMesh
{

	std::string GetBaseDir(const std::string& filepath);
	bool FileExists(const std::string& absFilename);
	void LoadTextureData(ObjData* objData, GLuint* texture, GLuint* texture2, int num);

	void LoadObjFile(ObjData* objData, std::string filename);

	void LoadObjToMemory2(ObjData* objData, GLfloat scaleFactor, GLfloat tOffset[]);

	void LoadObjToMemory(ObjData* objData, GLfloat scaleFactor, GLfloat tOffset[], GLuint* texture, GLuint* texture2, int num);


};

