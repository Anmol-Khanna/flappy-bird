#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
 public:
  Texture();
  void attachTexture(unsigned int width, unsigned int height,
                     unsigned int channels, unsigned char* data);
  void activate(unsigned int slot);

 private:
  GLuint texture_;
};

#endif