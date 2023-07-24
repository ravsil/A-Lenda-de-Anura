typedef struct _SPRITE
{
    unsigned long long int lines[16];
} SPRITE;

typedef struct _PLAYER
{
    SPRITE sprites[4];
    char name[9];
    int life;
    int maxLife;
    int attack;
    int defense;
    int mana;
    int magic;
    int potions;
    int xp;
    int lvl;
    int mapX;
    int mapY;
    int x;
    int y;
    int curScreen;
} PLAYER;

typedef struct _ENEMY
{
    int life;
    int maxLife;
    int attack;
    int defense;
    int accuracy;
} ENEMY;

typedef struct _GAME_SCREEN
{
    int world[7][14];
} GAME_SCREEN;

ENEMY enemy;
long long int characters[45];
SPRITE assets[4];
GAME_SCREEN screens[4];