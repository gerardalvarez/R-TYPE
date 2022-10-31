#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Music.h"
#include "MapScene.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	state.goMENU();
	Menuscene.init(0);

	Music::instance().musicaMenu();

	timer = 0;
	charging = false;


}

bool Game::update(int deltaTime)
{
	if(state.getState() == State::State_enum::MENU)
		return bPlay;

	mapScene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (state.getState()) {
	case State::State_enum::MENU:
		
		Menuscene.render();
		break;

	case State::State_enum::GAME:
		mapScene.render();
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
        if (key == 32) {
			mapScene.init();
			Music::instance().stop();
            state.goGAME();
			Music::instance().musicaGame();
			
			
        }
		if (key == 99) state.goCREDITS();
		if (key == 105) state.goINFO();
        if (key == 105 || key == 99 || key == 32) Music::instance().efectoMenuDelante();
		if (key == 27) { // Escape code
			bPlay = false;
			return;
        }
		break;

	case State::State_enum::GAME:
        if (key == 27) {
			Music::instance().stop();
            state.goMENU();
			Music::instance().musicaMenu();
			Menuscene.init(0);
           Music::instance().efectoMenuAtras();
		   
        }
		if (key == 49) {		//tecla 1
			mapScene.skip(1);
		}
		if (key == 50) {		//tecla 2
			mapScene.skip(2);
		}
		if (key == 51) {		//tecla 3
			mapScene.skip(3);
		}
		if (key == 52) {		//tecla 4
			mapScene.skip(4);
		}
		if (key == 53) {		//tecla 5
			mapScene.skip(5);
		}
		if (key == 103) {		//tecla g
			mapScene.godMode();
		}
		if (key == 122) {		//tecla z
			if (timer >= 2) {
				if (!charging) {
					mapScene.charge();
				}
				charging = true;
			}
			timer += 2;
		}
		break;

	case State::State_enum::CREDITS:
        if (key == 27) {
            state.goMENU();
			Menuscene.init(0);
            Music::instance().efectoMenuAtras();
        }
		break;

	case State::State_enum::INFO:
        if (key == 27) {
            state.goMENU();
			Menuscene.init(0);
           Music::instance().efectoMenuAtras();
        }
		break;

	default:
		break;

	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	switch (state.getState()) {
	case State::State_enum::GAME:
		if (key == 122) {		//tecla z
			if (!charging) {
				mapScene.normalShoot();
				timer = 0;
				Music::instance().disparo();
			}
			else {
				mapScene.powerShoot();
 				charging = false;
				timer = 0;
				
			}
		}
		break;
	default:
		break;

	}
	keys[key] = true;
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







