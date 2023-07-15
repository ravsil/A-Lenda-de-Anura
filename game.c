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

    int x = 0;
    int y = 0;
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

    fopen("bloco.dat", "rb");
    SPRITE assets[1];
    fread(assets, sizeof(assets), 1, f);

    int world[7][14] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}};

    while (mainLoop)
    {
        drawWorld(world, assets);
        drawPlayer(&player, x, y, reverse, !isNotMoving);
        refresh();
        playerMove(&key, &x, &y, &reverse, &isNotMoving);
    }

    endwin();
    return 0;
}
