#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


enum EnemyAnims
{
	TYPE_1, TYPE_2, BOOM
};

//x35 y35
void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(25, 25), glm::vec2(35/483.f, 35/1787.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(TYPE_1, 4);
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 0 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 1 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 2 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 3 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 4 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 5 / 483.f, 35 * 0 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2, 4);
	sprite->addKeyframe(TYPE_2, glm::vec2(35 * 0 / 483.f, 35 * 1 / 1787.f));
	sprite->addKeyframe(TYPE_2, glm::vec2(35 * 1 / 483.f, 35 * 1 / 1787.f));
	sprite->addKeyframe(TYPE_2, glm::vec2(35 * 2 / 483.f, 35 * 1 / 1787.f));


 	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

	sprite->setLoopAnimations(true);
 	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (map->collisionMoveDown(posEnemy, glm::ivec2(16, 16)))
	{
		startY = posEnemy.y;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
  	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::setType(int t)
{
	type = t;
	switch (t) {
	case 1:
		sprite->changeAnimation(TYPE_1);
		break;
	case 2:
		sprite->changeAnimation(TYPE_2);
		break;
	default:
		break;
	}
}
