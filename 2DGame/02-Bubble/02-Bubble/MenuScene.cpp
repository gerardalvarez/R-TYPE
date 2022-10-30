#pragma once
#include "MenuScene.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


MenuScene::MenuScene() {}
MenuScene:: ~MenuScene() {}

void MenuScene::init(int level) {
	BaseScene::init();

	switch (level) {
	case (0): //MENU
		spritesheet.loadFromFile("images/r-menu.png", TEXTURE_PIXEL_FORMAT_RGB);
		break;
	case(1): //CREDITS
		spritesheet.loadFromFile("images/r-creditos.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;
	case(2): //CREDITS
		spritesheet.loadFromFile("images/r-instr.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;

	}
	//spritesheet.loadFromFile("images/Menu_extra.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(glm::vec2(0.f, 0.f));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	if (!text.init("fonts/OpenSans-Regular.ttf") ){
		text.getSize();
	}

	loadSprites();


}

void MenuScene::loadSprites() {

	//SIQ QUEREMOS ANIMACIONES
}

void MenuScene::update(int deltaTime) {
	currentTime += deltaTime;
	currentTurnTime += deltaTime;


}


void MenuScene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	
	text.render("'Aaaaaaaaaaaaaaaaaa", glm::vec2(10, 10), 32, glm::vec4(1, 1, 1, 1));
	background->render();
}

