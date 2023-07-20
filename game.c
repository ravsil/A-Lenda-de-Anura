#include <stdio.h>
#include <ncurses.h>
#include "variables.h"
#include "graphics.h"
#include "logic.h"

int main()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();

    int mainLoop = 1;
    int x = 0;
    int y = 0;
    int reverse = 0;
    int isNotMoving = 1;
    int isOnTitle = 1;
    unsigned int selected = 0;
    int key;
    FILE *f;

    f = fopen("sapo.dat", "rb");
    PLAYER player;
    fread(&player, sizeof(PLAYER), 1, f);
    fclose(f);

    f = fopen("bloco.dat", "rb");
    SPRITE assets[1];
    fread(assets, sizeof(assets), 1, f);
    fclose(f);

    int world[7][14] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}};

    f = fopen("alfabeto.dat", "rb");
    fread(characters, sizeof(characters), 1, f);
    fclose(f);

    while (mainLoop)
    {
        titleScreen(&player, &key, &selected, &isOnTitle, &mainLoop);
        if (isOnTitle)
        {
            continue;
        }
        drawWorld(world, assets);
        drawPlayer(&player, x, y, reverse, !isNotMoving);
        refresh();
        playerMove(&key, &x, &y, &reverse, &isNotMoving);
    }

    endwin();
    return 0;
}