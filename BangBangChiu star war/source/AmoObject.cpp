#include"AmoObject.h"

AmoObject::AmoObject(){
	rect_.x = 0;
	rect_.y = 0;
	_xVal = 0;
	_yVal = 0;
	_amoType = NONE;
	_isMove = false;
}

AmoObject::~AmoObject() {}

void AmoObject::setIsMove(bool isMove) {
	_isMove = isMove;
}

bool AmoObject::getIsMove() const { return _isMove; }

void handleInput(SDL_Event events) {
	
}

void AmoObject::handleMoveRToL() {
	rect_.x -= _xVal;
	if (rect_.x < 0) _isMove = false;
}

void AmoObject::handleMove(const int& xBoder, const int& yBoder) {
	rect_.x += _xVal;
	if (rect_.x > xBoder) _isMove = false;
}

void AmoObject::setWidthHeight(const int& width, const int& height) { rect_.w = width; rect_.h = height; }

int AmoObject::getType() const { return _amoType; }

void AmoObject::setType(const int& type) { _amoType = type; }

void AmoObject::freeAmo(AmoObject* p) {
	delete p;
	p = NULL;
}