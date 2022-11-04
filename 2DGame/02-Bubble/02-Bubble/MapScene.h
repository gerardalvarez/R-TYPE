#pragma once
#include "BaseScene.h"

#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "boss.h"
#include "TexturedQuad.h"

#include "Text.h"
#include "Force.h"
#include "Object.h"

#include "Shoot.h"
#include "bossShoot.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class MapScene : public BaseScene
{

public:
	MapScene();
	MapScene(int lvl);
	~MapScene();

	void init();
	void skip(int part);
	void initlevel(int level);
	void update(int deltaTime);
	void render();
	void godMode();
	float getLeft();
	void putforce();
	void normalShoot();
	void normalShootForce();
	void normalBossShoot(bool t);
	void powerShoot();
	void powerBossShoot();
	void charge();
	void relocateShoots();

private:
	//void initShaders();

private:
	TileMap* map;
	Player* player;
	Enemy* enemy;
	boss* bosss;
	Force* force;
	Shoot* shoot;
	Shoot* shoot2;
	Object* object;
	vector<Shoot*> shoots;
	bossShoot* bshoot;
	vector<bossShoot*> bshoots;
	vector<glm::vec2> plastpos;
	Texture texs[1];
	TexturedQuad* texQuad[3];
	float left;
	float right;
	bool godModeActive;
	Text text;
	bool gameover;
	int counter;
	int num;
};