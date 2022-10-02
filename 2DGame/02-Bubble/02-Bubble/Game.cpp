#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	State state= MENU;
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	switch (state) {
	case MENU:
		if (getSpecialKey(GLUT_KEY_INSERT)) state = GAME;
		break;

	case GAME:
		scene.render();
		break;

	case INFO:

		break;

	case CREDITS:

		break;

	default:
		break;

	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (state) {
		case MENU:

			break;

		case GAME:
			 scene.render();
			break;

		case INFO:

			break;

		case CREDITS:

			break;

		default :
			break;

	}



	
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
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





