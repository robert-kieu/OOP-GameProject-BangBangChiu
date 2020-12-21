#pragma once

#include "CommonFunction.h"

#include <SDL_mixer.h>"


// bien Audio toan cuc:


//// Audio:
//extern Mix_Chunk* g_sound_bullet[2];	//am thanh cac loai dan: (2 loai)
//extern Mix_Chunk* g_sound_ex_boss = NULL;
//extern Mix_Chunk* g_sound_ex_main = NULL;
//extern Mix_Chunk* g_sound_injured = NULL;
//extern Mix_Chunk* g_sound_ready = NULL;

// Audio:
extern Mix_Chunk* g_sound_bullet[2];	//am thanh cac loai dan: (2 loai)
extern Mix_Chunk* g_sound_ex_boss;
extern Mix_Chunk* g_sound_ex_main;
extern Mix_Chunk* g_sound_injured;
extern Mix_Chunk* g_sound_ready;
extern Mix_Chunk* g_music;
// Audio Prototype:

namespace AudioFunction 
{
	void prepareAudioFile();

}