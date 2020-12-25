#include "Character.h"
using namespace std;

Main_character::Main_character() {
	p_rect.x = 0;
	p_rect.y = 0;
	p_rect.w = CHARACTER_WIDTH;
	p_rect.h = CHARACTER_HEIGHT;
	//p_object = NULL;
	x_val = 0;
	y_val = 0;
}
Main_character::~Main_character() { ; }
void Main_character::Move() {
	p_rect.x += x_val;
	if (p_rect.x < 250 || p_rect.x + CHARACTER_WIDTH > SCREEN_WIDTH- 250) p_rect.x -= x_val;
	p_rect.y += y_val;
	if (p_rect.y < 0 || p_rect.y + CHARACTER_HEIGHT > SCREEN_HEIGHT) p_rect.y -= y_val;
}
void Main_character::InputAction(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			x_val += CHARACTER_WIDTH / 25;
			break;
		case SDLK_LEFT:
			x_val -= CHARACTER_WIDTH / 25;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			x_val -= CHARACTER_WIDTH / 25;
			break;
		case SDLK_LEFT:
			x_val += CHARACTER_WIDTH / 25;
			break;
		default:
			break;
		}
	}
}