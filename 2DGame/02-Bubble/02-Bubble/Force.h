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

	void setPosition(const glm::vec2& pos);
	void setTaken(bool b);
	void setinscreen(bool b);
	bool inScreen();
	bool istaken();
	glm::vec2 getPos();
	bool calculateCollisions(int xmin, int xmax, int ymin, int ymax);
	void setCollisionBox(int xmin, int xmax, int ymin, int ymax);

	void upgrade();


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posForce;
	Texture spritesheet;
	Sprite* sprite;
	bool taken;
	bool inscreen;

	int xMin, xMax, yMin, yMax;
};


#endif 


