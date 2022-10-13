#pragma once
#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class BaseScene
{

public:

	void virtual init();
	void virtual update(int deltaTime);
	void virtual render();


protected:
	void initShaders();

protected:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};

#endif // _SCENE_INCLUDE