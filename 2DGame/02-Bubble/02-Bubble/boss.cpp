#include "boss.h"


enum bossAnims
{
	NORMAL, HITTED
};

void boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	posEnemy.x = 192;
	posEnemy.y = 192;
	spritesheet.loadFromFile("images/boss-final2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(908,231), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(HITTED, 8);
	sprite->addKeyframe(HITTED, glm::vec2(468 / 908.f, 231 / 231.f));
	sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(12 / 908.f, 231 / 231.f));

	

	bossHealth = bossMaxHealth = 30;
	defeated = false;
	phase1 = false;
	tileMapDispl = tileMapPos;
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	normal = power = false;
}

void boss::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->update(deltaTime);
		sprite->changeAnimation(NORMAL);
	}

}

void boss::render()
{
	sprite->render();
	
}

int boss::getlife()
{
	return bossHealth;

}

void boss::hitted()
{
	//spritesheet.loadFromFile("images/boss3-hitt.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite->changeAnimation(HITTED);
	--bossHealth;
}

void boss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void boss::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int boss::dispara(int deltaTime) {
	if (deltaTime  == 0) return 0;
	else return 2;
	
}

bool boss::isnormal() {
	return normal;
}

bool boss::ispower() {
	return power;
}