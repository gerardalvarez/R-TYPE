#pragma once
#ifndef _SHOOT_INCLUDE
#define _SHOOT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Shoot
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void calculateCollisions();
	float getPos();
	void setPosition(const glm::vec2& pos);
	void charge();
	void powerShoot();
	void enemyShoot();
	void setPlayerPos(glm::vec2& pos);
	void setEnemyPos(glm::vec2& pos);
	void calculateXDirecection();
	void calculateYDirecection();

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posShoot;
	glm::vec2 posPlayer;
	glm::vec2 posEnemy;
	glm::vec2 posObjective;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int xDirection;
	double yDirection;
};


#endif // _SHOOT_INCLUDE


