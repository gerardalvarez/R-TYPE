#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


enum PlayerAnims
{
	STAND, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, BOOM
};


//la nau fa 33px de x i 25px de y
void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/spritesheet02.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33/269.f, 25/269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND, 8);
		sprite->addKeyframe(STAND, glm::vec2(0 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(33*0 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(33*0 / 269.f, 25 / 269.f));

		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(33 * 1 / 269.f, 25 / 269.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(33 * 2 / 269.f, 25 / 269.f));
		
		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 0 / 269.f, 25 / 269.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 5 / 269.f, 25 * 2 / 269.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(33 * 4 / 269.f, 25 * 2 / 269.f));

		sprite->setAnimationSpeed(BOOM, 4);
		sprite->addKeyframe(BOOM, glm::vec2(33 * 0 / 269.f, 165 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(33 * 1 / 269.f, 160 / 269.f));
		sprite->addKeyframe(BOOM, glm::vec2(80 / 269.f, 150 / 269.f));
		
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
    
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(8, 16)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(BOOM);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(26, 10))) //caixa rara
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(BOOM);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		posPlayer.y -= 2;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(16, 16), (int*)&posPlayer.y)) //not implemented
		{
			posPlayer.y -= 2;
			sprite->changeAnimation(STAND);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		posPlayer.y += 2;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), (int*)&posPlayer.y))
		{
			posPlayer.y -= 2;
			sprite->changeAnimation(STAND);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND);
	}
	
	if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 16), (int*) & posPlayer.y))
	{
		startY = posPlayer.y;
		
	}

    posPlayer.x+=0.4;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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