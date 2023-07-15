#include <stdio.h>
#include <ncurses.h>
#include "graphics.h"
#include "logic.h"

int main()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();

    int x = 10;
    int y = 10;
    int reverse = 0;
    int mainLoop = 1;
    int isNotMoving = 1;
    int key;
    int calls = 0;
    FILE *f;
    f = fopen("sapo.dat", "rb");

    PLAYER player;
    fread(&player, sizeof(PLAYER), 1, f);
    fclose(f);

    while (mainLoop)
    {
        drawPlayer(&player, x, y, reverse, isNotMoving);
        refresh();
        playerMove(key, &x, &y, &reverse, &isNotMoving);
        clear();
        refresh();
    }

    endwin();
    return 0;
}
