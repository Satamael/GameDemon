#include "TXLib.h"
#include "Chars.cpp"
#include "Сonstants.cpp"
 void FGameOver (bool* GameOver, Player pers, Player enemy, int screenH, int screenW, HDC GameOverPicBad, int finish);

int main()
{

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int finish;
    bool GameOver = false;
    txCreateWindow(screenW, screenH);
    HDC GameOverPicBad = txLoadImage("GameOver.bmp");
    srand(time(NULL));

    int nWallD = 16;
    Player pers = {100, 100, 116, 117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("Stels pers.bmp")};
    Player ally = {200, 200,116,117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("ally.bmp")};
    Player enemy = {screenW-200, screenH-200,116,117, 3, 2, 0, 100, 100, 10, 5, 0, txLoadImage("enemy.bmp")};
    Wall dark[nWallD];



    for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {

        dark[nomer_steny] = {0,  0, screenW / 10, screenW / 10,txLoadImage("WallDark.bmp")};

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
        txSleep(20);
        FGameOver (&GameOver,pers,enemy,screenH,screenW,GameOverPicBad, 500);

    }

    txDeleteDC(pers.pic);
    txDeleteDC(enemy.pic);
    txDeleteDC(GameOverPicBad);
    for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {
    txDeleteDC(dark[nomer_steny].pic);
    }

    return 0;
}

void FGameOver (bool* GameOver, Player pers, Player enemy, int screenH, int screenW, HDC GameOverPicBad, int finish){
    if (enemy.frame == 1){
        *GameOver = true;
        txBitBlt (txDC(), screenW/2-161, screenH/2-56, 382, 112, GameOverPicBad, 0, 0);
        txSleep(3000);

 }else if (pers.x == finish) {
    //*GameOver = true;
 }
}

/*условие выхода
Апгрейды менюшка
если видимая
если по у очень близки
разность игрок стена
*/
