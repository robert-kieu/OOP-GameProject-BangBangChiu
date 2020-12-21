#include "ExplosionObject.h"


const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

const int BIG_EXP_WIDTH = 159;
const int BIG_EXP_HEIGHT = 208;

const int SMALL_EXP_WIDTH = 99;
const int SMALL_EXP_HEIGHT = 99;

const int UPGRADE_WIDTH = 150;
const int UPGRADE_HEIGHT = 125;



ExplosionObject exp_subboss;
ExplosionObject explo_main;



ExplosionObject::ExplosionObject()
{


}

ExplosionObject::~ExplosionObject()
{
	frame_ = 0;
	
}


void ExplosionObject::set_clip()
{
	for (int i = 0; i < 4; i++)
	{
		clipBig_[i].x = i * BIG_EXP_WIDTH;
		clipBig_[i].y = 0;
		clipBig_[i].w = BIG_EXP_WIDTH;
		clipBig_[i].h = BIG_EXP_HEIGHT;
	}

}


void ExplosionObject::showEx(SDL_Surface *des)
{
	if (frame_ >= 4)
	{
		frame_ = 0;
	}
	 
	SDLCommonFunc::applySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y); 
}



void ExplosionObject::set_clip_big()
{
	for (int i = 0; i < 8; i++)
	{
		clipBig_[i].x = i * BIG_EXP_WIDTH;
		clipBig_[i].y = 0;
		clipBig_[i].w = BIG_EXP_WIDTH;
		clipBig_[i].h = BIG_EXP_HEIGHT;
	}

}


void ExplosionObject::showExBig(SDL_Surface *des)
{
	if (frame_ >= 8)
	{
		frame_ = 0;
	}

	SDLCommonFunc::applySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}


void ExplosionObject::set_clip_small()
{
	for (int i = 0; i < 4; i++)
	{
		clip_[i].x = i * SMALL_EXP_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = SMALL_EXP_WIDTH;
		clip_[i].h = SMALL_EXP_HEIGHT;
	}
}

void ExplosionObject::set_clip_eat_item()
{
	for (int i = 0; i < 4; i++)
	{
		clip_[i].x = i * EAT_EXP_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = EAT_EXP_WIDTH;
		clip_[i].h = EAT_EXP_HEIGHT;
	}
}


void ExplosionObject::showExSmall(SDL_Surface *des)
{
	if (frame_ >= 4)
	{
		frame_ = 0;
	}

	SDLCommonFunc::applySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}


void ExplosionObject::set_clip_upgrade()
{
	for (int i = 0; i < 4; i++)
	{
		clip_[i].x = i * UPGRADE_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = UPGRADE_WIDTH;
		clip_[i].h = UPGRADE_HEIGHT;
	}


}


void ExplosionObject::showUpgrade(SDL_Surface* des)
{
	if (frame_ >= 4)
	{
		frame_ = 0;
	}

	SDLCommonFunc::applySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}



//----------------------------------------------------------------------//
bool ExplosionFunc::prepareExpSub()
{
	bool ret;
	ret = exp_subboss.loadImgObject("./image/expo_small.png");
	exp_subboss.set_clip_small();
	return ret;
}


bool ExplosionFunc::prepareExpMain()
{
	bool ret;
	ret = explo_main.loadImgObject("./image/expo_small.png");
	explo_main.set_clip_small();
	return ret;
}





