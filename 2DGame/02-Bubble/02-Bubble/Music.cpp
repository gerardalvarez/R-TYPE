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

void Music::disparo()
{
    engine->play2D("./sounds/disparo1.wav", false, false, true);
}

void Music::disparo_charge()
{
    engine->play2D("./sounds/carga.wav", false, false, true);
    
}

void Music::disparo2()
{
    engine->play2D("./sounds/disparo2.wav", false, false, true);

}

void Music::stop()
{
    engine->stopAllSounds();
}

void Music::gameover()
{
    engine->play2D("./sounds/gameover.wav", false, false, true);
}

void Music::ultimaex()
{
    engine->play2D("./sounds/ultimaexplosion.wav", false, false, true);
}

void Music::grito()
{ 
    engine->play2D("./sounds/grito.wav", false, false, true);
}

void Music::disparoboss()
{
    engine->play2D("./sounds/bosd.wav", false, false, true);
}

void Music::disparoboss2()
{
    engine->play2D("./sounds/ultimaexplosion.wav", false, false, true);
}

void Music::pause()
{
    engine->setAllSoundsPaused(true);
}