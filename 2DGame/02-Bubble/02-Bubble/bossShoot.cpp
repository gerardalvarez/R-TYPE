#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BossShoot.h"
#include "Game.h"
#include "Music.h"
#include <cmath>

enum BossShootAnims
{
	NORMAL, POWER, CHARGING
};


void BossShoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/aaa3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33 / 269.f, 25 / 269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(33 * 0 / 269.f, 25 * 3 / 269.f));

	sprite->setAnimationSpeed(POWER, 8);
	sprite->addKeyframe(POWER, glm::vec2(33 * 6 / 269.f, 25 * 3 / 269.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(pos.x), float(pos.y)));

}

void BossShoot::update(int deltaTime)
{
	sprite->update(deltaTime);
	calculateCollisions();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));

}

void BossShoot::render()
{
	sprite->render();
}

void BossShoot::calculateCollisions()
{
	if (sprite->animation() == POWER) {

		posbossShoot.x -= 1;

		if (posbossShoot.y < ppos.y) 
			posbossShoot.y += 1;
		else if (posbossShoot.y > ppos.y) 
			posbossShoot.y -= 1;
		
	}
	if (sprite->animation() == NORMAL) {
		if (posbossShoot.x < lppos.x) {
			if (posbossShoot.y < lppos.y) posbossShoot.y += 1;
			else if (posbossShoot.y > lppos.y) posbossShoot.y -= 1;
			posbossShoot.x -= 1;
		}
		else
			if (abs(posbossShoot.y - lppos.y) > abs(posbossShoot.x - lppos.x)) {
				if (posbossShoot.y < lppos.y) posbossShoot.y += 1;
				else if (posbossShoot.y > lppos.y) posbossShoot.y -= 1;
				posbossShoot.x -= 0.2;
			}
			else if (abs(posbossShoot.y - lppos.y) < abs(posbossShoot.x - lppos.x)) {
				if (posbossShoot.y < lppos.y) posbossShoot.y += 0.2;
				else if (posbossShoot.y > lppos.y) posbossShoot.y -= 0.2;
				posbossShoot.x -= 1;
			}
			else {
				posbossShoot.x -= 1;
				if (posbossShoot.y < lppos.y) posbossShoot.y += 1;
				else if (posbossShoot.y > lppos.y) posbossShoot.y -= 1;
			}
	}
}

void BossShoot::charge()
{
	sprite->changeAnimation(CHARGING);
	Music::instance().disparo_charge();
}

void BossShoot::powerbossShoot()
{
	sprite->changeAnimation(POWER);
	Music::instance().disparoboss2();
}

void BossShoot::setPlayerPos(glm::vec2& pos)
{
	posBoss = pos;
}

void BossShoot::setNavePos(glm::vec2& pos)
{
	ppos = pos;
}

void BossShoot::setPosition(const glm::vec2& pos)
{
	posbossShoot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));
}

void BossShoot::setNaveLastPos(glm::vec2& pos)
{
	lppos = pos;
}

glm::vec2 BossShoot::getNaveLastPos()
{
	return lppos;
}


float BossShoot::getPosx()
{
	return posbossShoot.x;
}
float BossShoot::getPosy()
{
	return posbossShoot.x;
}

void BossShoot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}