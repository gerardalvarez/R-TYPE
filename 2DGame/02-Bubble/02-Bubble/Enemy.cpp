#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


enum EnemyAnims
{
	STAND, BOOM
};

//x35 y35
void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	posEnemy.x = 192;
	posEnemy.y = 192;
	spritesheet.loadFromFile("images/Enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 35), glm::vec2(35/506.f, 35/1787.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(35 * 0 / 483.f, 35 * 0 / 1787.f));
	//sprite->addKeyframe(STAND, glm::vec2(35 * 1 / 483.f, 35 * 0 / 1787.f));
	//sprite->addKeyframe(STAND, glm::vec2(35 * 2 / 483.f, 35 * 0 / 1787.f));
	//sprite->addKeyframe(STAND, glm::vec2(35 * 3 / 483.f, 35 * 0 / 1787.f));
	//sprite->addKeyframe(STAND, glm::vec2(35 * 4 / 483.f, 35 * 0 / 1787.f));
	//sprite->addKeyframe(STAND, glm::vec2(35 * 5 / 483.f, 35 * 0 / 1787.f));

 	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
 	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (map->collisionMoveDown(posEnemy, glm::ivec2(16, 16)))
	{
		startY = posEnemy.y;
	}
	else {
		posEnemy.x -= 1;
		posEnemy.y += 1;
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