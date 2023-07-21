//
// Created by levi on 2023.07.18..
//

#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <fstream>
#include <sstream>
#include <vector>
#include "../external/GLM/glm.hpp"

class ObjLoader {
public:

    void parseVec3(const std::string &line, std::vector<glm::vec3> &out_vector);

    void parseVec2(const std::string &line, std::vector<glm::vec2> &out_vector);

    void
    parseFace(const std::string &line, std::vector<glm::ivec3> &out_faces, std::vector<glm::ivec3> &out_normIndices,
              std::vector<glm::ivec3> &out_texIndices);

    void loadObj(const std::string &path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_texCoords,
                 std::vector<glm::vec3> &out_normals, std::vector<glm::ivec3> &out_faces,
                 std::vector<glm::ivec3> &out_texIndices, std::vector<glm::ivec3> &out_normIndices);
};


#endif //OBJLOADER_H
