#ifndef FRACTAL_H
#define FRACTAL_H

#include "renderable.h"
#include "movable.h"

#ifdef USE_SIMD
class Fractal {};
#elif USE_CUDA
class Fractal {};
#elif USE_GL_COMPUTE_SHADER
class Fractal {};
#else
class Fractal : public Renderable, public Movable {
 public:
  Fractal(const int width, const int height);
  void render(glm::mat4 transform);

 private:
  int width_;
  int height_;
};
#endif
#endif