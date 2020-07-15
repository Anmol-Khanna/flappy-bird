#include "mesh.h"

Mesh::Mesh() { glGenVertexArrays(1, &vao_); }

void Mesh::activate() { glBindVertexArray(vao_); }
void Mesh::draw() { glDrawArrays(GL_TRIANGLES, 0, size_); }
void Mesh::draw(GLuint start, GLuint count) {
  glDrawArrays(GL_TRIANGLES, start, count);
}

Mesh::~Mesh() {
  glDeleteBuffers(vbos_.size(), vbos_.data());
  glDeleteVertexArrays(1, &vao_);
}