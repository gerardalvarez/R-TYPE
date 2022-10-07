#include <glm/glm.hpp>
#include "State.h"
#include "Sprite.h"


class Menu {
public:
    Menu();
    ~Menu();

    void init();
    void render(State::State_enum state);

private:
    void initShaders();
    Sprite* controls;
    Texture sceneMenu;

    
    
};
