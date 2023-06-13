#include <stdio.h>
#include <ncurses.h>

void draw(unsigned short int sprite[3][16], int x, int y, int color[8], int invert)
{
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
                    if (invert)
                    {
                        move(y + j, x + (16 - k) * 2);
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

int main()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();

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

    draw(frame1, x, y, colors, reverse);
    while (foo)
    {
        int key = getch();
        if (key == 'w')
        {
            y--;
            clear();
        }
        if (key == 's')
        {
            y++;
            clear();
        }
        if (key == 'a')
        {
            x--;
            reverse = 1;
            clear();
        }
        if (key == 'd')
        {
            x++;
            reverse = 0;
            clear();
        }

        switch (state)
        {
        case 1:
        case 2:
        case 3:
            draw(frame1, x, y, cc, reverse);
            break;
        case 4:
        case 5:
        case 6:
            draw(frame2, x, y, colors, reverse);
            break;
        case 7:
        case 8:
        case 9:
            draw(frame3, x, y, colors, reverse);
            break;
        }
        state++;
        if (state == 10)
        {
            state = 1;
        }

        refresh();
    }

    endwin();
    return 0;
}