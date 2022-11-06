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
	void normalShootForce(int type);
	void normalBossShoot(bool t);
	void powerShoot();
	void enemyShoot();
	void powerBossShoot();
	void charge();
	void clear();
	

private:
	//void initShaders();
	void doForce();
	void doGameOver();
	bool playerReachedForce();
	void updateEnemies(int deltaTime);
	void updateShoots(int deltaTime);
	void updateBossShoots(int deltaTime);
	void bossAI();
	void relocateShoots();
	void relocateEnemies();
	void relocateVisibleEnemies();
	void initEnemiesOnMap();
	void createEnemy(int type, glm::vec2 pos, int id, bool canShoot);
	void renderShoots();
	void renderEnemies();
	void renderBossShoots();
	void checkVisibles();
	void calculateShootCollisions();
	void calculateBossShootCollisions();
	bool isVisible();
	void eliminateFromVisible(int id);
	void calculatePlayerHitBox();
	void eliminateChargeShoot();

private:
	TileMap* map;
	Player* player;
	Enemy* enemy;
	Boss* boss;
	Force* force;
	Shoot* shoot;
	Shoot* shoot2;
	Object* object;
	vector<Shoot*> shoots;

	vector<Enemy*> enemies;
	vector<Enemy*> visibleEnemies;

	BossShoot* bshoot;
	vector<BossShoot*> bshoots;
	vector<glm::vec2> plastpos;

	Texture texs[1];
	TexturedQuad* texQuad[3];
	float left;
	float right;
	bool godModeActive;
	Text text;
	bool gameover;
	Texture enemySpritesheet;
	int counter;
	int num;
	int xMin, xMax, yMin, yMax;
	int forceCounter;
};