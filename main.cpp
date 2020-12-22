
#include "Test.h"
#include "Object.h"
#include "Character.h"
#include "Threats.h"
#include "TextGame.h"
#include "File.h"
#undef main
using namespace std;
TTF_Font* g_font = NULL;
TTF_Font* g_fontMenu = NULL;
TTF_Font* g_fontscore = NULL;
TTF_Font* g_fontover = NULL;
bool Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }
    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (g_screen == NULL) {
        return false;
    }
    if (TTF_Init() == -1) {
        return false;
    }
    g_font = TTF_OpenFont("Napolitana.otf", 65);
    g_fontMenu = TTF_OpenFont("Bubblegum.ttf", 40);
    g_fontscore = TTF_OpenFont("Bubblegum.ttf", 200);
    g_fontover = TTF_OpenFont("Bubblegum.ttf", 100);
    if (g_font == NULL||g_fontMenu == NULL||g_fontover == NULL||g_fontscore == NULL) {
        return false;
    }
    return true;
}

int main(int argc , char* argv[])
{
    cout << "Hello" << endl;
    int count = 0;
    int score = 0;

    //Load MainMenu
    
    bool Is_quit = false;
    if (Init() == false) {
        return 0;
    }

    //Tạo nhân vật chính
    Main_character human;
    human.Set_rect(300, 500);
    human.name = "malechar.png";
    human.mask = "malemask.png";
    bool test = human.Loadimg(human.name);
    if (!test) return 0;

    //Tạo vật rơi
    Threats* PLANE = new Threats[NUM_THREATS];
    PLANE[0].Name = "virus.png";
    PLANE[0].Set_Bonus(-1);
    PLANE[1].Name = "A.png";
    PLANE[1].Set_Bonus(4);
    PLANE[2].Name = "B.png";
    PLANE[2].Set_Bonus(3);
    PLANE[3].Name = "virus.png";
    PLANE[3].Set_Bonus(-1);
    PLANE[4].Name = "D.png";
    PLANE[4].Set_Bonus(1);
    PLANE[5].Name = "virus.png";
    PLANE[5].Set_Bonus(-1);
    PLANE[6].Name = "virus.png";
    PLANE[6].Set_Bonus(-1);
    PLANE[7].Name = "water.png";
    PLANE[7].Set_Bonus(-3);
    PLANE[8].Name = "B.png";
    PLANE[8].Set_Bonus(3);
    PLANE[9].Name = "C.png";
    PLANE[9].Set_Bonus(2);
    PLANE[10].Name = "virus.png";
    PLANE[10].Set_Bonus(-1);
    PLANE[11].Name = "ktrfinal.png";
    PLANE[11].Set_Bonus(-2);


    //tạo text điểm
    TextObject ScoreGame;
    ScoreGame.Set_Color(2);
    ScoreGame.Set_rect(30, 30);
    TextObject Virus;
    Virus.Set_Color(0);
    Virus.Set_rect(30, 100);
    string number_virus = "Virus:  ";
    TextObject Gover;
    Gover.Set_rect(250, 600);

    //Tạo menu
start:
    g_image = Load_image("bg3.png");
    if (g_image == NULL) return 0;
    int Ret_menu = ShowMenu(g_screen, g_fontMenu);
    int k = Ret_menu;
    if (Ret_menu == 4) Is_quit = true;
    if (k == 1) {//Menu chọn nhân vật
        int Ret_char = ShowCharacter(g_screen, g_fontMenu);
        switch (Ret_char)
        {
        case(0):
        {
            human.name = "malechar.png";
            human.mask = "malemask.png";
            test = human.Loadimg(human.name);
        }
        break;
        case(1):
        {
            human.name = "hustgirl.png";
            human.mask = "femalemask.png";
            test = human.Loadimg(human.name);
        }
        break;
        case(2):
        {
            human.name = "teacher.png";
            human.mask = "teachermask.png";
            test = human.Loadimg(human.name);
        }
            break;
        case(3):
        {
            human.name = "svtn.png";
            human.mask = "svtnmask.png";
            test = human.Loadimg(human.name);
        }
        break;
        case(4):
        {
            goto start;
        }
        break;
        default:
            break;
        }
    }
    if (k == 2) {//Show điểm cao nhất
        int Ret_score = ShowHighestScore(g_screen, g_fontMenu, g_fontscore);
        switch (Ret_score) {
        case(0): {
            Is_quit = true;
        }
               break;
        case(1): {
            goto start;
        }
               break;
        default:
            break;
        }
    }
    if (k == 3) {//Hướng dẫn chơi
        int Ret_guide = ShowGuide(g_screen, g_fontMenu);
        cout << Ret_guide << endl;
        switch (Ret_guide) {
        case(0): {
            Is_quit = true;
        }
               break;
        case(1): {
            goto start;
        }
               break;
        default:
            break;
        }
    }

    for (int i = 0; i < NUM_THREATS; ++i) {
        Threats* plane = (PLANE + i);
        test = plane->Loadimg(plane->Name);
        if (!test) return 0;
        int ran_x = (rand() % 10 + 1) * 100;
        if (ran_x > 950|| ran_x < 250) {//Tạo random vị trí
            ran_x = 250;
        }
        cout << ran_x << endl;
        plane->Set_rect(ran_x, 0-(i+1)*400);
    }
    int mask = 0;
    int val = 1;
    while (!Is_quit) {
        while (SDL_PollEvent(&g_even)) {
            if (g_even.type == SDL_QUIT) {
                Is_quit = true;
                break;
            }
            human.InputAction(g_even);
        }
        applySurface(g_image, g_screen, 0, 0);
        human.Show(g_screen);
        human.Move();
        for (int ii = 0; ii < NUM_THREATS; ++ii) {
            Threats* plane = (PLANE + ii);
            if (plane) {
                plane->Show(g_screen);
                plane->Move(SCREEN_WIDTH, SCREEN_HEIGHT);
                if (score > val * 30) ++val;
                plane->Set_Y_val(val);

                //kiem tra va cham:
                bool is_col = Check_Collision(plane->Get_rect(), human.Get_rect());
                if (is_col) {
                    if (plane->Get_Bonus() > 0) {
                        score += plane->Get_Bonus();
                        plane->Reset(0 - (ii + 1) * 400);
                        cout << score <<"    "<< count << endl;
                    }
                    if (plane->Get_Bonus() == -1) {
                        
                        if (mask != 0) { --mask; }
                        if (mask == 0) { 
                            human.Loadimg(human.name);
                            ++count;
                            number_virus += "X "; }
                        if (count <= 3) {
                      
                            plane->Reset(0 - (ii + 1) * 400);
                        }
                        else {
                            int y = ReadFile1("Score.txt");
                            if (score > y) {
                                string x = to_string(score);
                                WriteFile("Score.txt", x);
                            }
                            while (true) {
                                g_image = Load_image("gameover.png");
                                applySurface(g_image, g_screen, 0, 0);
                                string x = to_string(score);
                                string over = "Your score: ";
                                over += x;
                                Gover.Set_text(over);
                                Gover.Set_Color(5);
                                Gover.Render_text(g_fontover, g_screen);
                                SDL_Flip(g_screen);
                                switch (MessageBox(NULL, L"Do you want to quit", L"Game Over !!!", MB_OKCANCEL))
                                {
                                case IDOK:
                                {
                                    delete[] PLANE;
                                    Cleanup();
                                    SDL_Quit();
                                    return 0;
                                }
                                case IDCANCEL:
                                {
                                    count = 0;
                                    score = 0;
                                    number_virus = "Virus:  ";
                                    goto start;
                                }
                                break;
                                default:
                                    break;
                                }
                                

                            }                            
                        }
                    }
                    if (plane->Get_Bonus() == -2) {
                        mask = 2;
                        human.Loadimg(human.mask);
                        plane->Reset(0 - (ii + 1) * 400);
                    }
                    if (plane->Get_Bonus() == -3) {
                        count = (count > 1) ? (count - 2) : 0;
                        removeVirus(number_virus, count);
                        plane->Reset(0 - (ii + 1) * 400);
                    }
                }
            }
        }
        //in điểm 
        string score_val = to_string(score);
        string score_text = "SCORE:   ";
        score_text += score_val;
        ScoreGame.Set_text(score_text);
        ScoreGame.Render_text(g_font, g_screen);
        Virus.Set_text(number_virus);
        Virus.Render_text(g_font, g_screen);
        if (SDL_Flip(g_screen) == -1) {
            return 0;
        }
    }
    delete[] PLANE;
    Cleanup();
    SDL_Quit();
    return 1;
}