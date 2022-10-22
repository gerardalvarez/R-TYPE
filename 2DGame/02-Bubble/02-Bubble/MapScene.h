#pragma once
#include "BaseScene.h"

#include "TileMap.h"
#include "Player.h"
#include "TexturedQuad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class MapScene : public BaseScene
{

public:
	MapScene();
	MapScene(int lvl);
	~MapScene();

	void init();
	void initlevel(int level);
	void update(int deltaTime);
	void render();

private:
	//void initShaders();

private:
	TileMap* map;
	Player* player;
	Texture texs[1];
	TexturedQuad* texQuad[3];
	float left;
	float right;
};