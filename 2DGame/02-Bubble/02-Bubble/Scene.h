#pragma once
#include "BaseScene.h"

#include "TileMap.h"
#include "Player.h"
#include "TexturedQuad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Scene : public BaseScene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	//void initShaders();

private:
	TileMap* map;
	Player* player;
	Texture texs[1];
	TexturedQuad* texQuad[3];
};

