#include <stdio.h>
#include <ncurses.h>
#include "variables.h"
#include "graphics.h"
#include "combat.h"
#include "logic.h"
#include "mainMenu.h"

int main()
{
    initscr();
    noecho();
    curs_set(0);
    start_color();

    int mainLoop = 1;
    int reverse = 0;
    int isNotMoving = 1;
    int isOnTitle = 1;
    int mapX = 1;
    int mapY = 1;
    unsigned int selected = 0;
    int key;
    FILE *f;

    enemy.life = 10;
    enemy.attack = 5;
    enemy.defense = 5;
    enemy.accuracy = 90;

    f = fopen("sapo.dat", "rb");
    PLAYER player;
    fread(&player, sizeof(PLAYER), 1, f);
    fclose(f);
    f = fopen("gomba.dat", "rb");
    fread(&goomba, sizeof(SPRITE), 1, f);
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

        drawPlayer(&player, player.x, player.y, reverse, !isNotMoving);
        refresh();
        playerMove(&key, &reverse, &isNotMoving, &isOnTitle, &player, world, &mapX, &mapY);

        if (player.life <= 0)
        {
            mainLoop = 0;
        }
    }

    clear();
    drawText("fim de jogo", 75 * 3, 10, 0);
    drawText("voce perdeu", 75 * 3, 20, 0);
    getch();

    endwin();
    return 0;
}