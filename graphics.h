#include <ncurses.h>

typedef struct _SPRITE
{
    unsigned long long int lines[16];
} SPRITE;

typedef struct _PLAYER
{
    SPRITE sprites[2];
} PLAYER;

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

void drawWorld(int world[7][14], SPRITE *assets)
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

void drawText(long long int *characters, char *string, int size, int x, int y)
{
    int index;
    int initialX = x;
    int first = 1;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!first && i % size == 0)
        {
            y += 8;
            x = initialX;
        }

        if (string[i] == ' ')
        {
            x += 8 * 2;
            continue;
        }

        if (string[i] >= 'a')
        {
            index = string[i] - 'a';
        }
        else if (string[i] >= '0')
        {
            index = string[i] - '0' + 26;
        }

        x += 16;
        drawLetter(characters[index], x, y);

        if (first)
        {
            first = 0;
        }
    }
}