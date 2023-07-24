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
    int ending = 0;
    FILE *f;

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

        if (player.mana > 0)
        {
            isMagic = 2;
        }

        if (player.life <= 0)
        {
            mainLoop = 0;
            ending = 1;
        }
        else if (player.mana < 0)
        {
            mainLoop = 0;
            ending = 2;
        }
    }

    clear();
    switch (ending)
    {
    case 1:
        drawText("fim de jogo", 75 * 3, 10, 0);
        drawText("voce morreu", 75 * 3, 40, 0);
        break;
    case 2:
        drawText("fim de jogo", 75 * 3, 10, 0);
        drawText("voce perdeu seus poderes magicos", 20 * 3, 40, 0);
        drawText("e se tornou um sapo comum novamente", 15 * 3, 50, 0);
        break;
    }

    getch();
    endwin();
    return 0;
}