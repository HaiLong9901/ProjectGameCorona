#ifndef TEST_H_
#define TEST_H_
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include <SDL_ttf.h>
#include "File.h"
using namespace std;
const int  SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int  SCREEN_BPP = 32;
const int NUM_THREATS = 12;
extern SDL_Surface* g_image;
extern SDL_Surface* g_screen;
extern SDL_Surface* g_menu;
extern SDL_Event g_even;
extern SDL_Surface* g_Character;
extern SDL_Surface* g_SelectChar;
extern SDL_Surface* g_Guide;
extern SDL_Surface* g_Score;
SDL_Surface* Load_image(string name);
void applySurface(SDL_Surface* a, SDL_Surface* b, int x, int y);
void Cleanup();
bool Check_Collision(const SDL_Rect& Object1, const SDL_Rect& Object2);
int ShowMenu(SDL_Surface* des, TTF_Font* font);
bool CheckFocusMouse(int x, int y, SDL_Rect rect);
SDL_Rect ApplySurface(SDL_Surface* a, SDL_Surface* b, int x, int y);
int ShowCharacter(SDL_Surface* des, TTF_Font* font);
int ShowGuide(SDL_Surface* des, TTF_Font* font);
int ShowHighestScore(SDL_Surface* des, TTF_Font* font, TTF_Font* font1);
#endif // !TEST_H_

