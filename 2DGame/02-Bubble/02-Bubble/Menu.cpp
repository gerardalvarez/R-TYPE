#include "Menu.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Menu::Menu() {}

Menu::~Menu() { //delete background;
}

void Menu::init() {



}

void Menu::render(State::State_enum state) {
    
    switch (state) {
    case State::State_enum::MENU:
        background->render(tex[0], modelview);
        break;
    case State::State_enum::CREDITS:
        background->render(tex[2], modelview);
        break;
    case State::State_enum::INFO:
        background->render(tex[1], modelview);
        break;
    

    
}

void Menu::initShaders() {

}