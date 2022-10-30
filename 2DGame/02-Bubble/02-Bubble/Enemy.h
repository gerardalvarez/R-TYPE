#pragma once
#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the enemies. As such it has
// all properties it needs to track its movement and collisions.


class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posEnemy;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _ENEMY_INCLUDE


