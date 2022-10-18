#pragma once
 
#include "BaseScene.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Music.h"

class Menu : public BaseScene
{
public:
	Menu();
	~Menu();

	void init(int level);
	void update(int deltaTime);
	void render();
	void loadSprites();

private:
	struct Option {
		Sprite* sprite;
		Texture spritesheet;
	};


	Texture scene;
	Option options[7];
	int option; //opcion seleccionada

};