#include <stdio.h>
#include <ncurses.h>
#include "logic.h"
#include "graphics.h"

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

    f = fopen("bloco.dat", "rb");
    SPRITE assets[1];
    fread(assets, sizeof(assets), 1, f);
    fclose(f);

    int world[7][14] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}};

    f = fopen("alfabeto.dat", "rb");
    long long int characters[36];
    fread(characters, sizeof(characters), 1, f);
    fclose(f);

    drawText(characters, "jogo do sapo mago brabo", 30, 40 * 3, 10);
    drawText(characters, "iniciar", 30, 80 * 3, 60);
    drawText(characters, "creditos", 30, 80 * 3, 70);
    drawText(characters, "controles", 30, 80 * 3, 80);
    getch();
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