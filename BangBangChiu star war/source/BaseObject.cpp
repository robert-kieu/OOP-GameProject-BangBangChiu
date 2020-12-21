//#include "Common_Function.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

BaseObject::~BaseObject()
{
	if (p_object_ != NULL)
	{
		SDL_FreeSurface(p_object_);
	}
}


bool BaseObject::loadImgObject(const char *file_name)
{
	p_object_ = SDLCommonFunc::loadImage(file_name);
	if (p_object_ == NULL)	return false;

	return true;
}


void BaseObject::showObject(SDL_Surface *des)
{
	if (p_object_ != NULL)
	{
		rect_ = SDLCommonFunc::applySurface(p_object_, des, rect_.x, rect_.y);
	}
}



void BaseObject::setWidthHeight(const int &width, const int &height)
{
	rect_.w = width;	rect_.h = height;
}