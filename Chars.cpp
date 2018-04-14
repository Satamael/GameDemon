#include "TXLib.h"
#include "Constants.cpp"

struct Player {
    int x;
    int y;
    int pshir;
    int pdl;
    int speed;
    double frame;
    int direction;
    int hp;
    int mp;
    int dmg;
    int aspeed;
    bool invise;
    HDC pic;
    int x1;
    int y1;
};


struct menupics {
HDC picmenu;
HDC picautor;
HDC picprehis;
HDC pictypes;
HDC picpause;
HDC picupg;
};
struct Wall {
    int x;
    int y;
    int length;
    int height;
    HDC pic;
};
void NewWallPush(Player* pers,int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck);
void Wall_Push(int xWallD,int yWallD, int lengthWallD, int heightWallD, Player* pers, int screenW, int screenH);
void StelsPerson(Player* pers, Player ally, Player enemy, int screenW, int screenH);
bool stolknovenie(int x, int y, int dl, int shir, int x1, int y1, int dl1, int shir1);
void Enemy(Player* enemy,Player pers, Player ally, int screenW, int screenH);
void Ally(Player pers, Player enemy, Player* ally, int screenW, int screenH);
void NewEnGo(Player* enemy, int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck);


void StelsPerson(Player* pers, Player ally, Player enemy, int screenW, int screenH)
{
    if (GetAsyncKeyState('W') && (pers->y >= 0)) {
        pers->y = pers->y - pers->speed;
        pers->frame = pers->frame + 0.1;
        pers->direction = 0;
    } else if (GetAsyncKeyState('S') && (pers->y <= screenH - 70)) {
        pers->y = pers->y + pers->speed;
        pers->frame = pers->frame + 0.1;
        pers->direction = 1;
    }

    if (GetAsyncKeyState('A') && ( pers->x >= 0)){
        pers->x = pers->x-pers->speed;
        pers->frame = pers->frame + 0.1;
        pers->direction = 2;
    } else if (GetAsyncKeyState('D') && ( pers->x <= screenW - 70)){
        pers->x = pers->x+pers->speed;
        pers->frame = pers->frame + 0.1;  // ��� ��� �� ��
        pers->direction = 3;
    }


    if (round(pers->frame) > FRAME_KONEC_DVIZHENIA)
    {
         pers->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (GetAsyncKeyState(VK_SPACE))
    {
         pers->frame = FRAME_WITH_KNIFE;
    }
    else if (round(pers->frame) == FRAME_WITH_KNIFE)
    {
         pers->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (!GetAsyncKeyState(VK_SPACE) and
        !GetAsyncKeyState('W')      and
        !GetAsyncKeyState('S')      and
        !GetAsyncKeyState('A')      and
        !GetAsyncKeyState('D')
       )
    {
         pers->frame = FRAME_STOIT_ROVNO; // �� ������ ����� �����
    }
}

void Enemy(Player pers, Player* enemy, Player ally, int screenW, int screenH) {


    if (pers.x > enemy->x)
    {
        //enemy->x = enemy->x + enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 3;
    }
    else if (pers.x < enemy->x)
    {
        //enemy->x = enemy->x - enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 2;
    }

    if (pers.y > enemy->y)
    {
        //enemy->y = enemy->y + enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 1;
    }
    else if (pers.y < enemy->y)
    {
        //enemy->y = enemy->y - enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 0;
    }


    txSetColor(TX_YELLOW);
    char health_string[100];
    sprintf(health_string, "%d  %d %d  %d", enemy->x, pers.x, enemy->y, pers.y);
    txTextOut(300, 750, health_string);

    if (round(enemy->frame) > FRAME_KONEC_DVIZHENIA)
    {
         enemy->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (abs(enemy->x - pers.x) < 70 and abs(enemy->y - pers.y) < 70)
    {
         enemy->frame = FRAME_WITH_KNIFE;
    }
    else if (round(enemy->frame) == FRAME_WITH_KNIFE)
    {
         enemy->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (enemy-> x == enemy->x1 and enemy->y == enemy->y1)
    {
         //enemy->frame = FRAME_STOIT_ROVNO; // �� ������ ����� �����
    }
}

void Ally(Player pers, Player enemy, Player* ally, int screenW, int screenH) {

    if (ally->x + ally->speed*5 < pers.x)
    {
        ally->x = ally->x + ally->speed;
        ally->frame = ally->frame + 0.1;
        ally->direction = 3;
    }
    else if (pers.x < ally->x - ally->speed*5)
    {
        ally->x = ally->x - ally->speed;
        ally->frame = ally->frame + 0.1;
        ally->direction = 2;
    }

    if (pers.y > ally->y + ally->speed*5)
    {
        ally->y = ally->y + ally->speed;
        ally->frame = ally->frame + 0.1;
        ally->direction = 1;
    }
    else if (pers.y < ally->y - ally->speed*5)
    {
        ally->y = ally->y - ally->speed;
        ally->frame = ally->frame + 0.1;
        ally->direction = 0;
    }


    if (round(ally->frame) > FRAME_KONEC_DVIZHENIA)
    {
         ally->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (abs(ally->x - pers.x) < 70 and abs(ally->y - pers.y) < 70)
    {
         ally->frame = FRAME_STOIT_ROVNO;
    }
    else if (round(ally->frame) == FRAME_STOIT_ROVNO)
    {
         ally->frame = FRAME_NACHALO_DVIZHENIA;
    }


}
void NewWallPush(Player* pers, int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck){

    txBitBlt(txDC(), 0, 0, mapSizeX/10, mapSizeY/10, LevelCheck, 0, 0);

    txSetColor(TX_YELLOW);
    char health_string[100];
    sprintf(health_string, "%d %d", pers->x/10 + 2, pers->y/10 + 2);
    txTextOut(200, 800, health_string);
    //txSleep(1000);
    for (int x_iz_cikla = pers->x/10 + 2; x_iz_cikla <= pers->x/10 + pers->pshir/10 - 4; x_iz_cikla++)
    {
        for (int y_iz_cikla = pers->y/10 + 2; y_iz_cikla <= pers->y/10 + pers->pdl/10 - 4; y_iz_cikla++)
        {
            if (txGetPixel(x_iz_cikla, y_iz_cikla) == TX_BLACK) {
                pers->x = pers->x1;
                pers->y = pers->y1;
            }
        }
    }
} // YYYYYYYYYYYY
void NewEnGo(Player* enemy, int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck){
    txBitBlt(txDC(), 0, 0, mapSizeX/10, mapSizeY/10, LevelCheck, 0, 0);
    COLORREF CheckEnX = txGetPixel((enemy->x-1)/10, (enemy->y)/10);
    COLORREF CheckEnY = txGetPixel((enemy->x)/10, (enemy->y-1)/10);
    COLORREF CheckEnX1 = txGetPixel((enemy->x+1)/10, (enemy->y)/10);
    COLORREF CheckEnY1 = txGetPixel((enemy->x)/10, (enemy->y+1)/10);

    if (CheckEnX == RGB(237, 28, 36)){
        enemy->x=enemy->x-1;
        enemy->direction=2;
        enemy->frame=enemy->frame+0.1;
    }


    else if(CheckEnY == RGB(237, 28, 36)){
        enemy->y=enemy->y-1;
         enemy->direction=0;
         enemy->frame=enemy->frame+0.1;
    }


     else if(CheckEnX1 == RGB(237, 28, 36)){
        enemy->x=enemy->x+1;
         enemy->direction=3;
         enemy->frame=enemy->frame+0.1;
    }


     else if(CheckEnY1 == RGB(237, 28, 36) && CheckEnX1 != RGB(237, 28, 36)){
        enemy->y=enemy->y+1;
         enemy->direction=1;
         enemy->frame=enemy->frame+0.1;
    }

if (enemy->direction==2 && CheckEnX == RGB(237, 28, 36)){
        enemy->x=enemy->x-1;
         //enemy->direction=2;
         enemy->frame=enemy->frame+0.1;
} else if (enemy->direction==2 && CheckEnY == RGB(237, 28, 36)){
        enemy->y=enemy->y-1;
         enemy->direction=0;
         enemy->frame=enemy->frame+0.1;
}

 if (enemy->direction==0 && CheckEnY == RGB(237, 28, 36) && CheckEnX1 != RGB(237, 28, 36)){
        enemy->y=enemy->y-1;
         //enemy->direction=0;
         enemy->frame=enemy->frame+0.1;
} else if (enemy->direction==0 && CheckEnX1 == RGB(237, 28, 36)){
        enemy->x=enemy->x+1;
         enemy->direction=3;
         enemy->frame=enemy->frame+0.1;
}

if (enemy->direction==3 && CheckEnX1 == RGB(237, 28, 36)){
        enemy->x=enemy->x+1;
         //enemy->direction=3;
         enemy->frame=enemy->frame+0.1;
} else if (enemy->direction==3 && CheckEnY1 == RGB(237, 28, 36) && CheckEnX1 != RGB(237, 28, 36) ){
        enemy->y=enemy->y+1;
         enemy->direction=1;
         enemy->frame=enemy->frame+0.1;

}

if (enemy->direction==1 && CheckEnY1 == RGB(237, 28, 36)){
        enemy->y=enemy->y+1;
         //enemy->direction=1;
         enemy->frame=enemy->frame+0.1;
} else if (enemy->direction==1 && CheckEnX == RGB(237, 28, 36)){
        enemy->y=enemy->x-1;
         enemy->direction=2;
         enemy->frame=enemy->frame+0.1;
}

 if (enemy->direction==2 && CheckEnX == RGB(237, 28, 36)){
        enemy->x=enemy->x-1;
         //enemy->direction=2;
         enemy->frame=enemy->frame+0.1;
} else if (enemy->direction==2 && CheckEnY == RGB(237, 28, 36)){
        enemy->y=enemy->y-1;
         enemy->direction=0;
         enemy->frame=enemy->frame+0.1;
}

}
