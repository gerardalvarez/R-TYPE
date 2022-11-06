#pragma once
#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the enemies. As such it has
// all properties it needs to track its movement and collisions.


class Boss
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getlife();
	void hitted(int damage);
	void setPosition(const glm::vec2& pos);
	bool isnormal();
	bool ispower();
	int dispara(int deltaTime);
	bool normal, power;


private:
	
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