#pragma once

#include "CommonFunction.h"
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>


extern int bkgn_x;
extern bool is_run_screen;


namespace BackgroundFunc 
{
	bool prepareBackground(const int &level);


}