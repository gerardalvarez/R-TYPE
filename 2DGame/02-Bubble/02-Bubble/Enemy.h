#pragma once
#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Shoot.h"
#include "Player.h"


// Enemy is basically a Sprite that represents the enemies. As such it has
// all properties it needs to track its movement and collisions.


class Enemy
{

public:
	void init(Texture &spritesheet, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int vida, int id);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setPlayerPosition(const glm::vec2& pos);
	void setType(int t);
	void move();
	glm::vec2 getPos();
	void setRight(int r);
	bool calculatePlayerCollisions();
	void setPlayerCollisionBox(int xmin, int xmax, int ymin, int ymax);
	void setEnemyCollisionBox();
	void setBox(int xmin, int xmax, int ymin, int ymax);
	int getxMinE();
	int getxMaxE();
	int getyMinE();
	int getyMaxE();
	int getId();
	void explode();
	bool actionFinished();
	bool getisDead();

private:
	ShaderProgram texProgram;
	glm::ivec2 tileMapDispl;
	glm::vec2 posEnemy;
	glm::vec2 posPlayer;
	Shoot* shoot;
	vector<Shoot*> shoots;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool landed, walking;
	int type;
	bool direction;
	int right;
	int xMin, xMax, yMin, yMax;
	int xMinE, xMaxE, yMinE, yMaxE;
	int Id;
	bool isExploded;
	bool isDead;
};


#endif // _ENEMY_INCLUDE


