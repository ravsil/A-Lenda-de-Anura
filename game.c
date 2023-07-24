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
    int isMagic = 0;
    unsigned int selected = 0;
    int key;
    FILE *f;

    enemy.life = 10;
    enemy.maxLife = 10;
    enemy.attack = 5;
    enemy.defense = 5;
    enemy.accuracy = 90;

    f = fopen("bin/player.dat", "rb");
    PLAYER player;

    fread(&player, sizeof(PLAYER), 1, f);
    fclose(f);

    f = fopen("bin/assets.dat", "rb");
    fread(assets, sizeof(assets), 1, f);
    fclose(f);

    f = fopen("bin/characters.dat", "rb");
    fread(characters, sizeof(characters), 1, f);
    fclose(f);

    f = fopen("bin/screens.dat", "rb");
    fread(screens, sizeof(screens), 1, f);
    fclose(f);

    while (mainLoop)
    {
        titleScreen(&player, &key, &selected, &isOnTitle, &mainLoop);
        if (isOnTitle)
        {
            continue;
        }

        drawWorld(screens[player.curScreen].world);

        drawPlayer(&player, player.x, player.y, reverse, !isNotMoving + isMagic);
        refresh();
        playerMove(&key, &reverse, &isNotMoving, &isOnTitle, &player, screens[player.curScreen].world);

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