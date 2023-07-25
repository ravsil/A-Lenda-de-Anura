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
    int shouldPlay = 1;
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

        if (player.mana == 0 && player.xp == 0 && shouldPlay)
        {
            cutscene();
            shouldPlay = 0;
        }

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
        else if (player.lvl == -1)
        {
            mainLoop = 0;
            ending = 3;
        }
        else if (player.lvl == -2)
        {
            mainLoop = 0;
            ending = 4;
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
        drawText("voce perdeu seus poderes magicos", 15 * 3, 40, 0);
        drawText("e se tornou um sapo comum novamente", 15 * 3, 50, 0);
        break;
    case 3:
        drawText("fim de jogo", 75 * 3, 10, 0);
        drawText("a bruxa, utilizando sua varinha,", 15 * 3, 40, 0);
        drawText("lanca lhe um feitico fatal. e", 15 * 3, 50, 0);
        drawText("assim termina sua historia,", 15 * 3, 60, 0);
        drawText("pequeno sapo. talvez da proxima", 15 * 3, 70, 0);
        drawText("seja melhor ser mais educado.", 15 * 3, 80, 0);
        break;
    case 4:
        drawText("fim de jogo", 75 * 3, 10, 0);
        drawText("em seu coracao, se mantem a", 15 * 3, 30, 0);
        drawText("conviccao de que todos os humanos", 15 * 3, 40, 0);
        drawText("devem pagar pelos seus erros", 15 * 3, 50, 0);
        drawText("contra a natureza. esse foi so o", 15 * 3, 60, 0);
        drawText("primeiro passo de muitos que voce", 15 * 3, 70, 0);
        drawText("ainda iria dar na extincao de toda", 15 * 3, 80, 0);
        drawText("a humanidade.", 15 * 3, 100, 0);
        break;
    }

    getch();
    endwin();
    return 0;
}