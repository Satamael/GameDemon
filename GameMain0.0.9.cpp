#include "TXLib.h"
#include "Chars.cpp"
#include "Constants.cpp"
#include <string>

int mapX = 0;




using namespace std;

void FGameOver (bool* GameOver, Player* pers, Player* enemy, Player* enemy2,  Player enemy2_old, Player* ally,
                                Player enemy_old, Player ally_old, Player pers_old,
                                int screenH, int screenW, HDC win, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1, UPs* listt, int kills);
void Game ( Player pers, Player enemy,Player enemy2, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1,UPs* listt);
void menushka(Player* pers, bool* StartGame, bool* GameOver, menupics* menu1);
void proSpeeds(Player* pers);
void ProPre(menupics* menu1);
void ProPause(menupics* menu1, Player* pers,Player* pers_old,Player* ally, Player* ally_old,Player* enemy, UPs* listt);
void Upg(UPs* listt, HDC UPG,Player* pers,Player* pers_old, Player* ally,Player* ally_old);


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
    txSetFillColor(TX_BLACK);




    Player pers = {100, 25, 116, 117, 5, 2, 0, 50, 100, 10, 5, 1, txLoadImage("CharsPic/Stels pers.bmp")};
    Player pers_old = pers;
    Player ally = {200, 50,116,117, 5, 2, 0, 50, 100, 10, 5, 1, txLoadImage("CharsPic/ally.bmp")};
    Player ally_old = ally;
    Player enemy = {1740, 760,116,117, 3, 2, 0, 1, 100, 10, 5, 0, txLoadImage("CharsPic/enemy.bmp")};
    Player enemy_old = enemy;
    Player enemy2 = {1600, 280,116,117, 3, 2, 2, 100, 100, 10, 5, 0, txLoadImage("CharsPic/enemy.bmp")};
    Player enemy2_old = enemy2;
    UPs listt{0,0,0,0,25};
    menupics menu1 = {  txLoadImage("menu/menuEN.bmp"),
                        txLoadImage("menu/author.bmp"),
                        txLoadImage("menu/prehistoryEN.bmp"),
                        txLoadImage("menu/ContractTypeEN.bmp"),
                        txLoadImage("menu/pauseEN.bmp"),
                        txLoadImage("menu/UpgEN.bmp")};






    while (StartGame != true)
    {
        menushka(&pers, &StartGame, &GameOver, &menu1);
        if (GameOver)
        {
            return 0;
        }
    }



    if (StartGame==true) {
        Game (pers,enemy, enemy2, ally, GameOver, screenH, screenW, &menu1,&listt);
    }
    txDeleteDC(pers.pic);
    txDeleteDC(enemy.pic);
    txDeleteDC(enemy2.pic);
    txDeleteDC(ally.pic);
    txDeleteDC(menu1.picmenu);
    txDeleteDC(menu1.picautor);
    txDeleteDC(menu1.picprehis);
    txDeleteDC(menu1.pictypes);
    txDeleteDC(menu1.picpause);
    txDeleteDC(menu1.picupg);

    return 0;
}

void FGameOver (bool* GameOver, Player* pers,        Player* enemy, Player* enemy2,  Player enemy2_old,   Player* ally,
                                Player enemy_old,   Player ally_old,    Player pers_old,
                                int screenH, int screenW, HDC win, HDC GameOverPicBad, int finish,  bool* StartGame, menupics* menu1,UPs* listt,int kills) {
 bool BackMenu = false;

     if (enemy->frame == 1 and abs(enemy->x - pers->x) < 70 and abs(enemy->y - pers->y) < 70){
     pers->hp=pers->hp-1;
     }

     if (enemy2->frame == 1 and abs(enemy2->x - pers->x) < 70 and abs(enemy2->y - pers->y) < 70){
     pers->hp=pers->hp-1;
     }

    if (enemy->frame == 1 and abs(enemy->x - ally->x) < 70 and abs(enemy->y - ally->y) < 70){
     ally->hp=ally->hp-1;
     }

     if (enemy2->frame == 1 and abs(enemy2->x - ally->x) < 70 and abs(enemy2->y - ally->y) < 70){
     ally->hp=ally->hp-1;
     }

    if (pers->hp<1 or ally->hp<1){


        while(!BackMenu) {
            *GameOver = true;
            txBitBlt (txDC(), screenW/2-161, screenH/2-56, 382, 112, GameOverPicBad, 0, 0);
            if (GetAsyncKeyState('R')) {
                BackMenu = true;
                pers_old.speed = pers->speed;
                *pers = pers_old;
                *enemy = enemy_old;
                *enemy2 = enemy2_old;
                *ally = ally_old;
                *GameOver = false;
            }

            if (GetAsyncKeyState(VK_RETURN)) {
                BackMenu = true;
                *StartGame = false;

                txClear();
                *pers = pers_old;
                *enemy = enemy_old;
                *enemy2 = enemy2_old;
                *ally = ally_old;
                menushka(pers, StartGame, GameOver, menu1);

            }
            txSleep(10);
        }

    } else if (txGetPixel((pers->x)/10, (pers->y)/10)==RGB(255,242,0)) {
    *GameOver = true;

    while(!BackMenu) {
    txBitBlt (txDC(), screenW/2-161, screenH/2-56, 382, 112, win, 0, 0);
    txSleep(10);
    if (GetAsyncKeyState(VK_RETURN)) {
                BackMenu = true;
                *StartGame = false;
                listt->Souls=listt->Souls+1+(kills+1*listt->SoulHuntUp);
                txClear();
                *pers = pers_old;
                *enemy = enemy_old;
                *ally = ally_old;
                menushka(pers, StartGame, GameOver, menu1);
            }
            }
    }
 }

void Game (Player pers, Player enemy,Player enemy2, Player ally, bool GameOver, int screenH, int screenW, menupics* menu1,UPs* listt) {

    int kills = 0;
    Player enemy_old = enemy;
    Player ally_old = ally;
    bool StartGame = false;
    Player pers_old = pers;
    Player enemy2_old = enemy2;

    int nWallD = 16;
    HDC GameOverPicBad = txLoadImage("menu/GameOver.bmp");
    HDC win = txLoadImage("menu/win.bmp");
    HDC Level = txLoadImage("Levels/Level1.bmp");
    HDC LevelCheck = txLoadImage("Levels/Level11.bmp");
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
        enemy2.x1 = enemy2.x;
        enemy2.y1 = enemy2.y;
        ally.x1 = ally.x;
        ally.y1 = ally.y;

        StelsPerson(&pers, ally, enemy,enemy2, screenW, screenH);
        Enemy(pers, &enemy, ally, screenW, screenH);
        Enemy(pers, &enemy2, ally, screenW, screenH);
        Ally(pers, enemy,enemy2, &ally, screenW, screenH);
        NewWallPush(&pers, mapSizeX, mapSizeY, mapX, mapY, LevelCheck);
        FGameOver (&GameOver, &pers, &enemy, &enemy2, enemy2_old, &ally,
                              enemy_old, ally_old, pers_old,
                              screenH,screenW, win, GameOverPicBad, 500, &StartGame, menu1,listt,kills);
        NewEnGo(&enemy,mapSizeX,mapSizeY,mapX,mapY, LevelCheck);
        NewEnGo(&enemy2,mapSizeX,mapSizeY,mapX,mapY, LevelCheck);

        if (mapX > mapSizeX+200)
        {
            pers.x = pers.x - pers.speed;
        }

        if (mapY > mapSizeY+200)
        {
            pers.y = pers.y - pers.speed;
        }

        txBitBlt(txDC(), 0, 0, mapSizeX, mapSizeY, Level, mapX, mapY);

        mapX = pers.x - 200;
        mapY = pers.y - 200;



        txTransparentBlt(txDC(), pers.x  - mapX, pers.y  - mapY, pers.pdl, pers.pshir, pers.pic, pers.pdl * round(pers.frame), pers.pshir * pers.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), enemy.x - mapX, enemy.y - mapY, enemy.pdl, enemy.pshir, enemy.pic, enemy.pdl * round(enemy.frame), enemy.pshir * enemy.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), enemy2.x - mapX, enemy2.y - mapY, enemy2.pdl, enemy2.pshir, enemy2.pic, enemy2.pdl * round(enemy2.frame), enemy2.pshir * enemy2.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), ally.x  - mapX, ally.y  - mapY, ally.pdl, ally.pshir, ally.pic, ally.pdl * round(ally.frame), ally.pshir * ally.direction, RGB(255 , 255, 255));





        txSetColor(TX_RED);
        char str[100];
        sprintf(str, "%d", ally.hp);
        txTextOut(100, 100, str);
        sprintf(str, "%d", pers.hp);
        txTextOut(100, 200, str);



        txEnd();



        ProPause(menu1,&pers, &pers_old,&ally,&ally_old,&enemy, listt);
        txSleep(20);
    }

    txDeleteDC(GameOverPicBad);
    txDeleteDC(win);
    txDeleteDC(Level);
    txDeleteDC(LevelCheck);
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
                menu1->picupg = txLoadImage("menu/UpgEN.bmp");
            } else {
                menu1->picmenu = txLoadImage("menu/menuRU.bmp");
                menu1->picprehis = txLoadImage("menu/prehistoryRU.bmp");
                menu1->pictypes = txLoadImage("menu/ContractTypeRU.bmp");
                menu1->picpause = txLoadImage("menu/pauseRU.bmp");
                menu1->picupg = txLoadImage("menu/UpgRU.bmp");
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

void ProPre(menupics* menu1) {

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

void ProPause(menupics* menu1, Player* pers,Player* pers_old,Player* ally, Player* ally_old,Player* enemy, UPs* listt) {

    if (GetAsyncKeyState('P')) {

        HDC picP = menu1->picpause;
        HDC UPG = menu1->picupg;
        txSleep(1000);

        while(!GetAsyncKeyState('P')) {

            txClear();
            txBitBlt (txDC(), 0, 0, 500, 300, picP, 0, 0);
            txSleep(10);

            if (GetAsyncKeyState('U')) {
                while(!GetAsyncKeyState(VK_BACK)) {
                    txClear();
                    Upg(listt,UPG,pers,pers_old,ally, ally_old);
                    txSleep(10);
                }

            }


        }
        txSleep(1000);
        //txDeleteDC(UPG);
    }
}

void Upg(UPs* listt, HDC UPG,Player* pers,Player* pers_old, Player* ally,Player* ally_old){

    txBitBlt (txDC(), 0, 0, 1024, 768, UPG, 0, 0);
    char soul_string[100];
    sprintf(soul_string, "%d", listt->Souls);
    txTextOut (900, 75, soul_string);

    txRectangle(200,90, 190+(listt->inviseUp) * 10*(320/5)+5,190);
    txRectangle(200,270, 190+(listt->SoulHuntUp)*(320/5)+5,370);
        txRectangle(200,450, 190+(listt->HPUp)*(320/5)+5,540);
    txRectangle(200,630, 190+(listt->AllyHPUp)*(320/5)+5,730);
    if (505 <= txMouseX() && txMouseX() <= 600 &&
         80 <= txMouseY() && txMouseY() <= 160 &&
         txMouseButtons() & 1 && listt->Souls>0 && listt->inviseUp<0.5) {
        listt->inviseUp = listt->inviseUp+0.1;
        listt->Souls = listt->Souls - 1;
        txSleep(100);
    }

     if (505 <= txMouseX() && txMouseX() <= 600 &&
         260 <= txMouseY() && txMouseY() <= 340 &&
         txMouseButtons() & 1 && listt->Souls>0 && listt->SoulHuntUp<5) {
        listt->SoulHuntUp = listt->SoulHuntUp+1;
        listt->Souls = listt->Souls - 1;
        txSleep(100);
    }

     if (505 <= txMouseX() && txMouseX() <= 600 &&
         440 <= txMouseY() && txMouseY() <= 520 &&
         txMouseButtons() & 1 && listt->Souls>0 && listt->HPUp<5) {
        listt->HPUp = listt->HPUp+1;
        listt->Souls =listt->Souls - 1;
        pers->hp=pers->hp+50*listt->HPUp;
        txSleep(100);
    }

    if (505 <= txMouseX() && txMouseX() <= 600 &&
         620 <= txMouseY() && txMouseY() <= 700 &&
         txMouseButtons() & 1 && listt->Souls>0 && listt->AllyHPUp<5) {
        listt->AllyHPUp =listt->AllyHPUp+1;
        listt->Souls = listt->Souls - 1;
        ally->hp=ally->hp+50*listt->AllyHPUp;
        txSleep(100);


    }
pers_old->hp=pers->hp;
ally_old->hp=ally->hp;
}
