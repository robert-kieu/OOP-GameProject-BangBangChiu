#include "Audio.h"

// Audio:
Mix_Chunk* g_sound_bullet[2];	//am thanh cac loai dan: (2 loai)
Mix_Chunk* g_sound_ex_boss = NULL;
Mix_Chunk* g_sound_ex_main = NULL;
Mix_Chunk* g_sound_injured = NULL;
Mix_Chunk* g_sound_ready = NULL;
Mix_Chunk* g_music = NULL;

void AudioFunction::prepareAudioFile()
{
	//if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)	//return false;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return;


	//Read file wav audio:
	g_sound_bullet[0] = Mix_LoadWAV("./audio/bullet.wav");
	g_sound_bullet[1] = Mix_LoadWAV("./audio/rocket.wav");
	g_sound_injured = Mix_LoadWAV("./audio/small_explo.wav");

	g_sound_ex_boss = Mix_LoadWAV("./audio/boss_died.wav");
	g_sound_ex_main = Mix_LoadWAV("./audio/main_died.wav");
	g_sound_ready = Mix_LoadWAV("./audio/ready.wav");
	g_music = Mix_LoadWAV("./audio/soundtrack_menu.wav");
	if (g_music == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_injured == NULL || g_sound_ex_boss == NULL || g_sound_ex_main == NULL)
	{
		//return false;
		return;
	}

	
	
	
}

