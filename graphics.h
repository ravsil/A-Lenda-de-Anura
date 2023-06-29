#include <ncurses.h>

int isInBounds(int coord, int maxCoord, int way)
{
    if (coord + way < 0)
    {
        return 0;
    }
    else if (coord + way > maxCoord)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void draw(unsigned short int sprite[3][16], int x, int y, int mx, int my, int color[3], int invert)
{
    int xPixelCoord;
    int yPixelCoord;

    for (int i = 0; i < 3; i++)
    {
        init_pair(i + 1, color[i], color[i]);
        attron(COLOR_PAIR(i + 1));

        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                if (sprite[i][j] & (1 << k))
                {
                    yPixelCoord = x + (16 - k) * 2;
                    xPixelCoord = y + j;
                    if (!isInBounds(yPixelCoord - 1 + 8, my, 1))
                    {
                        yPixelCoord = 0 + j;
                    }
                    else if (!isInBounds(yPixelCoord + 1 + 8, my, -1))
                    {
                        yPixelCoord = my + j;
                    }
                    if (invert)
                    {
                        move(yPixelCoord, xPixelCoord);
                    }
                    else
                    {
                        move(y + j, x + k * 2);
                    }
                    printw("  ");
                }
            }
        }
        attroff(COLOR_PAIR(i + 1));
    }
}