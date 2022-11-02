#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "MapScene.h"
#include "Game.h"
#include "Music.h"
#include <time.h>

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
	bshoot = new bossShoot();

	initlevel(lvl);

}

MapScene::~MapScene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (enemy != NULL)
		delete enemy;
	if (shoot != NULL)
		delete shoot;
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

	//SHOOT
	shoot = NULL;

	//BOSSSHOOT
	bshoot = NULL;
	

	//ENEMY
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);

	//BOSS
	bosss = new boss();
	bosss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	bosss->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize()+2770, INIT_ENEMY_Y_TILES * map->getTileSize()-48));
	bosss->setTileMap(map);

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

	if (player->getIsDead() || bosss->getlife() <= 0) {
		
		if (player->getlives() <= 1 || bosss->getlife()<=0) {

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
	enemy->update(deltaTime);
	bosss->update(deltaTime);

	//ia boss
	if (int(currentTime ) % 200 == 10) bosss->power = true;
	if (int(currentTime) % 30 == 10) bosss->normal = true;
	if (right >= 3070) {
		if (bosss->ispower()) {
			powerBossShoot();
			bosss->power = false;
		}
		if (bosss->isnormal()) {
			normalBossShoot(false);
			bosss->normal = false;
		}

	}



	

	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->setPlayerPos(player->getPos());
				shoot->update(deltaTime);
				if (shoot->getPos() > right) {
					shoots[i] = NULL;
				}
			}
		}
	}

	if (!bshoots.empty()) {
		for (int i = 0; i < bshoots.size(); i++) {
			bshoot = bshoots[i];
			if (bshoot != NULL) {
				bshoot->setPlayerPos(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize() + 2760, INIT_ENEMY_Y_TILES * map->getTileSize() - 98));
				bshoot->setNavePos(player->getPos());
				bshoot->update(deltaTime);
				if (bshoot->getPos() < left) {
					bshoots[i] = NULL;
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
	//map->render();
	
	player->render();
	bosss->render();
	if (!shoots.empty()) {
		for (int i = 0; i < shoots.size(); i++) {
			shoot = shoots[i];
			if (shoot != NULL) {
				shoot->render();
			}
		}
	}

	if (!bshoots.empty()) {
		for (int i = 0; i < bshoots.size(); i++) {
			bshoot = bshoots[i];
			if (bshoot != NULL) {
				bshoot->render();
			}
		}
	}
	
	//enemy->render();
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

void MapScene::normalBossShoot(bool t) {
	bshoot = new bossShoot();

	glm::vec2 posBoss = glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize() + 2760, INIT_ENEMY_Y_TILES * map->getTileSize() - 48);
	bshoot->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posBoss);
	if (!t) bshoot->setPosition(glm::vec2((posBoss.x - 7), (posBoss.y + 55)));
	else bshoot->setPosition(glm::vec2((posBoss.x + 33), (posBoss.y + 125)));
	bshoot->setTileMap(map);
	bshoot->setNaveLastPos(player->getPos());
	bshoots.push_back(bshoot);
}

void MapScene::powerShoot()
{
	shoots[shoots.size() - 1] = NULL;
	normalShoot();
	shoot->powerShoot();

	
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
				bosss->hitted();
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

float MapScene::getLeft()
{
	return left;
}
