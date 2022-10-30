#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shoot.h"
#include "Game.h"


enum ShootAnims
{
	NORMAL, POWER, CHARGING
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Shoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/AAA.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33 / 269.f, 25 / 269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(33 * 0 / 269.f, 25 * 3 / 269.f));
	sprite->addKeyframe(NORMAL, glm::vec2(33 * 1 / 269.f, 25 * 3 / 269.f));

	sprite->setAnimationSpeed(POWER, 8);
	sprite->addKeyframe(POWER, glm::vec2(33 * 1 / 269.f, 25 * 4 / 269.f));
	sprite->addKeyframe(POWER, glm::vec2(33 * 2 / 269.f, 25 * 4 / 269.f));
	sprite->addKeyframe(POWER, glm::vec2(33 * 3 / 269.f, 25 * 4 / 269.f));

	sprite->setAnimationSpeed(CHARGING, 4);
	sprite->addKeyframe(CHARGING, glm::vec2(33 * 2 / 269.f, 25 * 3 / 269.f));
	sprite->addKeyframe(CHARGING, glm::vec2(33 * 3 / 269.f, 25 * 3 / 269.f));
	sprite->addKeyframe(CHARGING, glm::vec2(33 * 4 / 269.f, 25 * 3 / 269.f));
	sprite->addKeyframe(CHARGING, glm::vec2(33 * 5 / 269.f, 25 * 3 / 269.f));
	sprite->addKeyframe(CHARGING, glm::vec2(33 * 0 / 269.f, 25 * 4 / 269.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(pos.x), float(pos.y)));

}

void Shoot::update(int deltaTime)
{
	sprite->update(deltaTime);
	calculateCollisions();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShoot.x), float(tileMapDispl.y + posShoot.y)));
	
}

void Shoot::render()
{
	sprite->render();
}
//
//void Shoot::destroy() {
//	delete sprite;
//	posShoot.x = 0;
//	posShoot.y = 0;
//}

void Shoot::calculateCollisions()
{
	posShoot.x += 6;
	switch (map->collisionMoveRight(posShoot, glm::ivec2(23, 14), glm::ivec2(28, 15)))
	{
	case 0:
		break;
	default:
		sprite->changeAnimation(POWER);
		break;
	}
}

void Shoot::setPosition(const glm::vec2& pos)
{
	posShoot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShoot.x), float(tileMapDispl.y + posShoot.y)));
}

float Shoot::getPos()
{
	return posShoot.x;
}

void Shoot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}