#include "fractal.h"
#include "utils.h"

Fractal::Fractal(const int width, const int height)
    : width_{width}, height_{height} {
  auto const id = Renderable::create();
  Renderable::attach(id,
                     {-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f},
                     0, 2);
  const std::string vertexCode = getShaderCode("C:/Users/anony/Desktop/flappy/flappy-bird/src/fractal/fractal.vs"); //@TODO: make this relative
  const std::string fragmentCode = getShaderCode("C:/Users/anony/Desktop/flappy/flappy-bird/src/fractal/fractal.fs"); //@TODO: make this relative
  Renderable::attach(
      std::make_shared<Shader>(Shader(vertexCode, fragmentCode)));
}

void Fractal::render(glm::mat4 transform) {
  Renderable::activate();
  Renderable::set("itr", 200);
  Renderable::set("width", width_);
  Renderable::set("height", height_);
  Renderable::set("viewProjection", transform);
  Renderable::render({});
  Renderable::deactivate();
}