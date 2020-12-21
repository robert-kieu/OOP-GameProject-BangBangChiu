#include "Background.h"
#include <iostream>
using namespace std;


int bkgn_x = 0;
bool is_run_screen = true;

bool BackgroundFunc:: prepareBackground(const int &level)
{
	bool isSuccess = true;
	
	switch (level)
	{
	case 1:
		g_bkground = SDLCommonFunc::loadImage("./image/bk1.png");		// level 1:
		break;
	case 2: 
		g_bkground = SDLCommonFunc::loadImage("./image/bk2.png");		// level 2:
		break;
	case 3:
		g_bkground = SDLCommonFunc::loadImage("./image/bk3.png");		// level 3:
		break;
	case 4:
		g_bkground = SDLCommonFunc::loadImage("./image/bk4.png");		// level 4:
		break;
	default:
		break;
	}
	
	if (g_bkground == NULL)
	{
		cerr << "ko load background dc" << endl;
		isSuccess = false;
	}
	SDLCommonFunc::applySurface(g_bkground, g_screen, 0, 0);

	return isSuccess;
}