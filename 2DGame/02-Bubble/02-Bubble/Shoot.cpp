#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shoot.h"
#include "Game.h"
#include "Music.h"


enum ShootAnims
{
	NORMAL, POWER, CHARGING, ENEMY, GONE
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Shoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/AAA.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33 / 269.f, 25 / 269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(NORMAL, 2);
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

	sprite->setAnimationSpeed(ENEMY, 2);
	sprite->addKeyframe(ENEMY, glm::vec2(33 * 4 / 269.f, 25 * 4 / 269.f));

	sprite->setAnimationSpeed(GONE, 2);
	sprite->addKeyframe(GONE, glm::vec2(33 * 5 / 269.f, 25 * 4 / 269.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(pos.x), float(pos.y)));

	gone = false;
}

void Shoot::update(int deltaTime)
{
	sprite->setLoopAnimations(sprite->animation() == CHARGING);
	sprite->update(deltaTime);
	calculateCollisions();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShoot.x), float(tileMapDispl.y + posShoot.y)));
	
}

void Shoot::render()
{
	sprite->render();
}

void Shoot::calculateCollisions()
{
	if (sprite->animation() == ENEMY) {
		//setCollisionBox(x,x,y,y);
		posShoot.x += xDirection;
		posShoot.y += yDirection;
	}
	else if (sprite->animation() != CHARGING){
		setCollisionBox(12, 18, 14, 17);
		posShoot.x += 4;
	}
	else {
		posShoot.x = posPlayer.x + 22;
		posShoot.y = posPlayer.y + 5;
	}
}

bool Shoot::calculateEnemyCollisions(int xmin, int xmax, int ymin, int ymax)
{
	if (gone) {
		return false;
	}
	return ((xMin < xmax) && (xmin < xMax)
		&& (yMin < ymax) && (ymin < yMax));
}

void Shoot::charge()
{
	sprite->changeAnimation(CHARGING);
	Music::instance().disparo_charge();
}

void Shoot::powerShoot()
{
	sprite->changeAnimation(POWER);
	Music::instance().disparo2();
}

void Shoot::enemyShoot()
{
	sprite->changeAnimation(ENEMY);
	posObjective.x = posPlayer.x + 5;
	posObjective.y = posPlayer.y;
	calculateXDirecection();
	calculateYDirecection();
	
}

void Shoot::setPlayerPos(glm::vec2& pos)
{
	posPlayer = pos;
}

void Shoot::setEnemyPos(glm::vec2& pos)
{
	posEnemy = pos;
}

void Shoot::calculateXDirecection()
{
	if (posObjective.x < posShoot.x) {
		xDirection = -1;
	}
	else if (posObjective.x > posShoot.x) {
		xDirection = 1;
	}
	else {
		xDirection = 0;
	}
}

void Shoot::calculateYDirecection()
{
	double x1 = posEnemy.x;
	double x2 = posObjective.x;
	double y1 = posEnemy.y;
	double y2 = posObjective.y;

	yDirection = -((y2 - y1) / (x2 - x1));
}

void Shoot::setCollisionBox(int xmin, int xmax, int ymin, int ymax)
{
	xMin = posShoot.x + xmin;
	xMax = posShoot.x + xmax;
	yMin = posShoot.y + ymin;
	yMax = posShoot.y + ymax;
}

bool Shoot::getGone()
{
	return gone;
}

void Shoot::disapear()
{
	if (!gone) {
		gone = true;
		sprite->changeAnimation(GONE);
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