#pragma once


#include <Windows.h>
#include <SDL.h>
#include <vector>
#include <string>
#include <SDL_image.h>
#include <ctime>
#include<iostream>

#undef main
using namespace std;

extern const int WIDTH_LONG_BACKGROUND;					// background lon
extern const int WIDTH_SHORT_BACKGROUND;				// background nho
extern const int HEIGHT_BACKGROUND;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int SCREEN_BPP;								// chi so bit per pixel
extern const int NUM_THREAT;
extern const int SPEED_BACKGROUND;


extern SDL_Surface* g_screen;					//quan ly man hinh
extern SDL_Surface* g_bkground;					//quan ly background
extern SDL_Event	g_event;

extern HWND hWnd;


namespace SDLCommonFunc
{
	SDL_Surface* loadImage(string file);
	SDL_Rect applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void applySurfaceClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void cleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}