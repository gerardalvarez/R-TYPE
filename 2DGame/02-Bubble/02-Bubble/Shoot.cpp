#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shoot.h"
#include "Game.h"
#include "Music.h"


enum ShootAnims
{
	NORMAL, POWER, CHARGING, ENEMY, GONE, BOSSHIT, BOSSHITHARD, FORCE1, FORCE2, FORCE3, WAVESHOOT1, WAVESHOOT2
};


//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Shoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/AAA.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(33, 30), glm::vec2(33 / 269.f, 25 / 269.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

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

	sprite->setAnimationSpeed(BOSSHIT, 8);
	sprite->addKeyframe(BOSSHIT, glm::vec2(33 * 0 / 269.f, 25 * 5 / 269.f));
	sprite->addKeyframe(BOSSHIT, glm::vec2(33 * 2 / 269.f, 25 * 5 / 269.f));
	sprite->addKeyframe(BOSSHIT, glm::vec2(33 * 3 / 269.f, 25 * 5 / 269.f));

	sprite->setAnimationSpeed(BOSSHITHARD, 8);
	sprite->addKeyframe(BOSSHITHARD, glm::vec2(33 * 4 / 269.f, 25 * 5 / 269.f));
	sprite->addKeyframe(BOSSHITHARD, glm::vec2(33 * 4 / 269.f, 25 * 5 / 269.f));

	sprite->setAnimationSpeed(FORCE1, 2);
	sprite->addKeyframe(FORCE1, glm::vec2(33 * 0 / 269.f, 25 * 7 / 269.f));

	sprite->setAnimationSpeed(FORCE2, 2);
	sprite->addKeyframe(FORCE2, glm::vec2(33 * 1 / 269.f, 25 * 7 / 269.f));

	sprite->setAnimationSpeed(FORCE3, 2);
	sprite->addKeyframe(FORCE3, glm::vec2(33 * 2 / 269.f, 25 * 7 / 269.f));

	sprite->setAnimationSpeed(WAVESHOOT1, 2);
	sprite->addKeyframe(WAVESHOOT1, glm::vec2(33 * 0 / 269.f, 25 * 8 / 269.f));

	sprite->setAnimationSpeed(WAVESHOOT2, 2);
	sprite->addKeyframe(WAVESHOOT2, glm::vec2(33 * 1 / 269.f, 25 * 8 / 269.f));
	sprite->addKeyframe(WAVESHOOT2, glm::vec2(33 * 2 / 269.f, 25 * 8 / 269.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(pos.x), float(pos.y)));

	gone = false;
	bossHitted = false;
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
		setCollisionBox(12, 15, 12, 16);
		posShoot.x += xDirection;
		posShoot.y += yDirection;
	}
	else if (sprite->animation() == WAVESHOOT1) {
		setCollisionBox(1, 31, 6, 23);
		sprite->changeAnimation(WAVESHOOT2);
		sprite->setLoopAnimations(true);
		posShoot.x += 4;
	}
	else if (sprite->animation() == WAVESHOOT2) {
		setCollisionBox(1, 31, 6, 23);
		posShoot.x += 4;
	}
	else if (sprite->animation() == BOSSHIT || sprite->animation() == BOSSHITHARD) {
		if (sprite->lastAnimation()) {
			disapear();
		}
	}
	else if (sprite->animation() == FORCE1) {
		setCollisionBox(7, 22, 16, 17);
		posShoot.x += 4;
	}
	else if (sprite->animation() == FORCE2 || sprite->animation() == FORCE3) {
		setCollisionBox(14, 20, 11, 17);
		posShoot.x += 4;
		posShoot.y += yDirection;
	}
	else if (sprite->animation() != CHARGING){
		setCollisionBox(12, 18, 14, 17);
		posShoot.x += 4;
	}
	else {
		setCollisionBox(10, 23, 8, 18);
		posShoot.x = posPlayer.x + 22;
		posShoot.y = posPlayer.y + 5;
	}
}

bool Shoot::calculateEnemyCollisions(int xmin, int xmax, int ymin, int ymax)
{
	if (sprite->animation() == ENEMY) {
		return false;
	}
	if (gone) {
		return false;
	}
	return ((xMin < xmax) && (xmin < xMax)
		&& (yMin < ymax) && (ymin < yMax));
}

bool Shoot::calculatePlayerCollisions(int xmin, int xmax, int ymin, int ymax)
{
	if (sprite->animation() != ENEMY) {
		return false;
	}
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
	posObjective.x = posPlayer.x + 50;
	posObjective.y = posPlayer.y + 2;
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

void Shoot::calculateForceYDirecection(int r)
{
	double x1 = posPlayer.x;
	double x2 = r;
	double y1 = posPlayer.y;
	double y2 = 0;
	if (sprite->animation() == FORCE2) {
		yDirection = -1;
	}
	else {
		yDirection = 1;
	}
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

void Shoot::hitBoss()
{
	bossHitted = true;
	if (sprite->animation() == POWER) {
		sprite->changeAnimation(BOSSHITHARD);
	}
	else if (sprite->animation() == NORMAL) {
		sprite->changeAnimation(BOSSHIT);
	}
	else if (sprite->animation() == FORCE1 || sprite->animation() == FORCE2 || sprite->animation() == FORCE3 ) {
		sprite->changeAnimation(BOSSHIT);
	}
}

bool Shoot::getBossHitted()
{
	return bossHitted;
}

int Shoot::getDamage()
{
	if (sprite->animation() == BOSSHIT || sprite->animation() == NORMAL || sprite->animation() == ENEMY) {
		return 1;
	}
	else if (sprite->animation() == BOSSHITHARD || sprite->animation() == POWER ) {
		return 2;
	}
	else if (sprite->animation() == WAVESHOOT1 || sprite->animation() == WAVESHOOT2) {
		return 3;
	}
	else {
		return 1;
	}
}

bool Shoot::isCharge()
{
	return (sprite->animation() == CHARGING);
}

bool Shoot::isEnemy()
{
	return (sprite->animation() == ENEMY);
}

void Shoot::force(int type)
{
	if (type == 1) {
		sprite->changeAnimation(FORCE1);
	}
	else if (type == 2) {
		sprite->changeAnimation(FORCE2);
	}
	else{
		sprite->changeAnimation(FORCE3);
	}
}

void Shoot::waveShoot()
{
	sprite->changeAnimation(WAVESHOOT1);
}

bool Shoot::mapCollisions()
{
	if (map->shootMapCollision(xMin, xMax, yMin, yMax) != 0) {
		return true;
	}
	return false;
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

int Shoot::getxMin()
{
	return xMin;
}

int Shoot::getxMax()
{
	return xMax;
}

int Shoot::getyMin()
{
	return yMin;
}

int Shoot::getyMax()
{
	return yMax;
}
