#include "Music.h"

ISoundEngine* engine = createIrrKlangDevice();

void Music::Musica()
{

}

void Music::efectoMenuDelante()
{
    engine->play2D("./sounds/palante.wav",false,false,true);
}

void Music::efectoMenuAtras()
{
    engine->play2D("./sounds/patras.wav", false, false, true);
}

void Music::musicaMenu()
{
    engine->play2D("./sounds/menu.wav", true, false, true);
}

void Music::musicaGame()
{
    engine->play2D("./sounds/gamemusic.wav", true, false, true);
}

void Music::explosion_player()
{
    engine->play2D("./sounds/explosion.wav", false, false, true);
}


void Music::stop()
{
    engine->stopAllSounds();
}

void Music::pause()
{
    engine->setAllSoundsPaused(true);
}