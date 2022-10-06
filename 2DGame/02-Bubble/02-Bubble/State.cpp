#include "State.h"

State::State() { state = State_enum::MENU; }
State::~State() {}

void State::init() { state = State_enum::MENU; }

void State::changeState() {
  
}

void State::goCREDITS() {
    state = State_enum::CREDITS;
}

void State::goMENU() {
    state = State_enum::MENU;
}

void State::goGAME() {
    state = State_enum::GAME;
}

void State::goINFO() {
    state = State_enum::INFO;
}

State::State_enum State::getState() { return state; }