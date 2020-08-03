#ifndef PLAYER_H
#define PLAYER_H

#include "mesh.h"
#include "shader.h"
#include "movable.h"
#include "renderable.h"

class Player : public Renderable, public Movable {
 public:
  Player(Shader shader, Mesh mesh);

 private:
  Shader shader_;
  Mesh mesh_;
};

#endif