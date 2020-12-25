#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Test.h"
class BaseObject {
protected:
	SDL_Surface* p_object;
	SDL_Rect p_rect;
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool Loadimg(const char* file);
	void Set_rect(int x, int y) {
		p_rect.x = x;
		p_rect.y = y;
	}
	SDL_Rect Get_rect() {
		return p_rect;
	}
	SDL_Surface* Get_surface() { return p_object; }
	void Reset(const int& x);
};
#endif // !Object_h