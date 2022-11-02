#pragma once
#ifndef _bossbossShoot_INCLUDE
#define _bossShoot_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class bossShoot
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
	void powerbossShoot();
	void setPlayerPos(glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posbossShoot;
	glm::vec2 posPlayer;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _bossShoot_INCLUDE


