#ifndef THREATS_H_
#define THREATS_H_
#include "Test.h"
#include "Object.h"
#include<string.h>
#define THREAT_WIDTH 80
#define THREAT_HEIGHT 80

class Threats:public BaseObject {
private:
	int x_val_;
	int y_val_;
	char* name;
	int Bonus_point;
public:
	const char* Name;
	Threats();
	~Threats();
	void Move(const int& x_border, const int& y_border);
	void InputAction(SDL_Event even);
	void Set_X_val(int x) { x_val_ = x; }
	void Set_Y_val(int y) { y_val_ = y; }
	void Set_Bonus(int x);
	int Get_Bonus() { return Bonus_point; }
};
#endif // !THREATS_H_

