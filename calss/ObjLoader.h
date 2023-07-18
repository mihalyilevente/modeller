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
    void loadObj(const std::string &path, std::vector<glm::vec3> &out_vertices, std::vector<glm::ivec3> &out_faces);
};


#endif //OBJLOADER_H
