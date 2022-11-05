#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Force.h"
#include "Game.h"
#include<windows.h>
#include "Music.h"



enum ForceAnims
{
	SMALL,VERTICALSHOOTS,DOUBLESHOOT
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Force::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/force.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(23, 20), glm::vec2(33 / 269.f, 25 / 505.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(SMALL, 8);
	sprite->addKeyframe(SMALL, glm::vec2(10 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(10 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(43 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(43 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(76 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(76 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(109 / 269.f, 43 / 505.f));
	sprite->addKeyframe(SMALL, glm::vec2(109 / 269.f, 43 / 505.f));
	sprite->setLoopAnimations(true),

	taken = false;
	inscreen = false;
	sprite->changeAnimation(SMALL);
	tileMapDispl = tileMapPos;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posForce.x), float(tileMapDispl.y + posForce.y)));

}

void Force::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posForce.x), float(tileMapDispl.y + posForce.y)));
		sprite->update(deltaTime);
	}
}


bool Force::istaken()
{
	return taken;
}

glm::vec2 Force::getPos()
{
	return posForce;
}

void Force::render()
{
	sprite->render();
}

void Force::setTaken(bool b)
{
	taken = b;
}

void Force::setinscreen(bool b)
{
	inscreen = b;
}

void Force::setPosition(const glm::vec2& pos)
{
	posForce = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posForce.x), float(tileMapDispl.y + posForce.y)));
}

bool Force::inScreen()
{
	return inscreen;
}