#pragma once

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "CommonFunction.h"

#include "ExplosionObject.h"
#include "ThreatsObject.h"
#include "Audio.h"
#include"HPObject.h"
#include"Gift.h"
#include"Random.h"
#include"TextObject.h"
#include"Menu.h"
#include"Score.h"
#include "SaveLoad.h"
#include"Background.h"


extern int level;
extern bool is_quit;
extern bool resume;
extern bool newGame;
static Score score;

namespace ControlFunc
{
	bool Init();
	void setup(const int& lv);
	bool prepareGame();
	int playCampaign();
	
	void endGame();
}