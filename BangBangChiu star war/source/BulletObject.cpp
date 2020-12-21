#include "BulletObject.h"

BulletObject::BulletObject() {
	y_val_ = 0;
	x_val_ = 5;																// Tốc độ di chuyển theo chiều ngang mặc định là 5
	rect_.x = rect_.y = 0;
	is_move_ = true;
	type_ = BULLET;
}

BulletObject::~BulletObject() {
	// Do something here
}

void BulletObject::handleMove(const int& x_border, const int& y_border) {
	if (is_move_) {
		if (rect_.x > x_border + WIDTH_BULLET)
			is_move_ = false;
		rect_.x += x_val_;
	}
}

void BulletObject::handleInputAction(SDL_Event events) {
	// Do something here
}

void BulletObject::handleMoveRightToLeft() {
	if (is_move_) {
		if (rect_.x < -WIDTH_BULLET)
			is_move_ = false;
		rect_.x -= x_val_;
	}
}

int BulletObject::type() {
	return BULLET;
}

AmoObject* BulletObject::create() {
	AmoObject* newBullet = new BulletObject();
	bool ret = newBullet->loadImgObject("bullet.png");
	if (!ret) exit(EXIT_FAILURE);
	newBullet->setIsMove(true);
	newBullet->setWidthHeight(WIDTH_BULLET, HEIGHT_BULLET);
	newBullet->setType(BULLET);
	return newBullet;
}

void BulletObject::move(const int& x_limit, const int& y_limit) {
	this->showObject(g_screen);
	this->handleMove(x_limit, y_limit);
}

void BulletObject::moveRightToLeft(const int& x_limit, const int& y_limit) {
	this->showObject(g_screen);
	this->handleMoveRightToLeft();
}