#include "texture.h"

Texture::Texture() {};

void Texture::attachTexture(unsigned int width, unsigned int height,
                            unsigned int channels, unsigned char* data) {
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, (channels == 3 ? GL_RGB : GL_RGBA), width,
                 height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}

void Texture::activate(unsigned int slot=0) {
  glActiveTexture(GL_TEXTURE0+slot);
  glBindTexture(GL_TEXTURE_2D, texture_);
}