#include "ObjectMesh.h"

//#include "stb_image.h"
//#include "tiny_obj_loader.h"
//#include "structs.h"



std::string ObjectMesh::GetBaseDir(const std::string& filepath)
{
	if (filepath.find_last_of("/\\") != std::string::npos)
		return filepath.substr(0, filepath.find_last_of("/\\"));
	return "";
}

bool ObjectMesh::FileExists(const std::string& absFilename)
{
	struct stat buffer;
	return (stat(absFilename.c_str(), &buffer) == 0);

}

void ObjectMesh::LoadTextureData(ObjData* objData, GLuint* texture, GLuint* texture2, int num)
{
	int width, height;
	//std::string baseDir = objData->baseDir;

	//for (size_t m = 0; m < objData->materials.size(); m++) {
	//	tinyobj::material_t* mp = &objData->materials[m];
	//	if (mp->diffuse_texname.length() > 0) {
	//		std::cout << baseDir << "\n";
	//		if (objData->textures.find(mp->diffuse_texname) == objData->textures.end()) {
	//			GLuint textureId;
	//			int comp;

	//			//std::string textureFileName = baseDir + "/" + mp->diffuse_texname + ".tga";
	//			std::string texname = mp->diffuse_texname;
	//			std::string textureFileName = baseDir + "/" + texname;
	//			if (!FileExists(textureFileName)) {
	//				std::cerr << "Unable to find file:" << textureFileName << std::endl;
	//				exit(1);
	//			}
	//			unsigned char* image = stbi_load(textureFileName.c_str(),
	//				&width,
	//				&height,
	//				&comp,
	//				STBI_default
	//			);
	//			if (!image) {
	//				std::cerr << "Unable to load texture: " << textureFileName << std::endl;
	//				exit(1);

	//			}
	//			//std::cerr << "Loaded texture: " << textureFileName << std::endl;
	//			//std::cout << image;

	//			//glGenTextures(1, &textureId);
	//			//glActiveTexture(GL_TEXTURE0);
	//			if (m == 0)
	//				glBindTexture(GL_TEXTURE_2D, texture[num]);
	//			else
	//				glBindTexture(GL_TEXTURE_2D, texture2[num]);


	//			GLenum format = GL_RGBA;

	//			if (comp == 3) {
	//				format = GL_RGB;
	//			}
	//			else if (comp == 4) {
	//				format = GL_RGBA;
	//			}
	//			glTexImage2D(
	//				GL_TEXTURE_2D,
	//				0,
	//				format,
	//				width,
	//				height,
	//				0,
	//				format,
	//				GL_UNSIGNED_BYTE,
	//				image
	//			);
	//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//			stbi_image_free(image);

	//			objData->textures.insert(std::make_pair(texname, textureId));

	//		}

	//	}
	//}
}
