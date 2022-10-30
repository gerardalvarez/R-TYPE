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
	void setPlayerPos(glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posShoot;
	glm::vec2 posPlayer;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _SHOOT_INCLUDE


