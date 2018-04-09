#include "TXLib.h"
#include "Chars.cpp"
#include "Ñonstants.cpp"
#include <string>

using namespace std;
 //ÏÎÌÎÃÈÒÅ! Îíî íå ðàáîòàåò. Ñáèëñÿ ñî ñêîáêàìè.
//menu1 ÿ ïðîáðîñèë âî âñå ôóíêöèè (áóäåò íåõîðîøî, åñëè ïðè âûçîâå ìåíþøêè èç èãðû ó òåáÿ ïðîïàäåò ÿçûê)
void FGameOver (bool* GameOver, Player* pers, Player* enemy, Player* ally,
                                Player enemy_old, Player ally_old, Player pers_old,
                                int screenH, int screenW, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1);
void Game ( Player pers, Player enemy, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1);
void menushka(Player* pers, bool* StartGame, bool* GameOver, menupics* menu1);
void proSpeeds(Player* pers);
void ProPre(menupics* menu1);


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





    Player pers = {100, 100, 116, 117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("CharsPic/Stels pers.bmp")};
    Player pers_old = pers;
    Player ally = {200, 200,116,117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("CharsPic/ally.bmp")};
    Player ally_old = ally;
    Player enemy = {screenW-200, screenH-200,116,117, 3, 2, 0, 100, 100, 10, 5, 0, txLoadImage("CharsPic/enemy.bmp")};
    Player enemy_old = enemy;

    menupics menu1 = {  txLoadImage("menu/menuEN.bmp"),
                        txLoadImage("menu/author.bmp"),
                        txLoadImage("menu/prehistoryEN.bmp"),
                        txLoadImage("menu/ContractTypeEN.bmp"),
                        txLoadImage("menu/pauseEN.bmp")};






    while (StartGame != true)
    {
        menushka(&pers, &StartGame, &GameOver, &menu1);
        if (GameOver)
        {
            return 0;
        }
    }



    if (StartGame==true) {
        Game (pers,enemy, ally, GameOver, screenH, screenW, &menu1);
    }
    txDeleteDC(pers.pic);
    txDeleteDC(enemy.pic);
    txDeleteDC(menu1.picmenu);
    txDeleteDC(menu1.picautor);
    txDeleteDC(menu1.picprehis);
    txDeleteDC(menu1.pictypes);

    return 0;
}

void FGameOver (bool* GameOver, Player* pers,        Player* enemy,       Player* ally,
                                Player enemy_old,   Player ally_old,    Player pers_old,
                                int screenH, int screenW, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1) {


    if (enemy->frame == 1) {
        bool BackMenu = false;

        while(!BackMenu) {
            *GameOver = true;
            txBitBlt (txDC(), screenW/2-161, screenH/2-56, 382, 112, GameOverPicBad, 0, 0);
            if (GetAsyncKeyState('R')) {
                BackMenu = true;
                pers_old.speed = pers->speed;
                *pers = pers_old;
                *enemy = enemy_old;
                *ally = ally_old;
                *GameOver = false;
            }

            if (GetAsyncKeyState(VK_RETURN)) {
                BackMenu = true;
                *StartGame = false;
                txClear();
                *pers = pers_old;
                *enemy = enemy_old;
                *ally = ally_old;
                menushka(pers, StartGame, GameOver, menu1);
            }
            txSleep(10);
        }

    } else if (pers->x == finish) {
    //*GameOver = true;
    }
 }

void Game (Player pers, Player enemy, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1) {

    Player enemy_old = enemy;
    Player ally_old = ally;
    bool StartGame = false;
    Player pers_old = pers;

    int nWallD = 16;
    HDC GameOverPicBad = txLoadImage("menu/GameOver.bmp");
    HDC Level = txLoadImage("Levels/Level1.bmp");
        int mapSizeX = 1920;
        int mapSizeY = 1066;
        int mapX = 0;
        int mapY = 0;

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



        txBitBlt(txDC(), 0, 0, mapSizeX, mapSizeY, Level, mapX, mapY);

        int mapX =mapX+pers.x;
        int mapY =mapY+pers.y;

        char health_string[100];
        sprintf(health_string, "Çäîðîâüå %d êîîðäèíàòû %d %d  Ýêðàí %d  %d", pers.hp, pers.x, pers.y, screenW, screenH);
        txTextOut(screenW-500, screenH-100, health_string);

        txTransparentBlt(txDC(), pers.x, pers.y, pers.pdl, pers.pshir, pers.pic, pers.pdl * round(pers.frame), pers.pshir * pers.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), enemy.x, enemy.y, enemy.pdl, enemy.pshir, enemy.pic, enemy.pdl * round(enemy.frame), enemy.pshir * enemy.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), ally.x, ally.y, ally.pdl, ally.pshir, ally.pic, ally.pdl * round(ally.frame), ally.pshir * ally.direction, RGB(255 , 255, 255));




        /*Ñäåëàé îòäåëüíîé ôóíêöèåé. À åù¸ ëó÷øå çàêëþ÷è ýòî âñå â if
        (https://github.com/IngenerkaTeamCenter/SchoolEscape/blob/master/Lib/Director.cpp 151-158 ñòðîêè
         https://github.com/IngenerkaTeamCenter/SchoolEscape/blob/master/Lib/consmenu.cpp 16 ñòðîêà)
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

        HDC UPG=txLoadImage("menu/upgEN");
        if (GetAsyncKeyState('P')) {
            while(!GetAsyncKeyState('P')) {
                txBitBlt (txDC(), 0, 0, 500, 300,menu1->picpause, 0, 0);
                txSleep(10);
                if (!GetAsyncKeyState('U')) {
                    while(!GetAsyncKeyState(VK_BACK)) {
                        txBitBlt (txDC(), 0, 0, 1024, 768,UPG, 0, 0);
                    }
                }
            }
        }

        txEnd();
        FGameOver (&GameOver, &pers, &enemy, &ally,
                              enemy_old, ally_old, pers_old,
                              screenH,screenW,GameOverPicBad, 500, &StartGame, menu1);
        txSleep(20);
    }

    txDeleteDC(GameOverPicBad);
    txDeleteDC(Level);
}



void menushka(Player* pers, bool* StartGame, bool* GameOver,  menupics* menu1) {

    bool Language = false;


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
                menu1->picpause = txLoadImage("menu/pauseEN.bmp");
            } else {
                menu1->picmenu = txLoadImage("menu/menuRU.bmp");
                menu1->picprehis = txLoadImage("menu/prehistoryRU.bmp");
                menu1->pictypes = txLoadImage("menu/ContractTypeRU.bmp");
                menu1->picpause = txLoadImage("menu/pauseRU.bmp");
            }

            Language = !Language;
            txSleep(100);
        }

        else if (650 <= txMouseX() && txMouseX() <= 955 &&
                 230 <= txMouseY() && txMouseY() <= 305 && txMouseButtons() & 1) {
            ProPre(menu1);
        }

        else if (620 <= txMouseX() && txMouseX() <= 970 &&
                 345 <= txMouseY() && txMouseY() <= 388 && txMouseButtons() & 1) {
            proSpeeds(pers);
        }

        else if (725 <= txMouseX() && txMouseX() <=985 &&
                 465 <= txMouseY() && txMouseY() <=500 && txMouseButtons() & 1){
            txBitBlt (txDC(), 0, 0, 912, 446, menu1->picautor, 0, 0);
            txSleep(15000);
        }

        txSleep(10);
    }
}

void proSpeeds(Player* pers){

            char ForSpeed[20];
            sprintf(ForSpeed, "%d", pers->speed);//Ýòó ñòðîêó ÿ ïî ïóòè ïîòåðÿë
            const char* s =
                txInputBox ("Enter speed/Ââåäèòå ñêîðîñòü",
                "Enter speed/Ââåäèòå ñêîðîñòü", ForSpeed);
            int speed = atoi(s);
            pers->speed = speed;
            }

void ProPre(menupics* menu1){


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
/*óñëîâèå âûõîäà
Àïãðåéäû ìåíþøêà
åñëè âèäèìàÿ
åñëè ïî ó î÷åíü áëèçêè
ðàçíîñòü èãðîê ñòåíà
Ïîäãîíè ïîä 1024 * 768
*/
