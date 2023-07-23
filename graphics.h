#include <ncurses.h>
#include <time.h>
#include <string.h>

void drawSprite(SPRITE *sprite, int x, int y, int invert)
{
    unsigned long long int seven = 7;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int colorIndex = (sprite->lines[i] & (seven << j * 4)) >> j * 4;
            if (colorIndex == 0)
            {
                continue;
            }
            init_pair(colorIndex, colorIndex, colorIndex);
            attron(COLOR_PAIR(colorIndex));
            if (invert)
            {
                move(y + i, x + 46 - j * 3);
            }
            else
            {
                move(y + i, x + j * 3);
            }
            printw("   ");
            attroff(COLOR_PAIR(colorIndex));
        }
    }
}

void drawPlayer(PLAYER *player, int x, int y, int invert, int animationFrame)
{
    drawSprite(&player->sprites[animationFrame], x, y, invert);
}

void drawWorld(int world[7][14])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            drawSprite(&assets[world[i][j]], j * 16 * 3, i * 16, 0);
        }
    }
}

void drawLetter(long long int character, int x, int y)
{
    init_pair(20, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(20));
    long long int comparator = 1;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (character & (comparator << (i * 5 + j)))
            {
                move(y + i, x + j * 3);
                printw("   ");
            }
        }
    }
    attroff(COLOR_PAIR(20));
}

void drawText(char *string, int x, int y, int animate)
{
    int index;
    int initialX = x;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '\n')
        {
            y += 8;
            x = initialX;
            continue;
        }
        else if (string[i] == ' ')
        {
            x += 8 * 2;
            continue;
        }
        else if (string[i] >= 'a')
        {
            index = string[i] - 'a';
        }
        else if (string[i] >= '0')
        {
            index = string[i] - '0' + 26;
        }
        else if (string[i] == '/')
        {
            index = 38;
        }

        x += 16;
        drawLetter(characters[index], x, y);
        refresh();
        if (animate)
        {
            struct timespec delay;
            delay.tv_sec = 0;
            delay.tv_nsec = 1000000000 / 30;
            nanosleep(&delay, NULL);
        }
    }
}

void drawBox(int x0, int y0, int x, int y)
{
    init_pair(21, 13, 13);
    attron(COLOR_PAIR(21));
    for (int i = y0; i < y; i++)
    {
        for (int j = x0; j < x; j++)
        {
            move(y0 + i, x0 + j * 3);
            printw("   ");
        }
    }
    attroff(COLOR_PAIR(21));
}

void drawBattleInfo(PLAYER *player, ENEMY *enemy)
{
    drawBox(25, 0, 185, 17);
    char playerInfo[30];
    char enemyInfo[30];
    char life[5];
    char maxLife[5];

    playerInfo[0] = '\0';

    snprintf(life, 5, "%d", player->life);
    snprintf(maxLife, 5, "%d", player->maxLife);
    strcat(playerInfo, player->name);
    strcat(playerInfo, " ");
    strcat(playerInfo, life);
    strcat(playerInfo, "/");
    strcat(playerInfo, maxLife);
    drawText(playerInfo, 30 * 3, 5, 0);

    enemyInfo[0] = '\0';

    snprintf(life, 5, "%d", enemy->life);
    snprintf(maxLife, 5, "%d", enemy->maxLife);
    strcat(enemyInfo, "inimigo");
    strcat(enemyInfo, " ");
    strcat(enemyInfo, life);
    strcat(enemyInfo, "/");
    strcat(enemyInfo, maxLife);
    drawText(enemyInfo, 115 * 3, 5, 0);
}

void magicAnimation(PLAYER *player, ENEMY *enemy)
{
    for (int i = 0; i < 5; i++)
    {
        clear();
        drawBattleInfo(player, enemy);
        drawSprite(&player->sprites[0], 45 * 3, 30, 0);
        drawSprite(&goomba, 150 * 3, 30, 1);
        drawBox(10, 40, 210, 87);
        drawSprite(&assets[2], 65 * 3 + 48 * i, 30, 0);
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 1000000000 / 10;
        refresh();
        nanosleep(&delay, NULL);
    }

    clear();
    drawBattleInfo(player, enemy);
    drawSprite(&player->sprites[0], 45 * 3, 30, 0);
    drawSprite(&goomba, 150 * 3, 30, 1);
}