#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#include <iostream>

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	state.goMENU();

}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (state.getState()) {
	case State::State_enum::MENU:
		Menuscene.init(0);
		Menuscene.render();
		break;

	case State::State_enum::GAME:
		scene.render();
		break;

	case State::State_enum::CREDITS:
		Menuscene.init(1);
		Menuscene.render();
		break;

	case State::State_enum::INFO:
		Menuscene.init(2);
		Menuscene.render();
		break;

	default:
		break;

	}




}

void Game::keyPressed(int key)
{
	


	switch (state.getState()) {

	case State::State_enum::MENU:
		if (key == 32) state.goGAME();
		if (key == 99) state.goCREDITS();
		if (key == 105) state.goINFO();
		if (key == 27) { // Escape code
			bPlay = false;
			return;
		}
		break;

	case State::State_enum::GAME:
		if (key == 27) state.goMENU();
		break;

	case State::State_enum::CREDITS:
		if (key == 27) state.goMENU();
		break;

	case State::State_enum::INFO:
		if (key == 27) state.goMENU();
		break;

	default:
		break;

	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}







