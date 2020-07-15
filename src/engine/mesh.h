#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

class Mesh {
 public:
  Mesh();
  template <typename T>
  void attachVertexBuffer(std::vector<T> points, GLuint index, GLint size) {
    glBindVertexArray(vao_);
    GLuint vbo;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    vbos_.push_back(vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * points.size(), &points.front(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
    size_ = size;
  }
  void activate();
  void draw();
  void draw(GLuint start, GLuint count);
  ~Mesh();

 private:
  GLint size_;
  GLuint vao_;
  std::vector<GLuint> vbos_;
};

#endif