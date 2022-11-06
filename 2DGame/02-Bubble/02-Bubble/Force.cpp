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
	FIRST, SECOND, THIRD
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Force::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/force.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(23, 20), glm::vec2(33 / 269.f, 25 / 505.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(FIRST, 4);
	sprite->addKeyframe(FIRST, glm::vec2(33 * 0 / 269.f, 25 * 0 / 505.f));
	sprite->addKeyframe(FIRST, glm::vec2(33 * 1 / 269.f, 25 * 0 / 505.f));
	sprite->addKeyframe(FIRST, glm::vec2(33 * 2 / 269.f, 25 * 0 / 505.f));
	sprite->addKeyframe(FIRST, glm::vec2(33 * 3 / 269.f, 25 * 0 / 505.f));
	sprite->addKeyframe(FIRST, glm::vec2(33 * 4 / 269.f, 25 * 0 / 505.f));
	sprite->addKeyframe(FIRST, glm::vec2(33 * 5 / 269.f, 25 * 0 / 505.f));

	sprite->setAnimationSpeed(SECOND, 4);
	sprite->addKeyframe(SECOND, glm::vec2(33 * 0 / 269.f, 25 * 1 / 505.f));
	sprite->addKeyframe(SECOND, glm::vec2(33 * 1 / 269.f, 25 * 1 / 505.f));
	sprite->addKeyframe(SECOND, glm::vec2(33 * 2 / 269.f, 25 * 1 / 505.f));
	sprite->addKeyframe(SECOND, glm::vec2(33 * 3 / 269.f, 25 * 1 / 505.f));
	sprite->addKeyframe(SECOND, glm::vec2(33 * 4 / 269.f, 25 * 1 / 505.f));
	sprite->addKeyframe(SECOND, glm::vec2(33 * 5 / 269.f, 25 * 1 / 505.f));

	sprite->setAnimationSpeed(THIRD, 4);
	sprite->addKeyframe(THIRD, glm::vec2(33 * 0 / 269.f, 25 * 2 / 505.f));
	sprite->addKeyframe(THIRD, glm::vec2(33 * 1 / 269.f, 25 * 2 / 505.f));
	sprite->addKeyframe(THIRD, glm::vec2(33 * 2 / 269.f, 25 * 2 / 505.f));
	sprite->addKeyframe(THIRD, glm::vec2(33 * 3 / 269.f, 25 * 2 / 505.f));

	sprite->setLoopAnimations(true),

	taken = false;
	inscreen = false;

	sprite->changeAnimation(FIRST);
	tileMapDispl = tileMapPos;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posForce.x), float(tileMapDispl.y + posForce.y)));

}

void Force::update(int deltaTime)
{
	if (sprite != NULL) {
		setCollisionBox(6, 17, 2, 12);
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

bool Force::calculateCollisions(int xmin, int xmax, int ymin, int ymax)
{
	return ((xMin < xmax) && (xmin < xMax)
		&& (yMin < ymax) && (ymin < yMax));
}

void Force::setCollisionBox(int xmin, int xmax, int ymin, int ymax)
{
	xMin = posForce.x + xmin;
	xMax = posForce.x + xmax;
	yMin = posForce.y + ymin;
	yMax = posForce.y + ymax;
}
