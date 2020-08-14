#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <tiny_obj_loader.h>
#include <functional>
#include <algorithm>
#include "mesh.h"
#include "texture.h"

std::string getShaderCode(const std::string name);
struct vec3 {
  float v[3];
  vec3() {
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
  }
};

bool FileExists(const std::string& abs_filename);
std::string GetBaseDir(const std::string& filepath);
void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]);
bool LoadObjAndConvert(
    float bmin[3], float bmax[3], const char* filename,
    std::function<void(std::vector<float>)> onPositions,
    std::function<void(std::vector<float>)> onNormals,
    std::function<void(std::vector<float>)> onColours,
    std::function<void(std::vector<float>, std::string)> onTextureCoordinates,
    std::function<void(int, int, int, unsigned char*, std::string)> onTexture);
#endif