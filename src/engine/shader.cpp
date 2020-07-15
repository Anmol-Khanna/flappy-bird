#include "shader.h"

Shader::Shader(const std::string vertexShader, const std::string fragmentShader)
    : success_{false} {
  const GLchar* vertexShaders[] = {vertexShader.c_str()};
  if (!createShader(vertexHandler_, vertexShaders, GL_VERTEX_SHADER)) {
    return;
  }
  const GLchar* fragmentShaders[] = {fragmentShader.c_str()};
  if (!createShader(fragmentHandler_, fragmentShaders, GL_FRAGMENT_SHADER)) {
    return;
  }
  success_ = createProgram();
}
bool Shader::isInitialised() { return success_; }
void Shader::activate() { glUseProgram(program_); }
Shader::~Shader() {
  glDeleteShader(vertexHandler_);
  glDeleteShader(fragmentHandler_);
}
bool Shader::createShader(GLuint& handler, const GLchar** source,
                          GLenum shaderType) {
  char infoLog[1024];
  handler = glCreateShader(shaderType);
  glShaderSource(handler, 1, source, NULL);
  glCompileShader(handler);
  GLint success;
  glGetShaderiv(handler, GL_COMPILE_STATUS, &success);
  if (!success_) {
    glGetShaderInfoLog(handler, 1024, NULL, infoLog);
    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "
              << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
              << "\n"
              << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
  }
  return success_;
}
bool Shader::createProgram() {
  char infoLog[1024];
  program_ = glCreateProgram();
  if (!program_) {
    std::cout << "ERROR::CREATING_PROGRAM" << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
    return success_;
  }
  glAttachShader(program_, vertexHandler_);
  glAttachShader(program_, fragmentHandler_);
  glLinkProgram(program_);
  GLint success;
  glGetProgramiv(program_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_, 1024, NULL, infoLog);
    std::cout << "ERROR::LINKING_PROGRAM" << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
    return success_;
  }
  glValidateProgram(program_);
  glGetProgramiv(program_, GL_VALIDATE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_, 1024, NULL, infoLog);
    std::cout << "ERROR::VALIDATING_PROGRAM" << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
    return success_;
  }
  return success_ = true;
}