#pragma once
#ifndef _bossbossShoot_INCLUDE
#define _bossShoot_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class BossShoot
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos);
	void update(int deltaTime);
	void render();

	float getPosx();
	
	void setPosition(const glm::vec2& pos);
	
	void powerbossShoot();
	void normalBossShoot();
	void setBossPos(glm::vec2& pos);
	void setPlayerPos(glm::vec2& pos);

	void setCollisionBox(int xmin, int xmax, int ymin, int ymax);
	void calculateXDirecection();
	void calculateYDirecection();
	void calculateTrajectory();

	bool calculatePlayerCollisions(int xmin, int xmax, int ymin, int ymax);
	void disapear();

	bool getGone();

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posbossShoot;
	glm::vec2 posBoss;
	glm::vec2 playerPos;
	glm::vec2 lppos;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	int xMin, xMax, yMin, yMax;
	int xDirection;
	double yDirection;
	glm::vec2 posObjective;

	bool gone;
};


#endif // _bossShoot_INCLUDE


