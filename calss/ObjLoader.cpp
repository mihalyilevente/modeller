//
// Created by levi on 2023.07.18..
//

#include <iostream>
#include "ObjLoader.h"

void ObjLoader::loadObj(const std::string &path, std::vector<glm::vec3> &out_vertices, std::vector<glm::ivec3> &out_faces) {
    std::ifstream in(path, std::ios::in);
    if (!in) {
        throw std::runtime_error("Cannot open " + path);
    }

    std::string line;
    while (std::getline(in, line)) {
        // Ignore comments and empty lines
        if (line.substr(0, 1) == "#" || line.empty()) {
            continue;
        }
        else if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            out_vertices.push_back(v);
        }
        else if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            glm::ivec3 f;
            s >> f.x;
            s >> f.y;
            s >> f.z;
            out_faces.push_back(f);
        }
        else {
            std::cerr << "Line started with " << line.substr(0, 2) << " which we didn't parse\n";
        }
    }
}

