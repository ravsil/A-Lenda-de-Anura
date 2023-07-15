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
    int xPixelCoord;
    int yPixelCoord;
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
                move(y + i, x + 32 - j * 2);
            }
            else
            {
                move(y + i, x + j * 2);
            }
            printw("  ");
            attroff(COLOR_PAIR(colorIndex));
        }
    }
}

void drawPlayer(PLAYER *player, int x, int y, int invert, int animationFrame)
{
    drawSprite(&player->sprites[animationFrame], x, y, invert);
}