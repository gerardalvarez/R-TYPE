#ifndef _FORCE_INCLUDE
#define _FORCE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Force
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void calculateCollisions();
	void setTaken(bool b);
	void sendcamera(float left, float right);

	void rightCollisions();
	void leftCollisions();
	void upCollisions();
	void downCollisions();

	bool istaken();

	bool animationFinished();


	glm::vec2 getPos();


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posForce;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	float cameraleft;
	float cameraright;
	bool taken;
};


#endif 


