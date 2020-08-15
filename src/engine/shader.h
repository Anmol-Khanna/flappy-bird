#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
 public:
  Shader(const std::string vertexShader, const std::string fragmentShader);
  bool isInitialised();
  void activate();
  void deactivate();
  void loadUniform(const std::string name, glm::mat4 mat);
  void loadUniform(const std::string name, int val);
  bool validate();
  ~Shader();

 private:
  bool createShader(GLuint& handler, const GLchar** source, GLenum shaderType);
  bool createProgram();
  bool success_;
  GLuint vertexHandler_;
  GLuint fragmentHandler_;
  GLuint program_;
  GLint getLocation(const std::string name);
  std::unordered_map<std::string, GLint> locations_;
};

#endif