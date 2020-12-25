#ifndef TEXTGAME_H_
#define TEXTGAME_H_
#include "Test.h"
#include "Object.h"
using namespace std;
class TextObject :public BaseObject {
	string str_val_;
	SDL_Color text_color;
public:
	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		BLUE_TEXT = 3,
		YELLOW_TEXT = 4,
		BLUEF_TEXT = 5,
	};
	TextObject();
	~TextObject();
	void Set_text(const string& text) { str_val_ = text; }
	void Set_Color(const int& typecolor);
	void Render_text(TTF_Font* Font, SDL_Surface* des);
};



#endif // !TEXTGAME_H_
