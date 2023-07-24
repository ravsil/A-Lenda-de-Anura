#include <stdio.h>

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

typedef struct _SCREEN
{
    int world[7][14];
} GAME_SCREEN;

int main()
{
    FILE *file;
    PLAYER player;
    unsigned long long int sapoComumframe1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 600479914524672, 10508399076704256, 9593382117703680, 10508399130517504, 10208159173267968, 638009945182720, 10504894383740192};
    unsigned long long int sapoComumframe2[] = {73300705280, 300239975153664, 3449699827712, 900651204943872, 14410419278127104, 600484531544064, 56294995132416, 146584764416, 600411214061568, 9607605905400320, 14391718469317376, 14409173182919424, 14373988810699520, 18760435040256, 600333351002112, 9607532605743616};
    unsigned long long int sapoFrame1[] = {2336462209024, 38697655336960, 38620345925632, 39797703835648, 619245197066240, 636837114675200, 619249223598080, 153722867280904192, 2536427310135058432, 153722867280904192, 10508399076704256, 9593382117703680, 10508399130517504, 10208159173267968, 638009945182720, 10504894383740192};
    unsigned long long int sapoFrame2[] = {73300705280, 300239975153664, 3449699827712, 900651204943872, 14410419278127104, 600484531544064, 56294995132416, 146584764416, 600411214061568, 9607605905400320, 14391718469317376, 14409173182919424, 14373988810699520, 18760435040256, 600333351002112, 9607532605743616};
    player.name[0] = '\0';
    for (int i = 0; i < 16; i++)
    {
        player.sprites[0].lines[i] = sapoComumframe1[i];
        player.sprites[1].lines[i] = sapoComumframe2[i];
        player.sprites[2].lines[i] = sapoFrame1[i];
        player.sprites[3].lines[i] = sapoFrame2[i];
    }
    player.life = 10;
    player.maxLife = 10;
    player.attack = 5;
    player.defense = 5;
    player.mana = 20;
    player.magic = 5;
    player.potions = 1;
    player.xp = 0;
    player.lvl = 1;
    player.mapX = 1;
    player.mapY = 1;
    player.x = 0;
    player.y = 0;
    player.curScreen = 0;

    file = fopen("bin/player.dat", "wb");
    fwrite(&player, sizeof(PLAYER), 1, file);
    fclose(file);

    SPRITE assets[4];
    unsigned long long int grama[] = {7378697629500663398, 7378715221670913638, 7450773915219420774, 7383201229379626599, 7383201229127968358, 7378697698203297382, 8531619203078579814, 7378697633778787942, 7378979104460531302, 7451037798010087270, 7378715221938304870, 7378697698471736934, 7378697633778787942, 7378697629483820646, 7378697629483886439, 7378697629483824742};
    unsigned long long int agua[] = {9838263505978427528, 9838264674210580632, 9910321104328165512, 10995970085189360008, 9838282197944535192, 9838263578992937096, 9838263505978427528, 9842767105605798024, 9910620167180224648, 10991186110113683608, 9838263505978427784, 9838263506246862984, 9843048584894253192, 9838282266395646104, 9910321100016355720, 9838263505978427528};
    unsigned long long int poder[] = {0, 844425735440896, 13693353984, 175935600984064, 13511018244222976, 3547964899328, 56766871306240, 14532318494666752, 230714996204151600, 901191952445440, 3511726112768, 45088986019924480, 249913606304, 13690208256, 52789443035136, 0};
    unsigned long long int inimigo[] = {366498283520, 5864061665280, 93824992215040, 1501199875788800, 23121996524168448, 384286277478143312, 384286057579173200, 6148893731776124245, 6148895930801476949, 6148914691236517205, 384305995389949264, 75059993772032, 9645209201943040, 153723013880226336, 153722876407718432, 9607688331862528};
    for (int i = 0; i < 16; i++)
    {
        assets[0].lines[i] = grama[i];
        assets[1].lines[i] = agua[i];
        assets[2].lines[i] = poder[i];
        assets[3].lines[i] = inimigo[i];
    }
    file = fopen("bin/assets.dat", "wb");
    fwrite(&assets, sizeof(assets), 1, file);
    fclose(file);
    long long int characters[45] = {18857117230, 16694887983, 15603893806, 7836583207, 33320830015, 1108575295, 15625782830, 18842895921, 15170932878, 2320634015, 18833712689, 33320633377, 18842441585, 19115132465, 15621211694, 1108854319, 33073710638, 18842371631, 15620048430, 4433514655, 15621211697, 4648912433, 19182175793, 18834663985, 4433521201, 33321787935, 15621281582, 8867031432, 33357578798, 15619998254, 8867784012, 15620127807, 15621129774, 2216829471, 15621113390, 15620589102, 21898532002, 3472866531, 1143087376, 4299440686, 4299296900, 4294967296, 2285895680, 4572061956, 4364240964};

    file = fopen("bin/characters.dat", "wb");
    fwrite(characters, sizeof(characters), 1, file);
    fclose(file);

    GAME_SCREEN screen[4];
    int world1[98] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, -3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            screen[0].world[i][j] = world1[j + i * 14];
            screen[1].world[i][j] = 0;
            screen[2].world[i][j] = 0;
            screen[3].world[i][j] = 0;
        }
    }
    screen[0].world[2][13] = 23;
    screen[1].world[2][0] = 22;
    screen[1].world[3][3] = 3;
    file = fopen("bin/screens.dat", "wb");
    fwrite(screen, sizeof(screen), 1, file);
    fclose(file);

    return 0;
}