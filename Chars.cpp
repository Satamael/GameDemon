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
HDC picchoose;
};
struct Wall {
    int x;
    int y;
    int length;
    int height;
    HDC pic;
};

struct UPs{
double inviseUp;
int SoulHuntUp;
int HPUp;
int AllyHPUp;
int Souls;
};


void NewWallPush(Player* pers,int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck);
void Wall_Push(int xWallD,int yWallD, int lengthWallD, int heightWallD, Player* pers, int screenW, int screenH);
void StelsPerson(Player* pers, Player ally, Player enemy, int screenW, int screenH);
bool stolknovenie(int x, int y, int dl, int shir, int x1, int y1, int dl1, int shir1);
void Enemy(Player* enemy,Player pers, Player ally, int screenW, int screenH);
void Ally(Player pers, Player enemy,Player enemy2, Player* ally, int screenW, int screenH);
void NewEnGo(Player* enemy, int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck);
void NewEnGo2(Player* enemy, int mapSizeX,int mapSizeY,int mapX,int mapY, HDC LevelCheck);
void killing(Player* pers, Player* enemy, int kills);

void StelsPerson(Player* pers, Player ally, Player enemy, Player enemy2, int screenW, int screenH)
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
        pers->frame = pers->frame + 0.1;
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
         pers->frame = FRAME_STOIT_ROVNO;
    }
}

void Enemy(Player pers, Player* enemy, Player enemy_old, Player ally, int screenW, int screenH) {


/*if(abs(enemy->x - pers.x) < 200 and abs(enemy->y - pers.y) < 200 or  (abs(enemy->x - pers.x)) < 200 and abs(enemy->y - pers.y)< 200){

    if (pers.x > enemy->x)
    {
        enemy->x = enemy->x + enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 3;
    }
    else if (pers.x < enemy->x)
    {
        enemy->x = enemy->x - enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 2;
    }

    if (pers.y > enemy->y)
    {
        enemy->y = enemy->y + enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 1;
    }
    else if (pers.y < enemy->y)
    {
        //enemy->y = enemy->y - enemy->speed;
        enemy->frame = enemy->frame + 0.1;
        enemy->direction = 0;
    }
    }else{*enemy= enemy_old;}
    */

    if (round(enemy->frame) > FRAME_KONEC_DVIZHENIA)
    {
         enemy->frame = FRAME_NACHALO_DVIZHENIA;
    }

    if (enemy->invise==false and abs(enemy->x - pers.x) < 70 and abs(enemy->y - pers.y) < 70 or  (abs(enemy->x - pers.x)) < 70 and abs(enemy->y - pers.y)< 70 and enemy->direction!=pers.direction)
    {
         enemy->frame = FRAME_WITH_KNIFE;
    }
    else if (round(enemy->frame) == FRAME_WITH_KNIFE)
    {
         enemy->frame = FRAME_NACHALO_DVIZHENIA;
    }




}

void Ally(Player pers, Player enemy,Player enemy2, Player* ally, int screenW, int screenH) {

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

    COLORREF leftColor   = txGetPixel((enemy->x-10)/10, (enemy->y)   /10);
    COLORREF upColor     = txGetPixel((enemy->x)   /10, (enemy->y-10)/10);
    COLORREF rightColor  = txGetPixel((enemy->x+10)/10, (enemy->y)   /10);
    COLORREF bottomColor = txGetPixel((enemy->x)   /10, (enemy->y+10)/10);


    const int UP = 0;
    const int BOTTOM = 1;
    const int LEFT = 2;
    const int RIGHT = 3;


    const int speed = enemy->speed;


    if (enemy->direction == LEFT) {

        if (leftColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x - speed;
            enemy->direction = LEFT;
            enemy->frame = enemy->frame + 0.1;
        } else if (upColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y - speed;
            enemy->direction = UP;
            enemy->frame = enemy->frame + 0.1;
        } else if (bottomColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y + speed;
            enemy->direction = BOTTOM;
            enemy->frame = enemy->frame + 0.1;
        }

    } else if (enemy->direction == RIGHT) {

        if (rightColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x + speed;
            enemy->direction = RIGHT;
            enemy->frame = enemy->frame + 0.1;
        } else if (upColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y - speed;
            enemy->direction = UP;
            enemy->frame = enemy->frame + 0.1;
        } else if (bottomColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y + speed;
            enemy->direction = BOTTOM;
            enemy->frame = enemy->frame + 0.1;
        }

    } else if (enemy->direction == BOTTOM) {

        if (bottomColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y + speed;
            enemy->direction = BOTTOM;
            enemy->frame = enemy->frame + 0.1;
        } else if (leftColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x - speed;
            enemy->direction = LEFT;
            enemy->frame = enemy->frame + 0.1;
        } else if (rightColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x + speed;
            enemy->direction = RIGHT;
            enemy->frame = enemy->frame + 0.1;
        }

    } else if (enemy->direction == UP) {

        if (upColor == RGB(237, 28, 36)) {
            enemy->y = enemy->y - speed;
            enemy->direction = UP;
            enemy->frame = enemy->frame + 0.1;
        } else if (leftColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x - speed;
            enemy->direction = LEFT;
            enemy->frame = enemy->frame + 0.1;
        } else if (rightColor == RGB(237, 28, 36)) {
            enemy->x = enemy->x + speed;
            enemy->direction = RIGHT;
            enemy->frame = enemy->frame + 0.1;
        }

    }
}

void killing(Player* pers, Player* enemy, int* kills){
    const int UP = 0;
    const int BOTTOM = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

 if(pers->direction==enemy->direction and (abs(enemy->x - pers->x) < 70 and abs(enemy->y - pers->y) < 70 or  (abs(enemy->x - pers->x)) < 70 and abs(enemy->y - pers->y)< 70)){
 if (enemy->direction==UP and enemy->y<=pers->y and pers->frame==FRAME_WITH_KNIFE and enemy->invise==false){
 enemy->invise= true;
 kills= kills+1;
 } else if (enemy->direction==BOTTOM and enemy->y>=pers->y and pers->frame==FRAME_WITH_KNIFE and enemy->invise==false){
 enemy->invise= true;
 kills= kills+1;
 } else if (enemy->direction==RIGHT and enemy->x>=pers->x and pers->frame==FRAME_WITH_KNIFE and enemy->invise==false){
 enemy->invise= true;
 kills= kills+1;
 }else if (enemy->direction==LEFT and enemy->x<=pers->x and pers->frame==FRAME_WITH_KNIFE and enemy->invise==false){
 enemy->invise= true;
 kills= kills+1;
 }

}
}

