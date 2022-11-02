#pragma once
#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the enemies. As such it has
// all properties it needs to track its movement and collisions.


class boss
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getlife();

	void hitted();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	bool invincible, defeated, phase1;
	glm::ivec2 tileMapDispl;
	glm::vec2 posEnemy;
	int startY;
	Texture spritesheet;
	Texture spritesheet2;
	Sprite* sprite;
	Sprite* sprite2;
	TileMap* map;
	int bossHealth, bossMaxHealth, cooldown;
};


#endif // _ENEMY_INCLUDE