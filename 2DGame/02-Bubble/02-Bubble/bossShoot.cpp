#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "bossShoot.h"
#include "Game.h"
#include "Music.h"
#include <cmath>

enum bossShootAnims
{
	NORMAL, POWER, CHARGING
};


//la nau fa 33px  de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void bossShoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/aaa3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33 / 269.f, 25 / 269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(NORMAL, 8);

	sprite->addKeyframe(NORMAL, glm::vec2(33 * 0 / 269.f, 25 * 3 / 269.f));

	sprite->setAnimationSpeed(POWER, 8);
	sprite->addKeyframe(POWER, glm::vec2(33 * 6 / 269.f, 25 * 3 / 269.f));

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

void bossShoot::update(int deltaTime)
{
	sprite->setCharge(sprite->animation() == CHARGING);
	sprite->update(deltaTime);
	calculateCollisions();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));

}

void bossShoot::render()
{
	sprite->render();
}
//
//void bossShoot::destroy() {
//	delete sprite;
//	posbossShoot.x = 0;
//	posbossShoot.y = 0;
//}

void bossShoot::calculateCollisions()
{
	if (sprite->animation() != CHARGING) {
		if (sprite->animation() == POWER) {
			if (posBoss.x > ppos.x) {
				posbossShoot.x -= 1;
				if (posbossShoot.y < ppos.y) posbossShoot.y += 1;
				else if (posbossShoot.y > ppos.y) posbossShoot.y -= 1;
			}
		}
		if (sprite->animation() == NORMAL) {
			if (posBoss.x > lppos.x) {
				posbossShoot.x -= 1;
				if (posbossShoot.y < lppos.y) posbossShoot.y += 1;
				else if (posbossShoot.y > lppos.y) posbossShoot.y -= 1;
			}
		}
	}
	else {
		posbossShoot.x = posBoss.x + 22;
		posbossShoot.y = posBoss.y + 5;
	}
	switch (map->collisionMoveLeft(posbossShoot, glm::ivec2(28, 15)))
	{
	case 0:
		break;
	default:
		sprite->changeAnimation(POWER);
		break;
	}
}

void bossShoot::charge()
{
	sprite->changeAnimation(CHARGING);
	Music::instance().disparo_charge();
}

void bossShoot::powerbossShoot()
{
	sprite->changeAnimation(POWER);
	Music::instance().disparo2();
}

void bossShoot::setPlayerPos(glm::vec2& pos)
{
	posBoss = pos;
}

void bossShoot::setNavePos(glm::vec2& pos)
{
	ppos = pos;
}

void bossShoot::setPosition(const glm::vec2& pos)
{
	posbossShoot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));
}

void bossShoot::setNaveLastPos(glm::vec2& pos)
{
	lppos = pos;
}


float bossShoot::getPos()
{
	return posbossShoot.x;
}

void bossShoot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}