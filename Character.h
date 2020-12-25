#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Object.h"
#include "Test.h"
#define	CHARACTER_WIDTH 75
#define CHARACTER_HEIGHT 175

using namespace std;

class Main_character: public BaseObject {
private:
	int x_val;
	int y_val;
public:
	const char* name;
	const char* mask;
	Main_character();
	~Main_character();
	void InputAction(SDL_Event event);
	void Move();
};
#endif // !Character_h

