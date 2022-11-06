#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "MapScene.h"
#include "Game.h"
#include "Music.h"
#include <time.h>
#include <stdlib.h> 

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 2
#define INIT_PLAYER_Y_TILES 0

#define INIT_ENEMY_X_TILES 50
#define INIT_ENEMY_Y_TILES 10


enum FAnims
{
	F, T, G
};


MapScene::MapScene()
{
	map = NULL;
	player = new Player();
	enemy = new Enemy();
	
}

MapScene::~MapScene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (bshoot != NULL)
		delete bshoot;
	for (int i = 0; i < 3; i++)
		if (texQuad[i] != NULL)
			delete texQuad[i];
}


void MapScene::init()
{
	BaseScene::init();
	left = 0;
	right = SCREEN_WIDTH - 1;
	initlevel(1);


}

void MapScene::skip(int part)
{
	switch (part) {
	case 1:
		left = 0;
		break;
	case 2:
		left = 3072 / 4;
		break;
	case 3:
		left = 3072 / 2;
		break;
	case 4:
		left = 3072 / 4 * 3;
		break;
	default:
		left = 3072 - SCREEN_WIDTH;
		break;
	}
	right = left + SCREEN_WIDTH - 1;
	player->setPosition(glm::vec2(left, (192 / 2)));

}

void MapScene::godMode()
{
	godModeActive = !godModeActive;
	player->setGodMode(godModeActive);
}

void MapScene::initlevel(int level)
{
	left = 0;
	right = (SCREEN_WIDTH - 1);
	godModeActive = false;

	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //si es canvia la mida del mapa, es canvia aixo

	//PLAYER
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize() + 70));
	player->setTileMap(map);

	//force
	force = new Force();
	force->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	force->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize() + 70));


	//object
	object = new Object();
	object->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	object->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize()+208, INIT_PLAYER_Y_TILES * map->getTileSize() + 70));

	//SHOOT
	shoot = NULL;

	//ENEMIES
	enemySpritesheet.loadFromFile("images/Enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	initEnemiesOnMap();
  
	//BOSSSHOOT
	bshoot = NULL;

	//BOSS
	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize()+2770, INIT_ENEMY_Y_TILES * map->getTileSize()-48));

	//BACKGROUND QUAD CREATION
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(3072, 192) };						//ALERTA!!! AIXO DIU QUE TANT GRAN SERA EL QUAD
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };					//COORDENADES DE LA TEXTURA
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(3072.f / 3072.f, 1.f);
	// fer divisions de 2^x, no decimals
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);				//guarda el quadrat

	string lvl = "images/level0" + to_string(level) + ".png";

	texs[0].loadFromFile(lvl, TEXTURE_PIXEL_FORMAT_RGBA);									//les imatges son profunditat 32bits
	projection = glm::ortho(left, right, float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	//GAMEOVER BACKGORUNDS
	spritesheet.loadFromFile("images/312.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(750, 192), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setNumberAnimations(3);

		background->setAnimationSpeed(F, 32);
		background->addKeyframe(F, glm::vec2(478*0 / 1436.f, 304 / 304.f));

		background->setAnimationSpeed(T, 32);
		background->addKeyframe(T, glm::vec2(478 *1 / 1436.f, 304 / 304.f));

		background->setAnimationSpeed(G, 32);
		background->addKeyframe(G, glm::vec2(478 *2 / 1436.f, 304 / 304.f));

	//variables
	gameover = false;
	counter = 0;
	num = 1;
}

void MapScene::update(int deltaTime)
{
	currentTime += deltaTime;

	//PLAYER IS DEAD
	if (player->getIsDead()) {
		
		if ((player->getlives() <= 1 )) {
			doGameOver();
		}
		else {
			if (player->animationFinished()) {
				Music::instance().explosion_player();
				player->revive();
			}
			else {
				player->update(deltaTime);
			}
		}
	}
	//PLAYER IS ALIVE
	else if (gameover) {
		++counter;

		if (counter == 1) {
			Music::instance().ultimaex();
			for (int i = 0; i < bshoots.size(); i++) bshoots[i] = NULL;
		}
		else if (counter == 2) {
			Music::instance().stop();
		}
		else if (counter == 5) {
			Game::instance().state.goCREDITS();	//canviar per pantalla de win + score
			Music::instance().win();
		}
	}
	else if (player != NULL) {
		player->sendcamera(left, right);
		if (playerReachedForce()) 
		{
			force->setinscreen(true);
			object = NULL;
			force->setPosition(glm::vec2(left-20, 30));
			Music::instance().force();
		}

		player->update(deltaTime);
	
		if (force->inScreen()) {
			doForce();
		}
		force->update(deltaTime);

		updateEnemies(deltaTime);

		//BOSS
		if (int(right) >= 3030) {
			boss->update(deltaTime);
			//AI BOSS
			bossAI();
			updateBossShoots(deltaTime);
		}
		
		
		if (object != NULL) object->update(deltaTime);

		updateShoots(deltaTime);


		if (int(right) == 3030) {
			Music::instance().stop();
			Music::instance().bm();
		}

		if (!player->getIsDead() && int(right) <= 3070) {

			left += 0.4;
			right += 0.4;
		}
		projection = glm::ortho(left, right, float(SCREEN_HEIGHT - 1), 0.f);
	}
}

void MapScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	//map->render();
	
	renderBossShoots();
	renderEnemies();
	
	boss->render();
	renderShoots();


	if (force->inScreen()) force->render();
	
	if (object != NULL) object->render();
	
	player->render();
	
	if (gameover) {
		background->render();
	}
	//text.render("Videogames!!!", glm::vec2(10,20), 32, glm::vec4(1, 1, 1, 1));
}

void MapScene::normalShoot()
{
	shoot = new Shoot();

	glm::vec2 posPlayer = player->getPos();
	shoot->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posPlayer);
	shoot->setPosition(glm::vec2((posPlayer.x + 18), (posPlayer.y + 2)));
	shoot->setTileMap(map);
	shoots.push_back(shoot);
}


void MapScene::normalBossShoot(bool t) 
{
	bshoot = new BossShoot();

	glm::vec2 posBoss = glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize() + 2760, INIT_ENEMY_Y_TILES * map->getTileSize() - 48);
	bshoot->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posBoss);

	//decideix des don surten els trets
	if (!t) {
		bshoot->setPosition(glm::vec2((posBoss.x - 7), (posBoss.y + 55)));
	}
	else {
		bshoot->setPosition(glm::vec2((posBoss.x + 33), (posBoss.y + 125)));
	}
	bshoot->setPlayerPos(player->getPos());
	bshoot->normalBossShoot();
	bshoots.push_back(bshoot);
	Music::instance().disparoboss();
}

void MapScene::powerShoot()
{
	eliminateChargeShoot();
	relocateShoots();
	normalShoot();
	shoot->powerShoot();
	if (force->istaken()) shoot2->powerShoot();

}

void MapScene::powerBossShoot()
{
	normalBossShoot(true);
	bshoot->powerbossShoot();

}

void MapScene::charge() {
	normalShoot();
	shoot->charge();
}

void MapScene::relocateShoots()
{
	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot == NULL) {
				shoots.erase(shoots.begin() + i);
			}
		}
	}

	if (!bshoots.empty()) {
		for (int i = 0; i < bshoots.size(); i++) {
			bshoot = bshoots[i];
			if (bshoot == NULL) {
				bshoots.erase(bshoots.begin() + i);
				
			}
		}
	}
}

void MapScene::relocateEnemies()
{
	if (!enemies.empty()) {
		for (int i = 0; i < enemies.size(); i++) {
			enemy = enemies[i];
			if (enemy == NULL) {
				enemies.erase(enemies.begin() + i);
			}
		}
	}
}

void MapScene::relocateVisibleEnemies()
{
	if (!visibleEnemies.empty()) {
		for (int i = 0; i < visibleEnemies.size(); i++) {
			enemy = visibleEnemies[i];
			if (enemy == NULL) {
				visibleEnemies.erase(visibleEnemies.begin() + i);
			}
		}
	}
}

void MapScene::createEnemy(int type, glm::vec2 pos, int id, bool canShoot)
{
	enemy = new Enemy();
	int mapSize = map->getTileSize();
	enemy->init(enemySpritesheet, glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1, id, canShoot);
	enemy->setPosition(glm::vec2(pos.x * mapSize, pos.y * mapSize));
	enemy->setTileMap(map);
	enemy->setType(type);
	enemies.push_back(enemy);
}

void MapScene::renderShoots()
{
	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->render();
			}
		}
	}
}

void MapScene::renderEnemies()
{
	if (!enemies.empty()) {
		for (int i = 0; i < enemies.size(); i++) {
			enemy = enemies[i];
			if (enemy != NULL) {
				enemy->render();
			}
		}
	}

}

void MapScene::renderBossShoots()
{
	if (!bshoots.empty()) {
		for (int i = 0; i < bshoots.size(); i++) {
			bshoot = bshoots[i];
			if (bshoot != NULL) {
				bshoot->render();
			}
		}
	}
}

void MapScene::checkVisibles()
{
	for (int i = 0; i < visibleEnemies.size(); i++) {
		enemy = visibleEnemies[i];
		if (left > enemy->getPos().x) {
			enemies[i] = NULL;
		}
	}
}

void MapScene::calculateShootCollisions()
{
	if (!shoots.empty()){

		int xmin = shoot->getxMin();
		int xmax = shoot->getxMax();
		int ymin = shoot->getyMin();
		int ymax = shoot->getyMax();
		//CALCULATE IF ENEMIES SHOOTS HIT FORCE
		if (force->inScreen() && force->calculateCollisions(xmin, xmax, ymin, ymax)) {
			shoot->disapear();
		}
		//CALCULATE IF ENEMIES SHOOTS HIT THE PLAYER
		else if (shoot->calculatePlayerCollisions(xMin, xMax, yMin, yMax)) {
				player->setBoom();
				shoot->disapear();
		}
		//CALCULATE IF PLAYER SHOOTS HIT ENEMIES
		for (int i = 0; i < visibleEnemies.size(); i++) {
			enemy = visibleEnemies[i];
			int xmin = enemy->getxMinE();
			int xmax = enemy->getxMaxE();
			int ymin = enemy->getyMinE();
			int ymax = enemy->getyMaxE();
			if (shoot->calculateEnemyCollisions(xmin, xmax, ymin, ymax)) {
				enemy->explode();
				if (shoot->getDamage() == 1) {
					shoot->disapear();
				}
			}
		}
	}
}

void MapScene::calculateBossShootCollisions()
{
	if (!bshoots.empty()) {

		int xmin = player->getxMin();
		int xmax = player->getxMax();
		int ymin = player->getyMin();
		int ymax = player->getyMax();
		if (bshoot->calculatePlayerCollisions(xmin, xmax, ymin, ymax)) {
			player->setBoom();
			bshoot->disapear();
		}
		
	}
}

bool MapScene::isVisible()
{
	Enemy* enemy2 = new Enemy();
	for (int i = 0; i < visibleEnemies.size(); i++) {
		enemy2 = visibleEnemies[i];
		if (enemy->getId() == enemy2->getId()) {
			return true;
		}
	}
	return false;
}

void MapScene::eliminateFromVisible(int id)
{
	for (int i = 0; i < visibleEnemies.size(); i++) {
		Enemy* e = visibleEnemies[i];
		if (id == e->getId()) {
			visibleEnemies[i] = NULL;
		}
	}
	relocateVisibleEnemies();
}

void MapScene::calculatePlayerHitBox()
{
	xMin = player->getxMin();
	xMax = player->getxMax();
	yMin = player->getyMin();
	yMax = player->getyMax();
}

void MapScene::eliminateChargeShoot()
{
	for (int i = 0; i < shoots.size(); i++)
	{
		Shoot* s = shoots[i];
		if (s != NULL) {
			if (s->isCharge()) {
				shoots[i] = NULL;
			}
		}
	}
}

void MapScene::enemyShoot()
{
	shoot = new Shoot();
	glm::vec2 posEnemy = enemy->getPos();
	shoot->init(glm::ivec2(0, 0), texProgram, posEnemy);
	shoot->setPosition(glm::vec2((posEnemy.x), (posEnemy.y + 2)));
	shoot->setTileMap(map);
	shoot->setPlayerPos(player->getPos());
	shoot->setEnemyPos(posEnemy);
	shoot->enemyShoot();
	shoots.push_back(shoot);
}


void MapScene::clear()
{
	if (!enemies.empty())
		enemies.clear();

	if (!shoots.empty())
		shoots.clear();
}

void MapScene::initEnemiesOnMap()
{
	//1a orde
	createEnemy(1, glm::vec2(83, 14), 1, false);
	createEnemy(1, glm::vec2(86, 10), 2, true);
	createEnemy(1, glm::vec2(89, 15), 3, false);
	createEnemy(1, glm::vec2(92, 11), 4, false);
	
	//2a orde
	createEnemy(1, glm::vec2(104, 31), 5, false);
	createEnemy(1, glm::vec2(107, 34), 6, false);
	createEnemy(1, glm::vec2(110, 34), 7, true);
	createEnemy(1, glm::vec2(113, 31), 8, false);
	
	//3a orde
	createEnemy(1, glm::vec2(126, 20), 9, false);
	createEnemy(1, glm::vec2(129, 21), 10, false);
	createEnemy(1, glm::vec2(132, 17), 11, false);
	createEnemy(1, glm::vec2(135, 23), 12, false);
	createEnemy(1, glm::vec2(139, 19), 13, false);
	
	//4ta orde
	createEnemy(1, glm::vec2(159, 20), 14, false);
	createEnemy(1, glm::vec2(162, 15), 15, true);
	createEnemy(1, glm::vec2(165, 14), 16, false);
	createEnemy(1, glm::vec2(168, 15), 17, true);
	
	//5a orde
	createEnemy(1, glm::vec2(169, 4), 18, false);
	createEnemy(1, glm::vec2(172, 6), 19, true);
	createEnemy(1, glm::vec2(175, 4), 20, false);
	createEnemy(1, glm::vec2(178, 6), 21, false);
	createEnemy(1, glm::vec2(181, 4), 22, false);

	//6a orde
	createEnemy(1, glm::vec2(170, 25), 23, false);
	createEnemy(1, glm::vec2(173, 29), 24, false);
	createEnemy(1, glm::vec2(176, 29), 25, true);

	//1a orde torreta terra
	createEnemy(21, glm::vec2(174, 40), 26, true);
	
	//1a rodo
	createEnemy(3, glm::vec2(180, 20), 27, false);
	
	//7a orde
	createEnemy(1, glm::vec2(189, 17), 28, false);
	createEnemy(1, glm::vec2(192, 14), 29, false);
	createEnemy(1, glm::vec2(195, 17), 30, false);
	createEnemy(1, glm::vec2(198, 34), 31, false);
	createEnemy(1, glm::vec2(201, 34), 32, false);
	
	//8a orde
	createEnemy(1, glm::vec2(226, 19), 33, false);
	createEnemy(1, glm::vec2(229, 24), 34, false);

	//2a orde torreta terra
	createEnemy(21, glm::vec2(238, 40) ,35, true);
	createEnemy(21, glm::vec2(266, 40), 36, true);
	
	//1a orde cap llarg
	createEnemy(4, glm::vec2(270, 13), 37, false);
	createEnemy(4, glm::vec2(284, 24), 38, false);
	createEnemy(4, glm::vec2(288, 22), 39, false);
	createEnemy(4, glm::vec2(305, 24), 40, true);
	createEnemy(4, glm::vec2(310, 17), 41, false);
	createEnemy(4, glm::vec2(320, 8),  42, false);
	createEnemy(4, glm::vec2(310, 39), 43, false);
	createEnemy(4, glm::vec2(319, 33), 44, false);
	createEnemy(4, glm::vec2(325, 39), 45, true);
	createEnemy(4, glm::vec2(327, 19), 46, true);
	
	//9a orde
	createEnemy(1, glm::vec2(332, 32), 47, false);
	createEnemy(1, glm::vec2(335, 30), 48, true);

	//3a orde torreta terra
	createEnemy(21, glm::vec2(334, 36), 49, true);				
	createEnemy(21, glm::vec2(337, 36), 50, true);
	createEnemy(21, glm::vec2(340, 36), 51, true);
	createEnemy(21, glm::vec2(345, 32), 52, true);
	createEnemy(21, glm::vec2(348, 32), 53, true);
	createEnemy(21, glm::vec2(351, 32), 54, true);

	//1a orde torreta sostre
	createEnemy(22, glm::vec2(334, 5), 55, true);
	createEnemy(22, glm::vec2(337, 5), 56, true);
	createEnemy(22, glm::vec2(340, 5), 57, true);
	createEnemy(22, glm::vec2(345, 10), 58, true);
	createEnemy(22, glm::vec2(348, 10), 59, true);
	createEnemy(22, glm::vec2(351, 10), 60, true);

	//10a orde
	createEnemy(1, glm::vec2(370, 11), 61, false);
	createEnemy(1, glm::vec2(373, 11), 62, false);
	createEnemy(1, glm::vec2(376, 14), 63, true);

	//2a orde rodo
	createEnemy(3, glm::vec2(376, 24), 64, false);
	createEnemy(3, glm::vec2(398, 33), 65, false);

	//11a orde
	createEnemy(1, glm::vec2(384, 39), 66, false);
	createEnemy(1, glm::vec2(390, 38), 67, false);

	//3a orde torreta terra
	createEnemy(21, glm::vec2(404, 35), 68, true);
	createEnemy(21, glm::vec2(419, 40), 69, true);
	createEnemy(21, glm::vec2(422, 40), 70, true);
	createEnemy(21, glm::vec2(437, 35), 71, true);

	//2a orde torreta sostre
	createEnemy(22, glm::vec2(395, 2), 72, true);
	createEnemy(22, glm::vec2(398, 2), 73, true);
	createEnemy(22, glm::vec2(404, 7), 74, true);
	createEnemy(22, glm::vec2(419, 2), 75, true);
	createEnemy(22, glm::vec2(422, 2), 76, true);
	createEnemy(22, glm::vec2(437, 7), 77, true);

	//12a orde
	createEnemy(1, glm::vec2(430, 36), 78, false);
	createEnemy(1, glm::vec2(433, 35), 79, false);
	createEnemy(1, glm::vec2(436, 16), 80, false);
	createEnemy(1, glm::vec2(439, 15), 81, false);

	//13a orde
	createEnemy(1, glm::vec2(455, 35), 82, false);
	createEnemy(1, glm::vec2(458, 34), 83, true);
	createEnemy(1, glm::vec2(461, 17), 84, true);
	createEnemy(1, glm::vec2(464, 16), 85, false);
	createEnemy(1, glm::vec2(473, 17), 86, false);
	createEnemy(1, glm::vec2(475, 16), 87, false);

	//14a orde
	createEnemy(1, glm::vec2(480, 34), 88, false);
	createEnemy(1, glm::vec2(483, 32), 89, true);

	//3a orde torreta sostre
	createEnemy(22, glm::vec2(467, 5), 90, true);
	createEnemy(22, glm::vec2(470, 5), 91, true);
	createEnemy(22, glm::vec2(525, 9), 92, true);
	createEnemy(22, glm::vec2(528, 9), 93, true);
	createEnemy(22, glm::vec2(531, 9), 94, true);
	
	//15a orde
	createEnemy(1, glm::vec2(495, 9), 95, false);
	createEnemy(1, glm::vec2(498, 8), 96, false);
	createEnemy(1, glm::vec2(501, 12), 97, false);

	//3a orde rodo
	createEnemy(3, glm::vec2(525, 20), 98, false);

	//4a orde torreta terra
	createEnemy(21, glm::vec2(516, 36), 99, true);
	createEnemy(21, glm::vec2(519, 36), 100, true);

	//2a orde cap llarg
	createEnemy(4, glm::vec2(539, 31), 101, true);
	createEnemy(4, glm::vec2(545, 22), 102, false);
	createEnemy(4, glm::vec2(566, 26), 103, false);
	createEnemy(4, glm::vec2(582, 25), 104, true);
	createEnemy(4, glm::vec2(590, 26), 105, false);
	createEnemy(4, glm::vec2(590, 11), 106, false);
	createEnemy(4, glm::vec2(590, 32), 107, true);
	createEnemy(4, glm::vec2(605, 14), 108, true);
	createEnemy(4, glm::vec2(605, 34), 109, false);
	createEnemy(4, glm::vec2(608, 24), 110, false);
	
	//4a orde torreta sostre
	createEnemy(22, glm::vec2(609, 5), 111, true);
	createEnemy(22, glm::vec2(612, 5), 112, true);
	createEnemy(22, glm::vec2(615, 5), 113, true);

	//5a orde torreta terra
	createEnemy(21, glm::vec2(609, 36), 114, true);
	createEnemy(21, glm::vec2(612, 36), 115, true);
	createEnemy(21, glm::vec2(615, 36), 116, true);
	
	//16a orde
	createEnemy(1, glm::vec2(632, 17), 117, false);
	createEnemy(1, glm::vec2(635, 13), 118, false);
	createEnemy(1, glm::vec2(647, 12), 119, true);
	createEnemy(1, glm::vec2(639, 35), 120, false);
	createEnemy(1, glm::vec2(645, 38), 121, false);
	createEnemy(1, glm::vec2(648, 34), 122, true);

	//4a orde rodo
	createEnemy(3, glm::vec2(662, 31), 123, false);

	//16a orde
	createEnemy(1, glm::vec2(676, 19), 124, false);
	createEnemy(1, glm::vec2(681, 21), 125, true);

	//5a orde torreta sostre
	createEnemy(22, glm::vec2(672, 5), 126, true);
	createEnemy(22, glm::vec2(675, 5), 127, true);

	//6a orde torreta terra
	createEnemy(21, glm::vec2(672, 36), 128, true);
	createEnemy(21, glm::vec2(675, 36), 129, true);
}

void MapScene::doForce()
{
	int xmin = player->getxMin();
	int xmax = player->getxMax();
	int ymin = player->getyMin();
	int ymax = player->getyMax();
	if (force->calculateCollisions(xmin, xmax, ymin, ymax)) {
		force->setTaken(true);
	}
		
	if (force->istaken()) {
		force->setPosition(glm::vec2(player->getPos().x + 24, player->getPos().y + 11));
	}
	else {
		switch (num) {
		case 1:
			force->setPosition(glm::vec2(force->getPos().x + 1, force->getPos().y));
			if (force->getPos().x > right - 50) num = rand() % 4 + 1;
			break;
		case 2:
			force->setPosition(glm::vec2(force->getPos().x - 0.8, force->getPos().y));
			if (force->getPos().x < left + 50) num = rand() % 4 + 1;
			break;
		case 3:
			force->setPosition(glm::vec2(force->getPos().x, force->getPos().y - 0.8));
			if (force->getPos().y < 30) num = rand() % 4 + 1;
			break;
		case 4:
			force->setPosition(glm::vec2(force->getPos().x, force->getPos().y + 2));
			if (force->getPos().y > 160) num = rand() % 4 + 1;
			break;
		}
	}
}

void MapScene::doGameOver()
{
	gameover = true;
	++counter;
	background->setPosition(glm::vec2(left, 0));

	if (counter < 150) {
		if (counter == 5) {
			Music::instance().stop();
			Music::instance().ultimaex();
		}
		background->changeAnimation(F);
	}
	else if (counter < 250) {
		background->changeAnimation(T);
		if (counter == 151) Music::instance().gameover();
	}
	else if (counter < 350) background->changeAnimation(G);
	else {

		Music::instance().stop();
		Music::instance().musicaGame();
		this->init();
	}
}

bool MapScene::playerReachedForce()
{
	return (object != NULL && (player->getPos().y - 10 < object->getPos().y 
		&& player->getPos().y + 20 > object->getPos().y)
		&& (player->getPos().x  < object->getPos().x
		&& player->getPos().x + 30 > object->getPos().x));
}

void MapScene::updateEnemies(int deltaTime)
{
	if (!enemies.empty()) {
		for (int i = 0; i < enemies.size(); i++) {
			enemy = enemies[i];
			if (enemy != NULL) {
				if ((right - 5) >= enemy->getPos().x) {
					if (!enemy->getisDead()) {
						if (!isVisible()) {
							visibleEnemies.push_back(enemy);
						}
						else {
							enemy->setRight(right);
							enemy->setPlayerCollisionBox(player->getxMin(), player->getxMax(), player->getyMin(), player->getyMax());
							enemy->setPlayerPosition(player->getPos());

							enemy->update(deltaTime);

							if (enemy->getPos().x < (right - 10)) {
								if (force->inScreen()) {
									int xmin = enemy->getxMinE();
									int xmax = enemy->getxMaxE();
									int ymin = enemy->getyMinE();
									int ymax = enemy->getyMaxE();
									if (force->calculateCollisions(xmin, xmax, ymin, ymax)) {
										enemy->explode();
									}
								}
								if (enemy->calculatePlayerCollisions() && !player->getExplode()) {
									player->setBoom();
								}
							}

							enemies[i] = enemy;

							if (enemy->getPos().x < (left - 20)) {
								enemies[i] = NULL;
							}
							
							if (enemy->getCanShoot() && !enemy->getisShooting()) {
								enemyShoot();
								enemy->setisShooting(true);
							}

						}
						
					}
					else {
						eliminateFromVisible(enemy->getId());
						enemies[i] = NULL;
					}
				}
			}
		}
	}

	relocateEnemies();
	relocateVisibleEnemies();
}

void MapScene::updateShoots(int deltaTime)
{
	if (!shoots.empty()) {
		calculatePlayerHitBox();
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->setPlayerPos(player->getPos());
				shoot->update(deltaTime);
				
				//calcula colisions amb els enemics
				calculateShootCollisions();

				if (int(right) >= 3030 && int(shoot->getPos()) >= 2975) {
					if (!shoot->getBossHitted()) {
						shoot->hitBoss();
						if (boss->getlife() == 14 || boss->getlife() == 15) {
							Music::instance().grito();
						}	
						boss->hitted(shoot->getDamage());
					}
				}

				if (shoot->getPos() > right || shoot->getPos() < (left - 20)) {
					shoots[i] = NULL;
				}

				if (shoot->getGone()) {
					shoot = NULL;
				}
			}
		}
	}
	relocateShoots();
}

void MapScene::updateBossShoots(int deltaTime)
{
	if (!bshoots.empty()) {
		for (int i = 0; i < bshoots.size(); i++) {
			bshoot = bshoots[i];
			if (bshoot != NULL) {
				bshoot->setBossPos(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize() + 2760, INIT_ENEMY_Y_TILES * map->getTileSize() - 98));
				bshoot->setPlayerPos(player->getPos());
				bshoot->update(deltaTime);

				calculateBossShootCollisions();

				if (bshoot->getPosx() < left) {
					bshoots[i] = NULL;
				}

				if (bshoot->getGone()) {
					bshoot = NULL;
				}
			}
		}
	}
}

void MapScene::bossAI()
{
	//BOSS IS DEAD
	if (boss->getlife() <= 0) {
		gameover = true;
	}
	//BOSS IS ALIVE
	else if (!right <= 3070 && !gameover) { 
	
		//shooting frequency
		if (int(currentTime) % 200 == 10) {
			boss->power = true;
		}
		if (int(currentTime) % 40 == 10) {
			boss->normal = true;
		}


		if (right >= 3070) {
			if (boss->ispower()) {
				powerBossShoot();
				boss->power = false;
			}
			if (boss->isnormal()) {
				normalBossShoot(false);
				boss->normal = false;
			}

		}
	}
}

float MapScene::getLeft()
{
	return left;
}


void MapScene::putforce() {
	force->setinscreen(!force->inScreen());
	force->setTaken(!force->istaken());
}