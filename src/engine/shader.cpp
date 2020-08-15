#include "shader.h"

Shader::Shader(const std::string vertexShader, const std::string fragmentShader)
    : success_{false}, locations_{{}} {
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
void Shader::deactivate() { glUseProgram(0); }
GLint Shader::getLocation(const std::string name) {
  if (locations_.find(name) == locations_.end()) {
    auto location = glGetUniformLocation(program_, name.c_str());
    locations_.insert({name, location});
  }
  return locations_[name];
}
void Shader::loadUniform(const std::string name, glm::mat4 mat) {
  glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::loadUniform(const std::string name, int val) {
  glUniform1i(getLocation(name), val);
}
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
  if (!success) {
    GLsizei length;
    glGetShaderInfoLog(handler, 1024, &length, infoLog);
    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "
              << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
              << "\n"
              << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
    return false;
  }
  return true;
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
    return success_ = false;
  }
  return success_ = true;
}

bool Shader::validate() {
  char infoLog[1024];
  GLint success;
  glValidateProgram(program_);
  glGetProgramiv(program_, GL_VALIDATE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_, 1024, NULL, infoLog);
    std::cout << "ERROR::VALIDATING_PROGRAM" << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
    return success_ = false;
  }
  return success_ = true;
}