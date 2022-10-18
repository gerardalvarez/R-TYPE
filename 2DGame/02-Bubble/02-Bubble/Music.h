#pragma once
#include <string>
#include <../../../libs/irrKlang/include/irrKlang.h>
#include <GL/glew.h>
#include <GL/glut.h>
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
	void stop();
	bool muted;

private:
};
