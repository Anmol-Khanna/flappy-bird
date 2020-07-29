#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <glad/glad.h>

class Mesh {
 public:
  Mesh();
  void attachVertexBuffer(std::vector<float> points, GLuint index, GLint size);
  void attachMaterialId(std::string material) {
    material_ = material;
  }
  std::string getMaterialId() { return material_; }
  void activate();
  void draw();
  void draw(GLuint start, GLuint count);
  ~Mesh();

 private:
  GLint size_;
  GLuint vao_;
  std::string material_;
  std::vector<GLuint> vbos_;
};

#endif