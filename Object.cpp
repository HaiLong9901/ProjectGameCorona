#include "Object.h"
#include <iostream>
#include <string>
#include "Test.h"
BaseObject::BaseObject() {
	p_rect.x = 0;
	p_rect.y = 0;
	p_object = NULL;
}
BaseObject::~BaseObject() {
	//delete p_object;
	;
}
bool BaseObject::Loadimg(const char* file) {
	p_object = Load_image(file);
	if (p_object == NULL) return false;
	return true;
}
void BaseObject::Show(SDL_Surface* des) {
	if (p_object != NULL) {
		applySurface(p_object, des, p_rect.x, p_rect.y);
	}
}
void BaseObject::Reset(const int& x) {
	p_rect.y = x;
	if (p_rect.y > SCREEN_HEIGHT * 6 / 8 + 50) { // phần biến mất của threats
		p_rect.y = 0;
		int ran_x = rand() % 1000;
		if (ran_x > 1200) {//Tạo random vị trí
			ran_x = 100;
		}
		p_rect.x = ran_x;
	}
}