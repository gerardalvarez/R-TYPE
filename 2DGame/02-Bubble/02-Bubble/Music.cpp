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

void Music::stop()
{
    engine->stopAllSounds();
}