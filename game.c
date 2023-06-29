#include <stdio.h>
#include <ncurses.h>
#include "graphics.h"

/*
create color:
    short int mycolor = 29;
    init_color(mycolor, 999, 440, 550);
                         R    G    B
*/

int main()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();

    int mx, my;
    int x = 10;
    int y = 10;
    int reverse = 0;
    int foo = 1;
    int state = 1;
    int colors[] = {COLOR_RED, COLOR_GREEN, COLOR_YELLOW};
    int cc[] = {COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_MAGENTA};

    unsigned short int frame1[3][16] = {{1984, 16352, 0, 0, 0, 0, 0, 128, 1152, 1920, 2880, 4032, 8160, 7392, 0, 0}, {0, 0, 1248, 1104, 2256, 15408, 0, 1888, 15216, 30840, 4128, 0, 0, 0, 14448, 30840}, {0, 0, 2816, 15264, 30496, 960, 8128, 0, 0, 0, 25752, 28728, 24600, 0, 0, 0}};

    unsigned short int frame2[3][16] = {{1984, 16352, 0, 0, 0, 0, 0, 384, 896, 3712, 4064, 8176, 8184, 7280, 0, 0}, {0, 0, 1248, 1104, 2256, 15408, 0, 1656, 7288, 12384, 16384, 24576, 24576, 24588, 28, 56}, {0, 0, 2816, 15264, 30496, 960, 8128, 0, 57350, 49422, 6, 0, 0, 0, 0, 0}};

    unsigned short int frame3[3][16] = {{1984, 16352, 0, 0, 0, 0, 0, 128, 768, 3456, 7936, 7184, 3616, 448, 0, 0}, {0, 0, 1248, 1104, 2256, 15408, 0, 1888, 3312, 112, 240, 96, 64, 3584, 8128, 960}, {0, 0, 2816, 15264, 30496, 960, 8128, 0, 0, 4608, 0, 896, 384, 0, 0, 0}};

    draw(frame1, x, y, mx, my, colors, reverse);
    while (foo)
    {
        getmaxyx(stdscr, my, mx);
        my -= 16;
        mx -= 32;
        int key = getch();
        if (key == 'w')
        {
            if (isInBounds(y, my, -1))
            {
                y--;
            }
            else
            {
                y = my;
            }
        }
        if (key == 's')
        {
            if (isInBounds(y, my, 1))
            {
                y++;
            }
            else
            {
                y = 0;
            }
        }
        if (key == 'a')
        {
            if (isInBounds(x, mx, -1))
            {
                x--;
            }
            else
            {
                x = mx;
            }
            reverse = 1;
        }
        if (key == 'd')
        {
            if (isInBounds(x, mx, 1))
            {
                x++;
            }
            else
            {
                x = 0;
            }
            reverse = 0;
        }

        clear();
        switch (state)
        {
        case 1:
        case 2:
        case 3:
            draw(frame1, x, y, mx, my, cc, reverse);
            break;
        case 4:
        case 5:
        case 6:
            draw(frame2, x, y, mx, my, colors, reverse);
            break;
        case 7:
        case 8:
        case 9:
            draw(frame3, x, y, mx, my, colors, reverse);
            break;
        }

        if (x <= mx && x >= 0 && y <= my && y >= 0)
        {
            state++;
        }
        if (state == 10)
        {
            state = 1;
        }

        init_pair(14, COLOR_BLACK, COLOR_WHITE);
        attron(COLOR_PAIR(14));
        move(0, 0);
        printw("%d/%d %d/%d", x, mx, y, my);
        attroff(COLOR_PAIR(14));
        refresh();
    }

    endwin();
    return 0;
}