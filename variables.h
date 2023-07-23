typedef struct _SPRITE
{
    unsigned long long int lines[16];
} SPRITE;

typedef struct _PLAYER
{
    SPRITE sprites[2];
    char name[9];
    int life;
    int maxLife;
    int attack;
    int defense;
    int mana;
    int magic;
    int potions;
    int xp;
    int x;
    int y;
    int curScreen;
} PLAYER;

typedef struct _ENEMY
{
    int life;
    int attack;
    int defense;
    int accuracy;
} ENEMY;

ENEMY enemy;
SPRITE goomba;
long long int characters[39];