#include "testThread.h"
//
//#include "..\Obj_mesh.h"

std::string GetBaseDirs(const std::string& filepath) {
	if (filepath.find_last_of("/\\") != std::string::npos)
		return filepath.substr(0, filepath.find_last_of("/\\"));
	return "";
}

testThread::testThread(GLuint texture[8], GLuint multiTexture[8], GLfloat objOffset[], ObjData& objModel,
	std::string filepath, int index)
{
	//std::string warn;
	//std::string err;

	//std::string basepath = "Assets/";

	//std::string inputfile = basepath + filepath;

	//std::string baseDir = GetBaseDir(inputfile);
	//objModel->baseDir = baseDir;
	///*
	//bool isSuccess = tinyobj::LoadObj(&objData->attrib,
	//	&objData->shapes,
	//	NULL,
	//	&warn,
	//	&err,
	//	inputfile.c_str()
	//);*/
	//bool isSuccess = tinyobj::LoadObj(&objModel->attrib,
	//	&objModel->shapes,
	//	&objModel->materials,
	//	&warn,
	//	&err,
	//	inputfile.c_str(),
	//	baseDir.c_str()
	//);

	//if (!err.empty()) {
	//	std::cerr << err << std::endl;

	//}

	//std::cout << "loaded " << filepath << std::endl;

}

void testThread::run()
{
}
