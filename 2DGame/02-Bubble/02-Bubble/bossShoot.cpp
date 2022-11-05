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
	calculateTrajectory();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));

}

void BossShoot::render()
{
	sprite->render();
}

void BossShoot::powerbossShoot()
{
	sprite->changeAnimation(POWER);
	posObjective.x = playerPos.x;
	posObjective.y = playerPos.y - 5;
	calculateXDirecection();
	calculateYDirecection();
	Music::instance().disparoboss2();
}

void BossShoot::normalBossShoot()
{
	posObjective.x = playerPos.x + 5;
	posObjective.y = playerPos.y;
	calculateXDirecection();
	calculateYDirecection();
}

void BossShoot::setBossPos(glm::vec2& pos)
{
	posBoss = pos;
}

void BossShoot::setPlayerPos(glm::vec2& pos)
{
	playerPos = pos;
}

void BossShoot::setCollisionBox(int xmin, int xmax, int ymin, int ymax)
{
	xMin = posbossShoot.x + xmin;
	xMax = posbossShoot.x + xmax;
	yMin = posbossShoot.y + ymin;
	yMax = posbossShoot.y + ymax;
}

void BossShoot::calculateXDirecection()
{
	if (posObjective.x < posbossShoot.x) {
		xDirection = -1;
	}
	else if (posObjective.x > posbossShoot.x) {
		xDirection = 1;
	}
	else {
		xDirection = 0;
	}
}

void BossShoot::calculateYDirecection()
{
	double x1 = posbossShoot.x;
	double x2 = posObjective.x;
	double y1 = posbossShoot.y;
	double y2 = posObjective.y;

	yDirection = -((y2 - y1) / (x2 - x1));
}

void BossShoot::calculateTrajectory()
{
	posbossShoot.x += xDirection;
	posbossShoot.y += yDirection;
}

void BossShoot::setPosition(const glm::vec2& pos)
{
	posbossShoot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posbossShoot.x), float(tileMapDispl.y + posbossShoot.y)));
}

float BossShoot::getPosx()
{
	return posbossShoot.x;
}