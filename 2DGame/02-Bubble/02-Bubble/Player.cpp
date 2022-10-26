#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


enum PlayerAnims
{
	STAND, MOVE_UP, MOVE_DOWN, BOOM, REVERSE_UP, REVERSE_DOWN
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/spritesheet02.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33/269.f, 25/269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
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
		
		sprite->setAnimationSpeed(BOOM, 4);
		sprite->addKeyframe(BOOM, glm::vec2(33 * 0 / 269.f, 165 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 1 / 269.f, 160 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(80 / 269.f, 150 / 269.f));
		
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	isDead = false;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
    
	sprite->update(deltaTime);
	if (sprite->animation() == BOOM) {
		isDead = true;
	}
	else {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))				//MOVING LEFT
		{
			if (sprite->animation() != STAND)
				sprite->changeAnimation(STAND);
			posPlayer.x -= 2;
			switch (map->collisionMoveLeft(posPlayer, glm::ivec2(6, 14)))
			{
			case 0:
				break;
			case 2:
				posPlayer.x += 2;
				sprite->changeAnimation(BOOM);
				break;
			default:
				posPlayer.x += 2;
				sprite->changeAnimation(STAND);
				break;
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))			//MOVING RIGHT
		{
			if (sprite->animation() != STAND)
				sprite->changeAnimation(STAND);
			posPlayer.x += 2;
			switch (map->collisionMoveRight(posPlayer, glm::ivec2(23, 14), glm::ivec2(28, 15)))
			{
			case 0:
				break;
			case 2:
				posPlayer.x -= 2;
				sprite->changeAnimation(BOOM);
				break;
			default:
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND);
				break;
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))			//MOVING UP
		{
			if (sprite->animation() != MOVE_UP)
				sprite->changeAnimation(MOVE_UP);
			posPlayer.y -= 2;
			switch (map->collisionMoveUp(posPlayer, glm::ivec2(26, 12)))
			{
			case 0:
				break;
			case 2:
				posPlayer.y += 2;
				sprite->changeAnimation(BOOM);
				break;
			default:
				posPlayer.y += 2;
				sprite->changeAnimation(STAND);
				break;
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))			//MOVING DOWN
		{
			if (sprite->animation() != MOVE_DOWN)
				sprite->changeAnimation(MOVE_DOWN);
			posPlayer.y += 2;
			switch (map->collisionMoveDown(posPlayer, glm::ivec2(26, 20)))
			{
			case 0:
				break;
			case 2:
				posPlayer.y -= 2;
				sprite->changeAnimation(BOOM);
				break;
			default:
				posPlayer.y -= 2;
				sprite->changeAnimation(STAND);
				break;
			}
		}
		else
		{
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
		case 2:
			posPlayer.x -= 2;
			sprite->changeAnimation(BOOM);
			break;
		default:
			break;
		}

		posPlayer.x += 0.4;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
}

void Player::render()
{
	sprite->render();
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

bool Player::getIsDead()
{
	return isDead;
}