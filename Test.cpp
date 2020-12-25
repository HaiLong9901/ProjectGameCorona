#include "Test.h"
#include "TextGame.h"
SDL_Surface* g_image = NULL;
SDL_Surface* g_screen = NULL;
SDL_Surface* g_Character = NULL;
SDL_Surface* g_menu = NULL;
SDL_Surface* g_SelectChar = NULL;
SDL_Surface* g_Guide = NULL;
SDL_Surface* g_Score = NULL;
SDL_Event g_even;
SDL_Surface* Load_image(string name) {//Hàm load ảnh
    SDL_Surface* loadimage = NULL;
    SDL_Surface* op_loadimage = NULL;
    loadimage = IMG_Load(name.c_str());
    if (loadimage != NULL) {
        op_loadimage = SDL_DisplayFormat(loadimage);
        SDL_FreeSurface(loadimage);
        if (op_loadimage != NULL) {//xóa phông nhân vật
            UINT32 color_key = SDL_MapRGB(op_loadimage->format, 0, 0xFF, 0xFF);
            SDL_SetColorKey(op_loadimage, SDL_SRCCOLORKEY, color_key);
        }
    }
    return op_loadimage;
}
void applySurface(SDL_Surface* a, SDL_Surface* b, int x, int y) {//Mở ảnh trên windows
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(a, NULL, b, &offset);
    //return offset;
}
SDL_Rect ApplySurface(SDL_Surface* a, SDL_Surface* b, int x, int y){///********
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(a, NULL, b, &offset);
    return offset;
}
void Cleanup() {
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_image);
}
bool Check_Collision(const SDL_Rect& Object1, const SDL_Rect& Object2) {//kiểm tra va chạm
    int left_a = Object1.x-20;
    int right_a = Object1.x + Object1.w-20;
    int bottom_a = Object1.y + Object1.h-20;
    int top_a = Object1.y-20;
    int left_b = Object2.x;
    int right_b = Object2.x + Object2.w;
    int bottom_b = Object2.y + Object2.h;
    int top_b = Object2.y;
    
    if (left_a<left_b && right_a>left_b && right_a < right_b) {
        if (bottom_a >= top_b) return true;
    }
    if (left_a > left_b && left_a < right_b && right_a>right_b) {
        if(bottom_a >= top_b) return true;
    }
    if (left_a > left_b && left_a<right_b && right_a>left_b && right_a < right_b) {
        if (bottom_a >= top_b) return true;
    }
    return false;
}
bool CheckFocusMouse(int x, int y, SDL_Rect rect) {//kiểm tra focus chuột
    if (x >= rect.x && x <= rect.x + 250 && y >= rect.y && y <= rect.y + 45) {
        cout << rect.x << endl << rect.y << endl;
        return true;
    }
    return false;
}
int ShowMenu(SDL_Surface* des, TTF_Font* font) {
    g_menu = Load_image("menufinal.png");
    if (g_menu == NULL) {
        return 4;
    }
    const int Num_item = 5;
    SDL_Rect pos_arr[Num_item];
    pos_arr[0].x = 505;
    pos_arr[0].y = 425;

    pos_arr[1].x = 505;
    pos_arr[1].y = 480;

    pos_arr[2].x = 505;
    pos_arr[2].y = 535;

    pos_arr[3].x = 505;
    pos_arr[3].y = 590;

    pos_arr[4].x = 505;
    pos_arr[4].y = 645;

    TextObject Text_menu[Num_item];
    Text_menu[0].Set_text("Play Game");
    Text_menu[0].Set_Color(4);
    Text_menu[0].Set_rect(pos_arr[0].x, pos_arr[0].y);
    Text_menu[1].Set_text("Character");
    Text_menu[1].Set_Color(4);
    Text_menu[1].Set_rect(pos_arr[1].x, pos_arr[1].y);
    Text_menu[2].Set_text("Highest score");
    Text_menu[2].Set_Color(4);
    Text_menu[2].Set_rect(pos_arr[2].x, pos_arr[2].y);
    Text_menu[3].Set_text("Game Guide");
    Text_menu[3].Set_Color(4);
    Text_menu[3].Set_rect(pos_arr[3].x, pos_arr[3].y);
    Text_menu[4].Set_text("Exit");
    Text_menu[4].Set_Color(4);
    Text_menu[4].Set_rect(pos_arr[4].x, pos_arr[4].y);
    int xm = 0;
    int ym = 0;
    bool Selected[Num_item] = { false, false };
    SDL_Event m_event;
    while (true) {
        applySurface(g_menu, des, 0, 0);
        for (int i = 0; i < Num_item; ++i) {
            Text_menu[i].Render_text(font, des);
        }
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 4;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < Num_item; ++i) {
                    if (CheckFocusMouse(xm, ym, Text_menu[i].Get_rect())) {
                        if (Selected[i] == false) {
                            Selected[i] = true;
                            Text_menu[i].Set_Color(0);
                        }
                    }
                    else {
                        if (Selected[i] == true) {
                            Selected[i] = false;
                            Text_menu[i].Set_Color(4);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < Num_item; ++i) {
                    if (CheckFocusMouse(xm, ym, Text_menu[i].Get_rect())) {
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    return 4;
                }
            default:
                break;
                
            }
        }
        SDL_Flip(des);
    }
    return 4;
}
int ShowCharacter(SDL_Surface* des, TTF_Font* font){
    g_SelectChar = Load_image("testchar1.png");

    if (g_SelectChar == NULL) {
        return 5;
    }
    const int NUM_Char = 5;
    SDL_Rect pos_char[NUM_Char];
    pos_char[0].x = 200;
    pos_char[0].y = 330;

    pos_char[1].x = 800;
    pos_char[1].y = 330;

    pos_char[2].x = 200;
    pos_char[2].y = 660;

    pos_char[3].x = 800;
    pos_char[3].y = 660;
    
    pos_char[4].x = 20;
    pos_char[4].y = 20;
    TextObject characters[NUM_Char];
    characters[0].Set_text("HUST's Boy");
    characters[0].Set_Color(4);
    characters[0].Set_rect(pos_char[0].x, pos_char[0].y);

    characters[1].Set_text("HUST's Girl");
    characters[1].Set_Color(4);
    characters[1].Set_rect(pos_char[1].x, pos_char[1].y);

    characters[2].Set_text("Teacher");
    characters[2].Set_Color(4);
    characters[2].Set_rect(pos_char[2].x, pos_char[2].y);

    characters[3].Set_text("Volunteer student");
    characters[3].Set_Color(4);
    characters[3].Set_rect(pos_char[3].x, pos_char[3].y);

    characters[4].Set_text("Back");
    characters[4].Set_Color(4);
    characters[4].Set_rect(pos_char[4].x, pos_char[4].y);

    int xm = 0;
    int ym = 0;
    bool Selected[NUM_Char] = { false, false };
    SDL_Event m_event;
    while (true) {
        applySurface(g_SelectChar, des, 0, 0);
        for (int i = 0; i < NUM_Char; ++i) {
            characters[i].Render_text(font, des);
        }
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 5;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < NUM_Char; ++i) {
                    if (CheckFocusMouse(xm, ym, characters[i].Get_rect())) {
                        if (Selected[i] == false) {
                            Selected[i] = true;
                            characters[i].Set_Color(0);
                        }
                    }
                    else {
                        if (Selected[i] == true) {
                            Selected[i] = false;
                            characters[i].Set_Color(4);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < NUM_Char; ++i) {
                    if (CheckFocusMouse(xm, ym, characters[i].Get_rect())) {
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    return 5;
                }
            default:
                break;

            }
        }
        SDL_Flip(des);
    }
    return 5;
}
int ShowGuide(SDL_Surface* des, TTF_Font* font){
    g_Guide = Load_image("guide.png");
    if (g_Guide == NULL) {
        return 0;
    }
    TextObject Back;
    Back.Set_text("Back");
    Back.Set_Color(4);
    Back.Set_rect(20, 20);
    int xm = 0;
    int ym = 0;
    bool Selected = false;
    SDL_Event m_event;
    while (true) {
        applySurface(g_Guide, des, 0, 0);
        Back.Render_text(font, des);
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                if (CheckFocusMouse(xm, ym, Back.Get_rect())) {
                    if (Selected == false) {
                        Selected = true;
                        Back.Set_Color(0);
                    }
                }
                 else {
                    if (Selected == true) {
                        Selected = false;
                        Back.Set_Color(4);
                        }
                 }
                
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                if (CheckFocusMouse(xm, ym, Back.Get_rect())) {
                    return 1;
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
            default:
                break;

            }
        }
        SDL_Flip(des);
    }
    return 0;
}
int ShowHighestScore(SDL_Surface* des, TTF_Font* font, TTF_Font* font1) {
    g_Score = Load_image("score.png");
    if (g_Score == NULL) {
        return 0;
    }
    string text = to_string(ReadFile1("score.txt"));
    TextObject H_score;
    H_score.Set_Color(4);
    H_score.Set_rect(550, 400);
    H_score.Set_text(text);
    TextObject Back;
    Back.Set_text("Back");
    Back.Set_Color(4);
    Back.Set_rect(20, 20);
    int xm = 0;
    int ym = 0;
    bool Selected = false;
    SDL_Event m_event;
    while (true) {
        applySurface(g_Score, des, 0, 0);
        Back.Render_text(font, des);
        H_score.Render_text(font1, des);
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                if (CheckFocusMouse(xm, ym, Back.Get_rect())) {
                    if (Selected == false) {
                        Selected = true;
                        Back.Set_Color(0);
                    }
                }
                else {
                    if (Selected == true) {
                        Selected = false;
                        Back.Set_Color(4);
                    }
                }

            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                if (CheckFocusMouse(xm, ym, Back.Get_rect())) {
                    return 1;
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
            default:
                break;

            }
        }
        SDL_Flip(des);
    }
    return 0;
}