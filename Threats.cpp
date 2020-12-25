#include "Threats.h"

Threats::Threats() {
	p_rect.x = SCREEN_WIDTH / 3;
	p_rect.y = 0;
	p_rect.w = THREAT_WIDTH;
	p_rect.h = THREAT_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
	Bonus_point = 0;
}
Threats::~Threats() {
	;
}
void Threats::Move(const int& x_border, const int& y_border) {
	p_rect.y += y_val_;
	if (p_rect.y > SCREEN_HEIGHT * 6/8 + 50 ) { // phần biến mất của threats
		p_rect.y = 0;
		int ran_x = (rand() % 10 + 1)*100;
		if (ran_x > 1200) {//Tạo random vị trí
			ran_x = 100;
		}
		p_rect.x = ran_x;
	}
}
void Threats::InputAction(SDL_Event even) {

}
/*const char* RandomThreats(int x) {
	switch (x)
	{
	case(1): 
		return "Ap.png";
	case(2): case(3):
		return "A.png";
	case(4): case(5): case(6): 
		return "B.png";
	case(7): case(8): case(9): case(10): 
		return "C.png";
	case(11): case(12): case(13): case(14): case(15): 
		return "D.png";
	case(16): case(17): case(18): case(19): case(20): case(21): case(22): 
		return "virus.png";
	default:
		return "bg2.png";
		break;
	}
}*/
void Threats::Set_Bonus(int x) {
	Bonus_point = x;
}