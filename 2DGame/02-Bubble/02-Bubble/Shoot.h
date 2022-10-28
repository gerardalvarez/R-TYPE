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

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posShoot;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _SHOOT_INCLUDE


