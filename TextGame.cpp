#include "TextGame.h"

TextObject::TextObject() {
	p_rect.x = 50;
	p_rect.y = 50;
}
TextObject::~TextObject() { ; }
void TextObject::Set_Color(const int& typecolor) {
	if (typecolor == RED_TEXT) {
		SDL_Color color = {255, 0, 0};
		text_color = color;
	}
	else if (typecolor == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
	else if (typecolor == BLACK_TEXT) {
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
	else if (typecolor == BLUE_TEXT) {
		SDL_Color color = { 25, 0 ,255 };
		text_color = color;
	}
	else if (typecolor == YELLOW_TEXT) {
		SDL_Color color = { 255, 251, 0};
		text_color = color;
	}
	else if (typecolor == BLUEF_TEXT) {
		SDL_Color color = { 0, 102, 205 };
		text_color = color;
	}
	else {
		SDL_Color color = { 0, 255, 0 };
		text_color = color;
	}
}
void TextObject::Render_text(TTF_Font* Font, SDL_Surface* des) {
	p_object = TTF_RenderText_Solid(Font, str_val_.c_str(), text_color);//tạo đối tượn surface
	Show(des);
}