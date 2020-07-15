#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>

class Shader {
 public:
  Shader(const std::string vertexShader, const std::string fragmentShader);
  bool isInitialised();
  void activate();
  ~Shader();

 private:
  bool createShader(GLuint& handler, const GLchar** source, GLenum shaderType);
  bool createProgram();
  bool success_;
  GLuint vertexHandler_;
  GLuint fragmentHandler_;
  GLuint program_;
};

#endif