#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"



#define TURN_TIME 200

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
	glm::mat4 projection;

	float currentTime;
	float currentTurnTime;

};