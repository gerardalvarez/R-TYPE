//#include <iostream>
//#include <cmath>
//#include <glm/gtc/matrix_transform.hpp>
//#include "MapScene.h"
//#include "Game.h"
//
//
//#define SCREEN_X 32
//#define SCREEN_Y 16
//
//#define INIT_PLAYER_X_TILES 4
//#define INIT_PLAYER_Y_TILES 25
//
//
//MapScene::MapScene()
//{
//	map = NULL;
//	player = NULL;
//}
//
//MapScene::~MapScene()
//{
//	if (map != NULL)
//		delete map;
//	if (player != NULL)
//		delete player;
//	for (int i = 0; i < 3; i++)
//		if (texQuad[i] != NULL)
//			delete texQuad[i];
//}
//
//
//void MapScene::init()
//{
//	initShaders();
//	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //si es canvia la mida del mapa, es canvia aixo
//	player = new Player();
//	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
//	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
//	player->setTileMap(map);
//
//	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(CAMERA_WIDTH * 8, CAMERA_HEIGHT) };	//ALERTA!!! AIXO DIU QUE TANT GRAN SERA EL QUAD
//	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };					//COORDENADES DE LA TEXTURA
//
//	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);					//dins de la imatge, agafa un quadrat definit pels punts de texCoords
//	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);			//guarda el quadrat
//
//	texs[0].loadFromFile("images/level01.png", TEXTURE_PIXEL_FORMAT_RGB);			//carrega la imatge
//	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
//	currentTime = 0.0f;
//}
//
//void Scene::update(int deltaTime)
//{
//	currentTime += deltaTime;
//	player->update(deltaTime);
//}
//
//void Scene::render()
//{
//	glm::mat4 modelview;
//
//	texProgram.use();
//	texProgram.setUniformMatrix4f("projection", projection);
//	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
//	modelview = glm::mat4(1.0f);
//	texProgram.setUniformMatrix4f("modelview", modelview);
//	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
//	//map->render();
//	//for (int i = 0; i < CAMERA_WIDTH; i = i + 128) {
//	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
//	texProgram.setUniformMatrix4f("modelview", modelview);
//	texQuad[0]->render(texs[0]);
//	//}
//	player->render();
//}
//
//void Scene::initShaders()
//{
//	Shader vShader, fShader;
//
//	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
//	if (!vShader.isCompiled())
//	{
//		cout << "Vertex Shader Error" << endl;
//		cout << "" << vShader.log() << endl << endl;
//	}
//	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
//	if (!fShader.isCompiled())
//	{
//		cout << "Fragment Shader Error" << endl;
//		cout << "" << fShader.log() << endl << endl;
//	}
//	texProgram.init();
//	texProgram.addShader(vShader);
//	texProgram.addShader(fShader);
//	texProgram.link();
//	if (!texProgram.isLinked())
//	{
//		cout << "Shader Linking Error" << endl;
//		cout << "" << texProgram.log() << endl << endl;
//	}
//	texProgram.bindFragmentOutput("outColor");
//	vShader.free();
//	fShader.free();
//}
//
//
//
