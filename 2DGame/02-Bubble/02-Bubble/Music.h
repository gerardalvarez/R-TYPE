#pragma once
#include <string>
#include <../../../libs/irrKlang/include/irrKlang.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
//#pragma comment(lib, "../../../libs/irrklang/lib/irrklang.lib")

using namespace irrklang;


class Music
{
public:
	static Music& instance()
	{
		static Music music;

		return music;
	}

	void Musica();
    void efectoMenuDelante();
    void efectoMenuAtras();
	void musicaMenu();
	void musicaGame();
	void explosion_player();
	void disparo();
	void disparo_charge();
	void disparo2();
	void win();
	void bm();
	void stop();
	void force();
	void gameover();
	void ultimaex();
	void grito();
	void disparoboss();
	void disparoboss2();
	void pause();
	bool muted;

private:
};
