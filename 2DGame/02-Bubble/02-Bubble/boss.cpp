#include "Boss.h"


enum bossAnims
{
	NORMAL, HITTED
};

void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
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
	
	tileMapDispl = tileMapPos;
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	normal = power = false;
}

void Boss::update(int deltaTime)
{
	if (sprite != NULL) {
		sprite->update(deltaTime);
		sprite->changeAnimation(NORMAL);
	}
}

void Boss::render()
{
	sprite->render();
	
}

int Boss::getlife()
{
	return bossHealth;
}

void Boss::hitted()
{
	sprite->changeAnimation(HITTED);
	--bossHealth;
}

void Boss::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

int Boss::dispara(int deltaTime) {
	
	if (deltaTime  == 0) 
		return 0;
	
	return 2;
}

bool Boss::isnormal() {
	return normal;
}

bool Boss::ispower() {
	return power;
}