#include "mesh.h"

Mesh::Mesh() { glGenVertexArrays(1, &vao_); }
void Mesh::attachVertexBuffer(std::vector<float> points, GLuint index,
                              GLint size) {
  glBindVertexArray(vao_);
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  vbos_.push_back(vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), &points.front(),
               GL_STATIC_DRAW);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(index);
  size_ = points.size() / size;
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
void Mesh::activate() { glBindVertexArray(vao_); }
void Mesh::draw() { return draw(0, size_); }
void Mesh::draw(GLuint start, GLuint count) {
  glDrawArrays(GL_TRIANGLES, start, count);
}

Mesh::~Mesh() {
  glDeleteBuffers(vbos_.size(), vbos_.data());
  glDeleteVertexArrays(1, &vao_);
}