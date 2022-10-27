#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	bool getIsDead();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setGodMode(bool godModeActive);
	void calculateCollisions();
	void updatePositionX(int x);
	void updatePositionY(int y);
	void sendLeft(float left);
	
private:
	glm::ivec2 tileMapDispl;
    glm::vec2 posPlayer;
	int startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool isDead;
	bool godMode;
	float cameraleft;
};


#endif // _PLAYER_INCLUDE


