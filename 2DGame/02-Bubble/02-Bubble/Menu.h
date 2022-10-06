#include <glm/glm.hpp>
#include "State.h"


class Menu {
public:
    Menu();
    ~Menu();

    void init();
    void render(State::State_enum state);

private:
    void initShaders();

private:
    
};
