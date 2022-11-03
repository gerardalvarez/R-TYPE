#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


enum EnemyAnims
{
	TYPE_1, 
	TYPE_2_FACEUP1, TYPE_2_FACEUP2, TYPE_2_FACEUP3, TYPE_2_FACEUP4,
	TYPE_2_FACEDOWN1, TYPE_2_FACEDOWN2, TYPE_2_FACEDOWN3, TYPE_2_FACEDOWN4,
	TYPE_3_FLY, TYPE_3_LAND, TYPE_3_WALK,
	TYPE_4,
	BOOM
};

//x35 y35
void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int vida)
{
	spritesheet.loadFromFile("images/Enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texProgram = shaderProgram;
	sprite = Sprite::createSprite(glm::ivec2(25, 25), glm::vec2(35/483.f, 35/1787.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(13);

	sprite->setAnimationSpeed(TYPE_1, 4);
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 0 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 1 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 2 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 3 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 4 / 483.f, 35 * 0 / 1787.f));
	sprite->addKeyframe(TYPE_1, glm::vec2(35 * 5 / 483.f, 35 * 0 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEUP1, 4);
	sprite->addKeyframe(TYPE_2_FACEUP1, glm::vec2(35 * 0 / 483.f, 35 * 1 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEUP2, 4);
	sprite->addKeyframe(TYPE_2_FACEUP2, glm::vec2(35 * 1 / 483.f, 35 * 1 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEUP3, 4);
	sprite->addKeyframe(TYPE_2_FACEUP3, glm::vec2(35 * 2 / 483.f, 35 * 1 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEUP4, 4);
	sprite->addKeyframe(TYPE_2_FACEUP4, glm::vec2(35 * 3 / 483.f, 35 * 1 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEDOWN1, 4);
	sprite->addKeyframe(TYPE_2_FACEDOWN1, glm::vec2(35 * 0 / 483.f, 35 * 2 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEDOWN2, 4);
	sprite->addKeyframe(TYPE_2_FACEDOWN2, glm::vec2(35 * 1 / 483.f, 35 * 2 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEDOWN3, 4);
	sprite->addKeyframe(TYPE_2_FACEDOWN3, glm::vec2(35 * 2 / 483.f, 35 * 2 / 1787.f));

	sprite->setAnimationSpeed(TYPE_2_FACEDOWN4, 4);
	sprite->addKeyframe(TYPE_2_FACEDOWN4, glm::vec2(35 * 3 / 483.f, 35 * 2 / 1787.f));

	sprite->setAnimationSpeed(TYPE_3_FLY, 4);
	sprite->addKeyframe(TYPE_3_FLY, glm::vec2(35 * 0 / 483.f, 35 * 3 / 1787.f));

	sprite->setAnimationSpeed(TYPE_3_LAND, 4);
	sprite->addKeyframe(TYPE_3_LAND, glm::vec2(35 * 1 / 483.f, 35 * 3 / 1787.f));
	sprite->addKeyframe(TYPE_3_LAND, glm::vec2(35 * 2 / 483.f, 35 * 3 / 1787.f));

	sprite->setAnimationSpeed(TYPE_3_WALK, 4);
	sprite->addKeyframe(TYPE_3_WALK, glm::vec2(35 * 3 / 483.f, 35 * 3 / 1787.f));
	sprite->addKeyframe(TYPE_3_WALK, glm::vec2(35 * 4 / 483.f, 35 * 3 / 1787.f));
	sprite->addKeyframe(TYPE_3_WALK, glm::vec2(35 * 5 / 483.f, 35 * 3 / 1787.f));

	sprite->setAnimationSpeed(TYPE_4, 2);
	//sprite->addKeyframe(TYPE_4, glm::vec2(35 * 0 / 483.f, 35 * 4 / 1787.f));
	sprite->addKeyframe(TYPE_4, glm::vec2(35 * 1 / 483.f, 35 * 4 / 1787.f));
	sprite->addKeyframe(TYPE_4, glm::vec2(35 * 2 / 483.f, 35 * 4 / 1787.f));


 	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

	direction = false;
	landed = false;
	walking = false;

	life = vida;
	sprite->setLoopAnimations(true);
 	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	move();
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
	startY = posEnemy.y;
}

void Enemy::setPlayerPosition(const glm::vec2& pos)
{
	posPlayer = pos;
}

void Enemy::setType(int t)
{
	type = t;
	switch (t) {
	case 1:
		sprite->changeAnimation(TYPE_1);
		break;
	case 21:
		sprite->changeAnimation(TYPE_2_FACEUP4);
		break;
	case 22:
		sprite->changeAnimation(TYPE_2_FACEDOWN1);
		break;
	case 3:
		sprite->changeAnimation(TYPE_3_FLY);
		break;
	case 4:
		sprite->changeAnimation(TYPE_4);
		break;
	default:
		break;
	}
}

void Enemy::move()
{
	switch (type) {
	case 1:											//ocells
		posEnemy.x -= 0.5f;
		if (direction) {
			posEnemy.y -= 0.5f;
		}
		else {
			posEnemy.y += 0.5f;
		}
		if (posEnemy.y == (startY + 10) || posEnemy.y == (startY - 10)) {
			direction = !direction;
		}
		break;
	case 21:										//torreta faceup
		if (posPlayer.x >= (posEnemy.x - 30))				
			sprite->changeAnimation(TYPE_2_FACEUP1);
		else if (posPlayer.y < (160/3.f))					 
			sprite->changeAnimation(TYPE_2_FACEUP2);
		else if (posPlayer.y < (2*160/3))
			sprite->changeAnimation(TYPE_2_FACEUP3);
		else
			sprite->changeAnimation(TYPE_2_FACEUP4);
		break;
	case 22:										//torreta facedown
		if (posPlayer.x >= (posEnemy.x - 30))
			sprite->changeAnimation(TYPE_2_FACEDOWN4);
		else if (posPlayer.y < (160 / 3.f))
			sprite->changeAnimation(TYPE_2_FACEDOWN1);
		else if (posPlayer.y < (2 * 160 / 3))
			sprite->changeAnimation(TYPE_2_FACEDOWN2);
		else
			sprite->changeAnimation(TYPE_2_FACEDOWN3);
		break;
	case 3:											//rodo
		posEnemy.x -= 1;
		posEnemy.y += 0.8;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(6, 8)) == 1) {
			sprite->changeAnimation(TYPE_3_FLY);
			landed = false;
			walking = false;
			posEnemy.x += 1;
			posEnemy.y -= 2;
		}
		else if (map->collisionMoveDown(posEnemy, glm::ivec2(22, 25))==1) {
			if (!landed) {
				sprite->changeAnimation(TYPE_3_LAND);
				landed = true;
			}
			else if(!walking) {
				sprite->changeAnimation(TYPE_3_WALK);
				walking = true;
			}
			posEnemy.x += 0.2;
			posEnemy.y -= 0.8;
		}
		break;
	case 4:											//cap llarg
		posEnemy.x -= 0.8;
		if (posEnemy.y < (posPlayer.y - 5) || posEnemy.y > (posPlayer.y + 5)) {
			if (posPlayer.y > posEnemy.y) {
				posEnemy.y += 0.8;
			}
			else if (posPlayer.y < posEnemy.y) {
				posEnemy.y -= 0.8;
			}
		}
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(6, 6)) == 1) {
			posEnemy.x += 0.8;
		}

		if (map->collisionMoveUp(posEnemy, glm::ivec2(25, 7)) == 1) {
			posEnemy.y += 1;
		}
		else if (map->collisionMoveDown(posEnemy, glm::ivec2(25, 25)) == 1) {
			posEnemy.y -= 1;
		}
		sprite->changeAnimation(TYPE_4);
		break;
	default:
		break;
	}
}

void Enemy::recieveDamage()
{
	life--;
}

glm::vec2 Enemy::getPos()
{
	return posEnemy;
}
