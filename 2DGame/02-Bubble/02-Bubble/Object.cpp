#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Game.h"
#include<windows.h>


enum ObjectAnims
{
	NORMAL,VIDA, FORCE2
};

//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/force3.png", TEXTURE_PIXEL_FORMAT_RGBA);


	sprite = Sprite::createSprite(glm::ivec2(10, 10), glm::vec2(20 / 269.f, 20 / 505.f), &spritesheet, &shaderProgram);
	
	
	sprite->setNumberAnimations(3);
	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(11 / 269.f, 12 / 505.f));

	sprite->setAnimationSpeed(VIDA, 8);
	sprite->addKeyframe(VIDA, glm::vec2(43 / 269.f, 12 / 505.f));

	sprite->setAnimationSpeed(FORCE2, 8);
	sprite->addKeyframe(FORCE2, glm::vec2(79 / 269.f, 12 / 505.f));

	taken = false;
	inscreen = false;
	sprite->changeAnimation(NORMAL);
	tileMapDispl = tileMapPos;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));

}

void Object::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
		sprite->update(deltaTime);
	}

}

bool Object::istaken()
{
	return taken;
}

glm::vec2 Object::getPos()
{
	return posObject;
}

void Object::render()
{
	sprite->render();
}

void Object::setTaken(bool b)
{
	taken = b;
}

void Object::setinscreen(bool b)
{
	inscreen = b;
}

void Object::setPosition(const glm::vec2& pos)
{
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

bool Object::inScreen()
{
	return inscreen;
}

void Object::setvida()
{
	sprite->changeAnimation(VIDA);
}

