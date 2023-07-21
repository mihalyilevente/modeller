#include <iostream>
#include <vector>
#include <sstream>
#include "ObjLoader.h"

void ObjLoader::loadObj(const std::string& path,
                        std::vector<glm::vec3>& out_vertices,
                        std::vector<glm::vec2>& out_texCoords,
                        std::vector<glm::vec3>& out_normals,
                        std::vector<glm::ivec3>& out_faces,
                        std::vector<glm::ivec3>& out_texIndices,
                        std::vector<glm::ivec3>& out_normIndices) {
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
            parseVec3(line.substr(2), out_vertices);
        }
        else if (line.substr(0, 3) == "vt ") {
            parseVec2(line.substr(3), out_texCoords);
        }
        else if (line.substr(0, 3) == "vn ") {
            parseVec3(line.substr(3), out_normals);
        }
        else if (line.substr(0, 2) == "f ") {
            parseFace(line.substr(2), out_faces, out_normIndices, out_texIndices);
        }
        else {
            continue;
            //std::cerr << line << "Line started with " << line.substr(0, 2) << " which we didn't parse\n";
        }
    }
}

void ObjLoader::parseVec2(const std::string& line, std::vector<glm::vec2>& out_vector) {
    std::istringstream s(line);
    glm::vec2 v;
    s >> v.x;
    s >> v.y;
    out_vector.push_back(v);
}

void ObjLoader::parseVec3(const std::string& line, std::vector<glm::vec3>& out_vector) {
    std::istringstream s(line);
    glm::vec3 v;
    s >> v.x;
    s >> v.y;
    s >> v.z;
    out_vector.push_back(v);
}

void ObjLoader::parseFace(const std::string& line,
                          std::vector<glm::ivec3>& out_faces,
                          std::vector<glm::ivec3>& out_normIndices,
                          std::vector<glm::ivec3>& out_texIndices)
{
    std::istringstream s(line);
    std::string token;
    glm::ivec3 f(-1, -1, -1);
    glm::ivec3 fn(-1, -1, -1);
    glm::ivec3 ft(-1, -1, -1);
    std::string vtnSets[3];

    for (int i = 0; i < 3; ++i) {
        std::getline(s, vtnSets[i], ' ');

        std::vector<std::string> indexStrings;
        std::istringstream indexStream(vtnSets[i]);
        std::string index;

        while (std::getline(indexStream, index, '/')) {
            indexStrings.push_back(index);
        }

        if (!indexStrings[0].empty()) {
            f[i] = std::stoi(indexStrings[0]) - 1;
        }
        if (indexStrings.size() > 1 && !indexStrings[1].empty()) {
            ft[i] = std::stoi(indexStrings[1]) - 1;
        }
        if (indexStrings.size() > 2 && !indexStrings[2].empty()) {
            fn[i] = std::stoi(indexStrings[2]) - 1;
        }
    }

    out_faces.push_back(f);
    out_texIndices.push_back(ft);
    out_normIndices.push_back(fn);
}
