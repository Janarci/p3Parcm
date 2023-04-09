#ifndef STRUCTS_H
#define STRUCTS_H
#include "tiny_obj_loader.h"

 struct VertexData {
    glm::vec3 position;
    glm::vec2 UV;
    glm::vec3 normal;
};

 struct ObjData {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    GLulong numFaces;
    GLuint vaoId;
    std::string baseDir;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
};


#endif // STRUCTS_H