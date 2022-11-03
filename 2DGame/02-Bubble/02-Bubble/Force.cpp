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
	NORMAL,VERTICALSHOOTS,DOUBLESHOOT
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Force::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/force.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(23, 20), glm::vec2(33 / 269.f, 25 / 505.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(10 / 269.f, 43 / 505.f));

	sprite->setAnimationSpeed(VERTICALSHOOTS, 8);
	sprite->addKeyframe(VERTICALSHOOTS, glm::vec2(33 * 0 / 269.f, 25 / 505.f));
	sprite->addKeyframe(VERTICALSHOOTS, glm::vec2(33 * 1 / 269.f, 25 / 505.f));
	sprite->addKeyframe(VERTICALSHOOTS, glm::vec2(33 * 2 / 269.f, 25 / 505.f));

	sprite->setAnimationSpeed(DOUBLESHOOT, 8);
	sprite->addKeyframe(DOUBLESHOOT, glm::vec2(33 * 0 / 269.f, 25 / 505.f));
	sprite->addKeyframe(DOUBLESHOOT, glm::vec2(33 * 5 / 269.f, 25 * 2 / 505.f));
	sprite->addKeyframe(DOUBLESHOOT, glm::vec2(33 * 4 / 269.f, 25 * 2 / 505.f));



	taken = false;
	sprite->changeAnimation(NORMAL);
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

bool Force::animationFinished()
{
	return sprite->lastAnimation();
}

void Force::render()
{
	sprite->render();
}

void Force::calculateCollisions()
{
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP))					//MOVING RIGHT UP
	{
		rightCollisions();
		upCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))			//MOVING RIGHT DOWN
	{
		rightCollisions();
		downCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))				//MOVING LEFT UP
	{

		leftCollisions();
		upCollisions();

	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))			//MOVING LEFT DOWN
	{
		
		leftCollisions();
		downCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))				//MOVING LEFT
	{
		leftCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))			//MOVING RIGHT
	{

		rightCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))				//MOVING UP
	{
		upCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))				//MOVING DOWN
	{

		downCollisions();
	}


}

void Force::setTaken(bool b)
{
	taken = b;
}


void Force::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Force::setPosition(const glm::vec2& pos)
{
	posForce = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posForce.x), float(tileMapDispl.y + posForce.y)));
}


void Force::sendcamera(float left, float right)
{
	cameraright = right;
	cameraleft = left;
}

void Force::rightCollisions()
{
	posForce.x += 2;
	if (cameraright - 35 <= posForce.x) {
		posForce.x = cameraright - 35;
	}
}

void Force::leftCollisions()
{
	posForce.x -= 2;
}

void Force::upCollisions()
{
	posForce.y -= 2;
}

void Force::downCollisions()
{
	posForce.y += 2;
}

glm::vec2 Force::getPos()
{
	return posForce;
}



