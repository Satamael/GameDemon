    int nWallD = 16;
     srand(time(NULL));
     Wall dark[nWallD];


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

    void Wall_Push(int xWallD, int yWallD, int lengthWallD, int heightWallD, Player* pers, int screenW, int screenH)
{
    if (pers->x + 70 >= xWallD &&
        pers->x + 20 <= xWallD + lengthWallD &&
        pers->y + 70 >= yWallD &&
        pers->y + 20 <= yWallD + heightWallD)
    {
        pers->x = pers->x1;
        pers->y = pers->y1;
    }
}

for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {
        txDeleteDC(dark[nomer_steny].pic);
    }

bool stolknovenie(int x, int y, int dl, int shir, int x1, int y1, int dl1, int shir1) {

    bool stolkn_po_x = false;
    bool stolkn_po_y = false;
    bool stolkn = false;

    if (
        (x  <= x1           and x1          <= x + dl) or
        (x  <= x1 + dl1     and x1 + dl1    <= x + dl) or
        (x1 <= x            and x           <= x1 + dl1) or
        (x1 <= x + dl       and x + dl      <= x1 + dl1))
    {
        stolkn_po_x = true;
    }

    if (
        (y  <= y1           and y1          <= y + shir) or
        (y  <= y1 + shir1   and y1 + shir1  <= y + dl) or
        (y1 <= y            and y           <= y1 + shir1) or
        (y1 <= y + shir     and y + shir    <= y1 + shir1))
    {
        stolkn_po_y = true;
    }

    if (stolkn_po_x && stolkn_po_y)
    {
        stolkn = true;
    }

    return stolkn;

}
for (int nomer_steny = 0; nomer_steny < nWallD; nomer_steny++) {

            Wall_Push(
[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &pers, screenW, screenH);
            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &enemy, screenW, screenH);
            Wall_Push(dark[nomer_steny].x,  dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, &ally, screenW, screenH);
            txTransparentBlt(txDC(), dark[nomer_steny].x, dark[nomer_steny].y, dark[nomer_steny].length, dark[nomer_steny].height, dark[nomer_steny].pic, 0, 0, RGB(255 , 255, 255));
        }
