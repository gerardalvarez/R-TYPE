#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Estrellas.h"
#include "Game.h"
#include<windows.h>


enum EstrellasAnims
{
	NORMAL
};

//la nau fa 33px de x i 25px de y en la spritesheet, el quad sera de 33x 30y
void Estrellas::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/estrellas.png", TEXTURE_PIXEL_FORMAT_RGBA);


	sprite = Sprite::createSprite(glm::ivec2(1600,118), glm::vec2(1600 / 1600.f, 118 / 118.f), &spritesheet, &shaderProgram);


	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(0 / 1600.f, 0 / 118.f));

	sprite->changeAnimation(NORMAL);
	tileMapDispl = tileMapPos;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEstrellas.x), float(tileMapDispl.y + posEstrellas.y)));

}

void Estrellas::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEstrellas.x), float(tileMapDispl.y + posEstrellas.y)));
		sprite->update(deltaTime);
	}

}


glm::vec2 Estrellas::getPos()
{
	return posEstrellas;
}

void Estrellas::render()
{
	sprite->render();
}

void Estrellas::setinscreen(bool b)
{
	inscreen = b;
}

void Estrellas::setPosition(const glm::vec2& pos)
{
	posEstrellas = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEstrellas.x), float(tileMapDispl.y + posEstrellas.y)));
}
