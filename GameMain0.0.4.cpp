#include "TXLib.h"
#include "Chars.cpp"
#include "�onstants.cpp"
 void FGameOver (bool GameOver, Player pers, Player enemy, int screenH, int screenW, HDC GameOverPic);

int main()
{

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    bool GameOver = false;
    txCreateWindow(screenW, screenH);
    HDC GameOverPic = txLoadImage("GameOver.bmp");
    srand(time(NULL));

    int nWallD = 16;
    Player pers = {100, 100,116,117, 5, 2, 0, 100, 100, 10, 5, 1, txLoadImage("Stels pers.bmp")};
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



    while (!GameOver)
    {
        txSetColor(TX_BLACK);
        txClear();
        txBegin();

        pers.x1 = pers.x;
        pers.y1 = pers.y;
        enemy.x1 = enemy.x;
        enemy.y1 = enemy.y;

        StelsPerson(&pers, screenW, screenH);
        Enemy(pers, &enemy, screenW, screenH);

        char health_string[100];
        sprintf(health_string, "�������� %d ���������� %d %d  ����� %d  %d", pers.hp, pers.x, pers.y, screenW, screenH);
        txTextOut(screenW-500, screenH-100, health_string);

        txTransparentBlt(txDC(), pers.x, pers.y, pers.pdl, pers.pshir, pers.pic, pers.pdl * round(pers.frame), pers.pshir * pers.direction, RGB(255 , 255, 255));
        txTransparentBlt(txDC(), enemy.x, enemy.y, enemy.pdl, enemy.pshir, enemy.pic, enemy.pdl * round(enemy.frame), enemy.pshir * enemy.direction, RGB(255 , 255, 255));


        for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {

            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &pers, screenW, screenH);
            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &enemy, screenW, screenH);
            txTransparentBlt(txDC(), dark[nomer_steny].x, dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, dark[nomer_steny].pic, 0, 0, RGB(255 , 255, 255));
        }

        txEnd();
        txSleep(20);
        FGameOver (GameOver,pers,enemy,screenH,screenW,GameOverPic);
    }

    txDeleteDC(pers.pic);
    txDeleteDC(enemy.pic);
    txDeleteDC(GameOverPic);
    for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {
        txDeleteDC(dark[nomer_steny].pic);
    }

    return 0;
}

void FGameOver (bool GameOver, Player pers, Player enemy, int screenH, int screenW, HDC GameOverPic){
    if (enemy.frame == 1){
        bool GameOver = true;
        txBitBlt (txDC(), 0, 0, 382, 112, GameOverPic, screenH/2, screenW/2);
        txSleep(3000);

 }
}

/*������� ������
�������� �������
���� �������
���� �� � ����� ������
�������� ����� �����
*/
