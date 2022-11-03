#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "MapScene.h"
#include "Game.h"
#include "Music.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 2
#define INIT_PLAYER_Y_TILES 0

#define INIT_ENEMY_X_TILES 50
#define INIT_ENEMY_Y_TILES 10



MapScene::MapScene()
{
	map = NULL;
	player = new Player();
	enemy = new Enemy();
}

MapScene::MapScene(int lvl)
{
	map = NULL;
	player = new Player();
	enemy = new Enemy();
	shoot = new Shoot();
	initlevel(lvl);

}

MapScene::~MapScene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
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

	//SHOOT
	shoot = NULL;

	//ENEMIES
	enemySpritesheet.loadFromFile("images/Enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	initEnemiesOnMap();
	shooting = false;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(3072, 192) };						//ALERTA!!! AIXO DIU QUE TANT GRAN SERA EL QUAD
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };					//COORDENADES DE LA TEXTURA
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(3072.f / 3072.f, 1.f);
	// fer divisions de 2^x, no decimals
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);				//guarda el quadrat

	string lvl = "images/level0" + to_string(level) + ".png";

	texs[0].loadFromFile(lvl, TEXTURE_PIXEL_FORMAT_RGBA);									//les imatges son profunditat 32bits
	projection = glm::ortho(left, right, float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	spritesheet.loadFromFile("images/3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);

	gameover = false;
}

void MapScene::update(int deltaTime)
{
	currentTime += deltaTime;

	if (player->getIsDead()) {
		
		if (player->getlives() <= 1) {

			gameover = true;
			background->render();

			//pantalla game over
			Game::instance().state.goMENU();
			Music::instance().stop();
			Music::instance().musicaMenu();
		}
		else {
			if (player->animationFinished()) {
				Music::instance().explosion_player();
				player->revive();
				
			}
		}
		
	}
	player->sendcamera(left, right);
	if (player != NULL) player->update(deltaTime);
	
	//initEnemiesOnMap();

	if (!enemies.empty()) {
		for (int i = 0; i < enemies.size(); i++) {
			enemy = enemies[i];
			if (enemy != NULL) {
				enemy->setRight(right);
				enemy->setPlayerPosition(player->getPos());
				enemy->update(deltaTime);
			}
		}
	}
	

	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->setPlayerPos(player->getPos());
				shoot->update(deltaTime);
				if (shoot->getPos() > right || shoot->getPos() < (left-20)) {
					shoots[i] = NULL;
				}
			}
		}
	}
	relocateShoots();
	if (!player->getIsDead() && right <= 3070) {

		left += 0.4;
		right += 0.4;
	}
	projection = glm::ortho(left, right, float(SCREEN_HEIGHT - 1), 0.f);
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
	
	map->render();
	
	player->render();


	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->render();
			}
		}
	}

	for (int i = 0; i <= enemies.size(); i++) {

	}

	if (!enemies.empty()) {
		for (int i = 0; i < enemies.size(); i++) {
			enemy = enemies[i];
			if (enemy != NULL) {
				enemy->render();
				glm::vec2 posEnemy = enemy->getPos();
				if (!shooting && posEnemy.x < (right - 30)) {
					shooting = true;
					enemyShoot();
				}
			}
		}
	}
	//text.render("Videogames!!!", glm::vec2(10,20), 32, glm::vec4(1, 1, 1, 1));
}

void MapScene::normalShoot() {
	shoot = new Shoot();
	glm::vec2 posPlayer = player->getPos();
	shoot->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posPlayer);
	shoot->setPosition(glm::vec2((posPlayer.x + 18), (posPlayer.y + 2)));
	shoot->setTileMap(map);
	shoots.push_back(shoot);
}

void MapScene::powerShoot()
{
	shoots[shoots.size() - 1] = NULL;
	normalShoot();
	shoot->powerShoot();
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
}

void MapScene::createEnemy(int type, glm::vec2 pos)
{
	enemy = new Enemy();
	int mapSize = map->getTileSize();
	enemy->init(enemySpritesheet, glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	enemy->setPosition(glm::vec2(pos.x * mapSize, pos.y * mapSize));
	enemy->setTileMap(map);
	enemy->setType(type);
	enemies.push_back(enemy);
}

void MapScene::enemyShoot()
{
	shooting = true;
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
	//primera orde
	createEnemy(1, glm::vec2(83, 14));
	createEnemy(1, glm::vec2(89, 10));
	createEnemy(1, glm::vec2(92, 15));
	createEnemy(1, glm::vec2(99, 11));
	
	//segona orde
	createEnemy(1, glm::vec2(104, 31));
	createEnemy(1, glm::vec2(107, 34));
	createEnemy(1, glm::vec2(112, 34));
	createEnemy(1, glm::vec2(117, 31));
	
	//tercera orde
	createEnemy(1, glm::vec2(126, 20));
	createEnemy(1, glm::vec2(131, 21));
	createEnemy(1, glm::vec2(136, 17));
	createEnemy(1, glm::vec2(141, 23));
	createEnemy(1, glm::vec2(144, 19));
	
	//quarta orde
	createEnemy(1, glm::vec2(159, 20));
	createEnemy(1, glm::vec2(162, 15));
	createEnemy(1, glm::vec2(166, 14));
	createEnemy(1, glm::vec2(171, 15));
	
	//cinquena orde
	createEnemy(1, glm::vec2(168, 4));
	createEnemy(1, glm::vec2(172, 6));
	createEnemy(1, glm::vec2(176, 4));
	createEnemy(1, glm::vec2(180, 6));
	createEnemy(1, glm::vec2(184, 4));
	//sisena orde
	createEnemy(1, glm::vec2(168, 25));
	createEnemy(1, glm::vec2(172, 29));
	createEnemy(1, glm::vec2(177, 29));

	//primera orde torreta terra
	createEnemy(21, glm::vec2(174, 40));
	
	//primer rodo
	createEnemy(3, glm::vec2(180, 20));
	
	//setena orde
	createEnemy(1, glm::vec2(189, 17));
	createEnemy(1, glm::vec2(193, 14));
	createEnemy(1, glm::vec2(195, 17));
	createEnemy(1, glm::vec2(196, 34));
	createEnemy(1, glm::vec2(204, 34));
	
	//vuitena orde
	createEnemy(1, glm::vec2(226, 19));
	createEnemy(1, glm::vec2(232, 24));

	//segona orde torreta terra
	createEnemy(21, glm::vec2(238, 40));
	createEnemy(21, glm::vec2(266, 40));
	
	//primera orde cap llarg
	createEnemy(4, glm::vec2(257, 13));
	createEnemy(4, glm::vec2(270, 24));
	createEnemy(4, glm::vec2(285, 22));
	createEnemy(4, glm::vec2(299, 24));
	createEnemy(4, glm::vec2(306, 17));
	createEnemy(4, glm::vec2(315, 8));
	createEnemy(4, glm::vec2(307, 39));
	createEnemy(4, glm::vec2(311, 33));
	createEnemy(4, glm::vec2(322, 39));
	createEnemy(4, glm::vec2(327, 19));
	
	//novena orde
	createEnemy(1, glm::vec2(332, 32));
	createEnemy(1, glm::vec2(338, 30));

	//tercera orde torreta terra
	createEnemy(21, glm::vec2(334, 36));				
	createEnemy(21, glm::vec2(337, 36));
	createEnemy(21, glm::vec2(340, 36));
	createEnemy(21, glm::vec2(345, 32));
	createEnemy(21, glm::vec2(348, 32));
	createEnemy(21, glm::vec2(351, 32));

	//primera orde torreta sostre
	createEnemy(22, glm::vec2(334, 5));
	createEnemy(22, glm::vec2(337, 5));
	createEnemy(22, glm::vec2(340, 5));
	createEnemy(22, glm::vec2(345, 10));
	createEnemy(22, glm::vec2(348, 10));
	createEnemy(22, glm::vec2(351, 10));

	//desena orde
	createEnemy(1, glm::vec2(370, 11));
	createEnemy(1, glm::vec2(374, 11));
	createEnemy(1, glm::vec2(378, 14));

	//segona orde rodo
	createEnemy(3, glm::vec2(376, 24));
	createEnemy(3, glm::vec2(398, 33));

	//onzena orde
	createEnemy(1, glm::vec2(384, 39));
	createEnemy(1, glm::vec2(390, 38));
}

float MapScene::getLeft()
{
	return left;
}
