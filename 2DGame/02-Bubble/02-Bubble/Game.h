#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "MenuScene.h"
#include "MapScene.h"
#include "State.h"


//this are the original screen sizes of the game
#define SCREEN_WIDTH 256 
#define SCREEN_HEIGHT 192


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	State state;
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;							// Continue to play game?
	BaseScene* scene;						// Scene to render
    MapScene mapScene;					// Scene to render
	bool keys[256], specialKeys[256];	// Store key states so that 
	MenuScene Menuscene;

};


#endif // _GAME_INCLUDE


