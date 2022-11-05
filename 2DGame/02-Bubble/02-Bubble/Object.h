#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Sprite.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Object
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


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 posObject;

	Texture spritesheet;
	Sprite* sprite;

	bool taken;
	bool inscreen;
};


#endif 


