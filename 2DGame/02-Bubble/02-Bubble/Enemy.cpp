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
	sprite[0] = Sprite::createSprite(glm::ivec2(35, 35), glm::vec2(35/506.f, 35/1856.f), &spritesheet, &shaderProgram);
	sprite[0]->setNumberAnimations(1);

	sprite[0]->setAnimationSpeed(STAND, 8);
	sprite[0]->addKeyframe(STAND, glm::vec2(35 * 1 / 506.f, 35 * 3 / 1856.f));
	sprite[0]->addKeyframe(STAND, glm::vec2(35 * 2 / 506.f, 35 * 3 / 1856.f));
	sprite[0]->addKeyframe(STAND, glm::vec2(35 * 3 / 506.f, 35 * 3 / 1856.f));

 	sprite[0]->changeAnimation(0);
	tileMapDispl = tileMapPos;
 	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::update(int deltaTime)
{
	if (this != NULL) {
		sprite[0]->update(deltaTime);

		if (map->collisionMoveDown(posEnemy, glm::ivec2(16, 16)))
		{
			startY = posEnemy.y;
		}
		else {
			posEnemy.x -= 1;
			posEnemy.y += 1;
		}

		sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
}

void Enemy::render()
{
	sprite[0]->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
  	posEnemy = pos;
	sprite[0]->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}