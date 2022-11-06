#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include<windows.h>
#include "Music.h"
#include <list>



enum PlayerAnims
{
	STAND, MOVE_UP, MOVE_DOWN, BOOM, REVERSE_UP, REVERSE_DOWN, GOD, BOOM2
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/AAA.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33/269.f, 25/269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
		sprite->setAnimationSpeed(STAND, 8);
		sprite->addKeyframe(STAND, glm::vec2(0 / 269.f, 25 / 269.f));

		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(33 * 0 / 269.f, 25 / 269.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(33 * 1 / 269.f, 25 / 269.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(33 * 2 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 0 / 269.f, 25 / 269.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 5 / 269.f, 25 * 2 / 269.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 4 / 269.f, 25 * 2 / 269.f));

		sprite->setAnimationSpeed(REVERSE_UP, 8);
		sprite->addKeyframe(REVERSE_UP, glm::vec2(33 * 2 / 269.f, 25 / 269.f));
		sprite->addKeyframe(REVERSE_UP, glm::vec2(33 * 1 / 269.f, 25 / 269.f));
		sprite->addKeyframe(REVERSE_UP, glm::vec2(33 * 0 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(REVERSE_DOWN, 8);
		sprite->addKeyframe(REVERSE_DOWN, glm::vec2(33 * 4 / 269.f, 25 * 2 / 269.f));
		sprite->addKeyframe(REVERSE_DOWN, glm::vec2(33 * 5 / 269.f, 25 * 2 / 269.f));
		sprite->addKeyframe(REVERSE_DOWN, glm::vec2(33 * 0 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(BOOM, 16);
		sprite->addKeyframe(BOOM, glm::vec2(33 * 0 / 269.f, 25 * 6 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 1 / 269.f, 25 * 6 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 2 / 269.f, 25 * 6 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 3 / 269.f, 25 * 6 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 4 / 269.f, 25 * 6 / 269.f));

		sprite->setAnimationSpeed(GOD, 8);
		sprite->addKeyframe(GOD, glm::vec2(33 * 6 / 269.f, 25 * 2 / 269.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	isDead = false;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	lives = 3;

}

void Player::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->update(deltaTime);
		if (sprite->animation() == BOOM) {
			isDead = true;
		}
		else {
			calculateMapCollisions();
			if (cameraright <= 3070) {
				posPlayer.x += 0.4;
			}
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		}
	}
}

int Player::getlives()
{
	return lives;
}

void Player::revive()
{
	
	--lives;
	isDead = false;
	explode = false;
	posPlayer.y = 192/2-15;
	posPlayer.x = cameraright -((cameraright - cameraleft) / 2)-70;
	sprite->changeAnimation(STAND);
	//Sleep(2000);

}

void Player::setCollisionBox(int xmin, int xmax, int ymin, int ymax)
{
	xMin = posPlayer.x + xmin;
	xMax = posPlayer.x + xmax;
	yMin = posPlayer.y + ymin;
	yMax = posPlayer.y + ymax;
}


bool Player::animationFinished()
{
	return sprite->lastAnimation();
}

void Player::setBoom()
{
	if (!godMode) {
		sprite->changeAnimation(BOOM);
		explode = true;
	}
}

bool Player::getExplode()
{
	return explode;
}

void Player::render()
{
	sprite->render();
}

void Player::calculateMapCollisions() 
{
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP))					//MOVING RIGHT UP
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		setCollisionBox(5, 27, 13, 25);
		rightCollisions();
		upCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))			//MOVING RIGHT DOWN
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		setCollisionBox(5, 26, 11, 23);
		rightCollisions();
		downCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))				//MOVING LEFT UP
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		setCollisionBox(5, 27, 13, 25);
		leftCollisions();
		upCollisions();
	
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))			//MOVING LEFT DOWN
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		setCollisionBox(5, 26, 11, 23);
		leftCollisions();
		downCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))				//MOVING LEFT
	{
		if (sprite->animation() != STAND)
			sprite->changeAnimation(STAND);
		setCollisionBox(5, 28, 14, 25);
		leftCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))			//MOVING RIGHT
	{
		setCollisionBox(5, 28, 14, 25);
		if (sprite->animation() != STAND)
			sprite->changeAnimation(STAND);
		rightCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))				//MOVING UP
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		setCollisionBox(5, 27, 13, 25);
		upCollisions();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))				//MOVING DOWN
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		setCollisionBox(5, 26, 13, 23);
		downCollisions();
	}
	else
	{
		setCollisionBox(5, 28, 12, 21);
		if (sprite->animation() == MOVE_UP)
			sprite->changeAnimation(REVERSE_UP);
		else if (sprite->animation() == MOVE_DOWN)
			sprite->changeAnimation(REVERSE_DOWN);
		else {
			sprite->changeAnimation(STAND);
		}
	}

	switch (map->collisionMoveRight(posPlayer, glm::ivec2(23, 14), glm::ivec2(28, 15)))
	{
	case 1:
		updatePositionX(-2);
		sprite->changeAnimation(BOOM);
		break;
	case 2:
		updatePositionX(-2);
		break;
	default:
		break;
	}

	if (godMode) {
		sprite->changeAnimation(GOD);
	}
}


void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::updatePositionX(int x)
{
	if(!godMode) posPlayer.y += x;
}

void Player::updatePositionY(int y)
{
	if (!godMode) posPlayer.y += y;
}

void Player::sendcamera(float left,float right)
{
	cameraright = right;
	cameraleft = left;
}

void Player::rightCollisions()
{
	posPlayer.x += 1;
	if (cameraright - 35 <= posPlayer.x) {
		posPlayer.x = cameraright - 35;
	}
	switch (map->collisionMoveRight(posPlayer, glm::ivec2(23, 14), glm::ivec2(28, 15)))
	{
	case 0:
		break;
	case 1:
		updatePositionX(-1);
		sprite->changeAnimation(BOOM);
		break;
	default:
		updatePositionX(-1);
		sprite->changeAnimation(STAND);
		break;
	}
}

void Player::leftCollisions()
{
	posPlayer.x -= 1;
	if (cameraleft + 5 >= posPlayer.x) {
		posPlayer.x = cameraleft + 5;
	}
	switch (map->collisionMoveLeft(posPlayer, glm::ivec2(6, 14)))
	{
	case 0:
		break;
	case 1:
		updatePositionX(1);
		sprite->changeAnimation(BOOM);
		break;
	default:
		updatePositionX(1);
		sprite->changeAnimation(STAND);
		break;
	}
}

void Player::upCollisions()
{
	posPlayer.y -= 1;
	switch (map->collisionMoveUp(posPlayer, glm::ivec2(26, 12)))
	{
	case 0:
		break;
	case 1:
		updatePositionY(1);
		sprite->changeAnimation(BOOM);
		break;
	default:
		updatePositionY(1);
		sprite->changeAnimation(STAND);
		break;
	}
}

void Player::downCollisions()
{
	posPlayer.y += 1;
	switch (map->collisionMoveDown(posPlayer, glm::ivec2(26, 20)))
	{
	case 0:
		break;
	case 1:
		updatePositionY(-6);
		sprite->changeAnimation(BOOM);
		break;
	default:
		updatePositionY(-1);
		sprite->changeAnimation(STAND);
		break;
	}
}

glm::vec2 Player::getPos()
{
	return posPlayer;
}

bool Player::getIsDead()
{
	return isDead;
}

void Player::setGodMode(bool godModeActive){
	godMode = godModeActive;
}

int Player::getxMin()
{
	return xMin;
}

int Player::getxMax()
{
	return xMax;
}

int Player::getyMin()
{
	return yMin;
}

int Player::getyMax()
{
	return yMax;
}
