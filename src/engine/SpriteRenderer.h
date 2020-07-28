#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <glm.h>

class SpriteRenderer {

	public:
		SpriteRenderer(Shader &shader);
        ~SpriteRenderer();
		void DrawSprite();

	private:
        Shader shader;
        unsigned int quadVAO;

		void initRenderData();
};
