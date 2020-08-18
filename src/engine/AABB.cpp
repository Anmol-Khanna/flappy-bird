#include "AABB.h"

// constructs a unit cube about the origin
AABB::AABB()
    : min_{glm::vec3(-0.5f, -0.5f, -0.5f)},
      max_{glm::vec3(+0.5f, +0.5f, +0.5f)},
      vertices{// front face
               max_[0], min_[1], min_[2], max_[0], min_[1], max_[2], max_[0],max_[1], max_[2], max_[0], max_[1], min_[2],
               // back face
               min_[0], min_[1], min_[2], min_[0], min_[1], max_[2], min_[0],max_[1], max_[2], min_[0], max_[1], min_[2],
               // left face
               min_[0], min_[1], min_[2], max_[0], min_[1], min_[2], max_[0],max_[1], min_[2], min_[0], max_[1], min_[2],
               // right face
               min_[0], min_[1], max_[2], max_[0], min_[1], max_[2], max_[0],max_[1], max_[2], min_[0], max_[1], max_[2],
               // top face
               min_[0], max_[1], min_[2], max_[0], max_[1], min_[2], max_[0],max_[1], max_[2], min_[0], max_[1], max_[2],
               // bottom face
               min_[0], min_[1], min_[2], max_[0], min_[1], min_[2], max_[0],min_[1], max_[2], min_[0], min_[1], max_[2]} 
{
  // create and bind VAO, VBO, pull in shaders, glDrawArrays()
  const char* AABBVertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  const char* AABBFragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n\0";

  unsigned int VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &AABBVertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &AABBFragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  AABBShaderProgram = glCreateProgram();
  glAttachShader(AABBShaderProgram, vertexShader);
  glAttachShader(AABBShaderProgram, fragmentShader);
  glLinkProgram(AABBShaderProgram);
  glGetProgramiv(AABBShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(AABBShaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR:: SHADER PROGRAM COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// constructs an AABB of given scale, about given position
AABB::AABB(glm::vec3 position, glm::mat4 scale) {
  // @TODO(anmol): make this actually do somthing
  min_ = glm::vec3(0.0f, 0.0f, 0.0f);
  max_ = glm::vec3(0.0f, 0.0f, 0.0f);
  float vertices[] = {
      // front face
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      max_[2],
      max_[0],
      max_[1],
      max_[2],
      max_[0],
      max_[1],
      min_[2],
      // back face
      min_[0],
      min_[1],
      min_[2],
      min_[0],
      min_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      min_[2],
      // left face
      min_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      max_[1],
      min_[2],
      min_[0],
      max_[1],
      min_[2],
      // right face
      min_[0],
      min_[1],
      max_[2],
      max_[0],
      min_[1],
      max_[2],
      max_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      // top face
      min_[0],
      max_[1],
      min_[2],
      max_[0],
      max_[1],
      min_[2],
      max_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      // bottom face
      min_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      max_[2],
      min_[0],
      min_[1],
      max_[2],
  };
}

// creates AABB from min and max points
AABB::AABB(glm::vec3 min, glm::vec3 max) {
  // @TODO(anmol): check that min is always < max, if not, swap them
  min_ = min;
  max_ = max;
  float vertices[] = {
      // front face
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      max_[2],
      max_[0],
      max_[1],
      max_[2],
      max_[0],
      max_[1],
      min_[2],
      // back face
      min_[0],
      min_[1],
      min_[2],
      min_[0],
      min_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      min_[2],
      // left face
      min_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      max_[1],
      min_[2],
      min_[0],
      max_[1],
      min_[2],
      // right face
      min_[0],
      min_[1],
      max_[2],
      max_[0],
      min_[1],
      max_[2],
      max_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      // top face
      min_[0],
      max_[1],
      min_[2],
      max_[0],
      max_[1],
      min_[2],
      max_[0],
      max_[1],
      max_[2],
      min_[0],
      max_[1],
      max_[2],
      // bottom face
      min_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      min_[2],
      max_[0],
      min_[1],
      max_[2],
      min_[0],
      min_[1],
      max_[2],
  };

}

// sets position to the position of the linked Object
void AABB::update() {
  // @TODO(anmol): update
  return;
}

// draws the AABB
//void AABB::render(glm::mat4 transform) {
void AABB::render() {
  glUseProgram(AABBShaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 24);
  glBindVertexArray(0);
  /*
  auto const id = Renderable::create();
  Renderable::attach(id,vertices,0, 1); // vertices[] will always have 72 verts in it, 4 verts per face 72/4 Renderable::attach(std::make_shared<Shader>(Shader(AABBvertexShaderSource, AABBFragmentShaderSource)));
  Renderable::activate();
  Renderable::set("viewProjection", transform);
  Renderable::render({});
  Renderable::deactivate();*/
}
