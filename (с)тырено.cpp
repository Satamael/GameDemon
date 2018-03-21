
#include "TXLib.h"
#include "consmenu.cpp"
#include "Bomzh.cpp"
#include <iostream>
#include <string>

struct Point
{
    int x, y;
    int x1, y1;
    int x2, y2;
    int nomerPoint;
};

void moveDirector(Director *d, Point* p, int radius)
{
    int predX = d->x;
    int predY = d->y;
    int maxCountOfFrames = 4;

    if((d->x - p->x2) * (d->x - p->x2) + (d->y - p->y2) * (d->y - p->y2) <= radius * radius)	//Попали в зону видимости
    {
        p->nomerPoint = 2;
    }
    else if( abs(p->x - d->x) < 10 && abs(p->y - d->y) < 10)	//Разворот
    {
        p->nomerPoint = 1;
    }
    else if( abs(p->x1 - d->x) < 10 && abs(p->y1 - d->y) < 10)	//Разворот
    {
        p->nomerPoint = 0;
    }
    else if ((d->x - p->x2) * (d->x - p->x2) + (d->y - p->y2) * (d->y - p->y2) > radius * radius && p->nomerPoint == 2)	//Только что вышли из зоны видимости
    {
        p->nomerPoint = 0;
    }

    //В зависимости от цели, движемся в ту или другую точку
    int x, y;
    if (p->nomerPoint == 0)
    {
        x = p->x;
        y = p->y;
    }
    else if(p->nomerPoint == 1)
    {
        x = p->x1;
        y = p->y1;
    }
    else if(p->nomerPoint == 2)
    {
        x = p->x2;
        y = p->y2;
    }

    //Движение по направлению к цели
    if(d->y < y - d->speed)
    {
        d->y = d->y + d->speed;
        d->direction = DIRECTION_DOWN;
    }
    else if(d->y > y + d->speed){
        d->y = d->y - d->speed;
        d->direction = DIRECTION_UP;
    }
    if(d->x < x - d->speed)
    {
        d->x = d->x + d->speed;
        d->direction = DIRECTION_RIGHT;
    } else if(d->x > x + d->speed){
        d->x = d->x - d->speed;
        d->direction = DIRECTION_LEFT;
    }
}