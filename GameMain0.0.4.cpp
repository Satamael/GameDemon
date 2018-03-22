#include "TXLib.h"
#include "Chars.cpp"
#include "Сonstants.cpp"
#include <string>

using namespace std;

//menu1 я пробросил во все функции (будет нехорошо, если при вызове менюшки из игры у тебя пропадет язык)
void FGameOver (bool* GameOver, Player pers, Player enemy, Player ally,
                                Player enemy_old, Player ally_old, Player pers_old,
                                int screenH, int screenW, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1);
void Game (Wall* dark, Player pers, Player enemy, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1);
void menushka(Player* pers, bool* StartGame, bool* GameOver, menupics* menu1);

int screenWDoma = 2400;

int main()
{
    txDisableAutoPause();
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int finish;
    bool GameOver = false;
    bool StartGame = false;
    bool Language = false;
    txCreateWindow(screenW, screenH);
    int nWallD = 16;


    srand(time(NULL));


    Player pers = {100, 100, 116, 117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("CharsPic/Stels pers.bmp")};
    Player pers_old = pers;
    Player ally = {200, 200,116,117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("CharsPic/ally.bmp")};
    Player ally_old = ally;
    Player enemy = {screenW-200, screenH-200,116,117, 3, 2, 0, 100, 100, 10, 5, 0, txLoadImage("CharsPic/enemy.bmp")};
    Player enemy_old = enemy;
    Wall dark[nWallD];
    menupics menu1 = {  txLoadImage("menu/menuEN.bmp"),
                        txLoadImage("menu/autor.bmp"),
                        txLoadImage("menu/prehistoryEN.bmp"),
                        txLoadImage("menu/ContractTypeEN.bmp")};

    //Сделай отдельной функцией
    for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {

        dark[nomer_steny] = {0,  0, screenW / 10, screenW / 10,txLoadImage("CharsPic/WallDark.bmp")};

        bool stolkn = false;
        int x_st = random (screenW - 100);
        int y_st = random (screenH - 100);

        for (int nomer = 0; nomer < nomer_steny; nomer++)
        {
            if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                             dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height))
            {
                stolkn = true;
            }
            else if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                                  pers.x,               pers.y, pers.pdl, pers.pshir))
            {
                stolkn = true;
            }
            else if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                                  enemy.x,              enemy.y, enemy.pdl, enemy.pshir))
            {
                stolkn = true;
            }
        }

        while (stolkn)
        {
            stolkn = false;
            x_st = random (screenW - 100);
            y_st = random (screenH - 100);
            for (int nomer = 0; nomer < nomer_steny; nomer++)
            {
                if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                                 dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height))
                {
                    stolkn = true;
                }
                else if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                                      pers.x,               pers.y, pers.pdl, pers.pshir))
                {
                    stolkn = true;
                }
                else if (stolknovenie(x_st,                 y_st,                dark[nomer_steny].length, dark[nomer_steny].height,
                                      enemy.x,              enemy.y, enemy.pdl, enemy.pshir))
                {
                    stolkn = true;
                }
            }

            //cout << nomer_steny << " " << x_st << std::endl;
        }

        dark[nomer_steny].x = x_st;
        dark[nomer_steny].y = y_st;
    }



    while (StartGame != true)
    {
        menushka(&pers, &StartGame, &GameOver, &menu1);
        if (GameOver)
        {
            return 0;
        }
    }



    if (StartGame==true) {
        Game (dark, pers,enemy, ally, GameOver, screenH, screenW, &menu1);
    }

    //Не удаляешь многие картинки (из menu1) например
    txDeleteDC(pers.pic);
    txDeleteDC(enemy.pic);
    for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {
        txDeleteDC(dark[nomer_steny].pic);
    }

    return 0;
}

void FGameOver (bool* GameOver, Player pers,        Player enemy,       Player ally,
                                Player enemy_old,   Player ally_old,    Player pers_old,
                                int screenH, int screenW, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1) {


    if (enemy.frame == 1) {
        bool BackMenu = false;

        while(!BackMenu) {
            *GameOver = true;
            txBitBlt (txDC(), screenW/2-161, screenH/2-56, 382, 112, GameOverPicBad, 0, 0);
            if (GetAsyncKeyState('R')) {
                BackMenu = true;
                pers = pers_old;
                enemy = enemy_old;
                ally = ally_old;
                *GameOver = false;
            }

            if (GetAsyncKeyState(VK_RETURN)) {
                BackMenu = true;
                *StartGame = false;
                menushka(&pers, StartGame, GameOver, menu1);
            }
            txSleep(10);
        }

    } else if (pers.x == finish) {
    //*GameOver = true;
    }
 }

void Game (Wall* dark, Player pers, Player enemy, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1) {

    Player enemy_old = enemy;
    Player ally_old = ally;
    bool StartGame = false;
    Player pers_old = pers;

    int nWallD = 16;
    HDC GameOverPicBad = txLoadImage("menu/GameOver.bmp");

    while (GameOver != true)
    {
        txSetColor(TX_BLACK);
        txClear();
        txBegin();

        pers.x1 = pers.x;
        pers.y1 = pers.y;
        enemy.x1 = enemy.x;
        enemy.y1 = enemy.y;
        ally.x1 = ally.x;
        ally.y1 = ally.y;

        StelsPerson(&pers, ally, enemy, screenW, screenH);
        Enemy(pers, &enemy, ally, screenW, screenH);
        Ally(pers, enemy, &ally, screenW, screenH);


        char health_string[100];
        sprintf(health_string, "Здоровье %d координаты %d %d  Экран %d  %d", pers.hp, pers.x, pers.y, screenW, screenH);
        txTextOut(screenW-500, screenH-100, health_string);

        txTransparentBlt(txDC(), pers.x, pers.y, pers.pdl, pers.pshir, pers.pic, pers.pdl * round(pers.frame), pers.pshir * pers.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), enemy.x, enemy.y, enemy.pdl, enemy.pshir, enemy.pic, enemy.pdl * round(enemy.frame), enemy.pshir * enemy.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), ally.x, ally.y, ally.pdl, ally.pshir, ally.pic, ally.pdl * round(ally.frame), ally.pshir * ally.direction, RGB(255 , 255, 255));


        for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {

            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &pers, screenW, screenH);
            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &enemy, screenW, screenH);
            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &ally, screenW, screenH);
            txTransparentBlt(txDC(), dark[nomer_steny].x, dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, dark[nomer_steny].pic, 0, 0, RGB(255 , 255, 255));
        }

        /*Сделай отдельной функцией. А ещё лучше заключи это все в if
        (https://github.com/IngenerkaTeamCenter/SchoolEscape/blob/master/Lib/Director.cpp 151-158 строки
         https://github.com/IngenerkaTeamCenter/SchoolEscape/blob/master/Lib/consmenu.cpp 16 строка)
        */
        txSetColor(TX_RED);
        char str[100];
        sprintf(str, "%d", ally.x);
        txTextOut(100, 100, str);
        sprintf(str, "%d", ally.y);
        txTextOut(100, 200, str);
        sprintf(str, "%d", ally.speed);
        txTextOut(100, 300, str);
        sprintf(str, "%d", ally.direction);
        txTextOut(100, 400, str);

        txEnd();
        FGameOver (&GameOver, pers, enemy, ally,
                              enemy_old, ally_old, pers_old,
                              screenH,screenW,GameOverPicBad, 500, &StartGame, menu1);
        txSleep(20);
    }

    txDeleteDC(GameOverPicBad);
}



void menushka(Player* pers, bool* StartGame, bool* GameOver,  menupics* menu1) {

    bool Language = false;

    //Следующие две строки нужны когда менюшку из игры вызываешь (у тебя GameOver был равен true, и в цикл ты не заходил)
    *StartGame = false;
    *GameOver = false;

    while (*StartGame != true && *GameOver != true)
    {
        txBitBlt (txDC(), 0, 0, 1024, 768, menu1->picmenu, 0, 0);

        if (GetAsyncKeyState('Q')){
            *GameOver = true;
        }

        if (635 <= txMouseX() && txMouseX() <= 980 &&
            156 <= txMouseY() && txMouseY() <= 200 && txMouseButtons() & 1) {
            *StartGame = true;

        } else if ( 29 <= txMouseX() && txMouseX() <= 115 &&
            657 <= txMouseY() && txMouseY() <= 716 && txMouseButtons() & 1) {

            if (!Language) {
                menu1->picmenu = txLoadImage("menu/menuEN.bmp");
                menu1->picprehis = txLoadImage("menu/prehistoryEN.bmp");
                menu1->pictypes = txLoadImage("menu/ContractTypeEN.bmp");
            } else {
                menu1->picmenu = txLoadImage("menu/menuRU.bmp");
                menu1->picprehis = txLoadImage("menu/prehistoryRU.bmp");
                menu1->pictypes = txLoadImage("menu/ContractTypeRU.bmp");
            }

            Language = !Language;
            txSleep(100);
        }

        else if (650 <= txMouseX() && txMouseX() <= 955 &&
                 230 <= txMouseY() && txMouseY() <= 305 && txMouseButtons() & 1) {

            //Сделай отдельной функцией
            bool ClosePrehistory = false;
            while(!ClosePrehistory) {

                txBitBlt (txDC(), 0, 0, 1024, 768,  menu1->picprehis, 0, 0);
                if (GetAsyncKeyState(VK_BACK)) {
                    ClosePrehistory = true;
                }

                if (GetAsyncKeyState(VK_SPACE)){
                    while(!GetAsyncKeyState(VK_BACK)){
                        txBitBlt (txDC(), 0, 0, 1024, 768,  menu1->pictypes, 0, 0);
                    }
                }
            }
        }

        else if (620 <= txMouseX() && txMouseX() <= 970 &&
                 345 <= txMouseY() && txMouseY() <= 388 && txMouseButtons() & 1) {

            //Сделай отдельной функцией
            char ForSpeed[20];
            sprintf(ForSpeed, "%d", pers->speed);//Эту строку я по пути потерял
            const char* s =
                txInputBox ("Enter speed/Введите скорость",
                "Enter speed/Введите скорость", ForSpeed);
            int speed = atoi(s);
            pers->speed = speed;
        }

        else if (725 <= txMouseX() && txMouseX() <=985 &&
                 465 <= txMouseY() && txMouseY() <=500 && txMouseButtons() & 1){
            txBitBlt (txDC(), 0, 0, 912, 446, menu1->picautor, 0, 0);
            txSleep(15000);
        }

        txSleep(10);
    }
}
/*условие выхода
Апгрейды менюшка
если видимая
если по у очень близки
разность игрок стена
Подгони под 1024 * 768
*/
