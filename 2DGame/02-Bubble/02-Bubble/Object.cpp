#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Game.h"
#include<windows.h>
#include "Music.h"



enum ObjectAnims
{
	NORMAL
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/force2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(20 / 269.f, 20 / 505.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(11 / 269.f, 12 / 505.f));

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

bool Object::animationFinished()
{
	return sprite->lastAnimation();
}

glm::vec2 Object::getPos()
{
	return posObject;
}

void Object::render()
{
	sprite->render();
}

void Object::calculateCollisions()
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

void Object::setTaken(bool b)
{
	taken = b;
}

void Object::setinscreen(bool b)
{
	inscreen = b;
}



void Object::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Object::setPosition(const glm::vec2& pos)
{
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}


void Object::sendcamera(float left, float right)
{
	cameraright = right;
	cameraleft = left;
}

bool Object::inScreen()
{
	return inscreen;
}

void Object::rightCollisions()
{
	posObject.x += 2;
	if (cameraright - 35 <= posObject.x) {
		posObject.x = cameraright - 35;
	}
}

void Object::leftCollisions()
{
	posObject.x -= 2;
}

void Object::upCollisions()
{
	posObject.y -= 2;
}

void Object::downCollisions()
{
	posObject.y += 2;
}




