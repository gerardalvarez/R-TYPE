#pragma once

#include "BaseScene.h"
#include "Text.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MenuScene : public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void init(int level);
	void update(int deltaTime);
	void render();
	void loadSprites();

private:
	Texture scene;
	Text text;
};