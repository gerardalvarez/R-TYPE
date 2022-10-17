#pragma once
#include "Menu.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


Menu::Menu() {}
Menu:: ~Menu() {}

void Menu::init(int level) {
	BaseScene::init();

	switch (level){
		case (0): //MENU
			spritesheet.loadFromFile("images/Menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case(1): //CREDITS
			spritesheet.loadFromFile("images/Menu_extra.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case(2): //CREDITS
			spritesheet.loadFromFile("images/Menu_extra.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		
	}
	//spritesheet.loadFromFile("images/Menu_extra.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(640,480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(glm::vec2(0.f, 0.f));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	loadSprites();

	this->option = level;

}

void Menu::loadSprites() {

	/*for (int i = 0; i <= 4; ++i) {
		options[i].spritesheet.loadFromFile("images/level_image" + to_string(i + 1) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
		options[i].sprite = Sprite::createSprite(glm::ivec2(194, 151), glm::vec2(1.f, 1.f), &options[i].spritesheet, &texProgram);
		options[i].sprite->setPosition(vec2(51.6 + (i * 245.6), 337));
	}

	options[5].spritesheet.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[5].sprite = Sprite::createSprite(glm::ivec2(270, 60), glm::vec2(1.f, 1.f), &options[5].spritesheet, &texProgram);
	options[5].sprite->setPosition(vec2(float(SCREEN_WIDTH - 525), float(SCREEN_HEIGHT - 60)));

	options[6].spritesheet.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	options[6].sprite = Sprite::createSprite(glm::ivec2(150, 60), glm::vec2(1.f, 1.f), &options[6].spritesheet, &texProgram);
	options[6].sprite->setPosition(vec2(float(SCREEN_WIDTH - 200), float(SCREEN_HEIGHT - 60)));*/
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	currentTurnTime += deltaTime;


	}


void Menu::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background->render();

}

