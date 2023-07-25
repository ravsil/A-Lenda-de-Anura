#include <ncurses.h>
#include <time.h>
#include <string.h>

void drawSprite(SPRITE *sprite, int x, int y, int invert)
{
    unsigned long long int fifteen = 15;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int colorIndex = (sprite->lines[i] & (fifteen << j * 4)) >> j * 4;
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
    int index;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (world[i][j] > 20)
            {
                switch (world[i][j])
                {
                case 22:
                    index = 0;
                    break;
                case 27:
                    index = 7;
                    break;
                case 28:
                    index = 8;
                    break;
                case 25:
                    index = 5;
                    break;
                }
            }
            else
            {
                index = world[i][j];
            }
            drawSprite(&assets[index], j * 16 * 3, i * 16, 0);
        }
    }
}

void drawLetter(long long int character, int x, int y)
{
    init_pair(20, 2, 2);
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
        else if (string[i] >= 'a' && string[i] <= 'z')
        {
            index = string[i] - 'a';
        }
        else if (string[i] >= '0' && string[i] <= '9')
        {
            index = string[i] - '0' + 26;
        }
        else
        {
            switch (string[i])
            {
            case '/':
                index = 38;
                break;
            case '?':
                index = 39;
                break;
            case '!':
                index = 40;
                break;
            case '.':
                index = 41;
                break;
            case ',':
                index = 42;
                break;
            case ')':
                index = 43;
                break;
            case '(':
                index = 44;
                break;
            }
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

void magicAnimation(PLAYER *player, ENEMY *enemy, int miss)
{
    for (int i = 0; i < 5; i++)
    {
        clear();
        drawBattleInfo(player, enemy);
        drawSprite(&player->sprites[2], 45 * 3, 30, 0);
        if (enemy->maxLife == 50)
        {
            drawSprite(&assets[10], 150 * 3, 20, 0);
            drawSprite(&assets[9], 150 * 3, 36, 0);
        }
        else
        {

            drawSprite(&assets[3], 150 * 3, 30, 1);
        }
        drawBox(10, 40, 210, 87);
        drawSprite(&assets[2], 65 * 3 + 48 * i, 30 + (miss * i * 5), 0);
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 1000000000 / 10;
        refresh();
        nanosleep(&delay, NULL);
    }

    clear();
    drawBattleInfo(player, enemy);
    drawSprite(&player->sprites[2], 45 * 3, 30, 0);
    if (enemy->maxLife == 50)
    {
        drawSprite(&assets[10], 150 * 3, 20, 0);
        drawSprite(&assets[9], 150 * 3, 36, 0);
    }
    else
    {

        drawSprite(&assets[3], 150 * 3, 30, 1);
    }
}

void cutscene()
{
    drawBox(10, 40, 210, 87);
    drawText("voce acorda no meio de um pantano,", 10 * 3, 90, 1);
    drawText("e o lugar lhe parece familiar.", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("o ar puro do lamacal te enche de", 10 * 3, 90, 1);
    drawText("determinacao. apos um longo coaxar,", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("voce chega a conclusao que todos", 10 * 3, 90, 1);
    drawText("os lugares deveriam ser pantanos. na", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("verdade, todos os seres deveriam ser", 10 * 3, 90, 1);
    drawText("sapos. voce sente que assim,e somente", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("assim, o mundo se tornaria um lugar", 10 * 3, 90, 1);
    drawText("melhor, haveria menos degradacao", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("ambiental, e mais respeito e cuidado", 10 * 3, 90, 1);
    drawText("com a natureza... O ecofascismo lhe", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("parece uma boa alternativa!", 10 * 3, 90, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("com isso em mente, voce, ate", 10 * 3, 90, 1);
    drawText("entao um simples sapo cururu, decide", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("dar inicio a sua jornada de", 10 * 3, 90, 1);
    drawText("dominacao mundial. visando, e claro. a", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("aniquilacao da raca humana e de todos", 10 * 3, 90, 1);
    drawText("os nao sapos. isso sim que e vida", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("boa...", 10 * 3, 90, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("va ate a bruxa que se encontra", 10 * 3, 90, 1);
    drawText("na floresta, apos o lago, talvez", 10 * 3, 100, 1);
    getch();
    drawBox(10, 40, 210, 87);
    drawText("ela possa te indicar um caminho.", 10 * 3, 90, 1);
    getch();
}

int cutscene2()
{
    drawBox(10, 40, 210, 87);
    drawText("ola pequena criaturinha, o que te", 10 * 3, 90, 1);
    drawText("tras aqui?", 10 * 3, 100, 1);
    getch();
    int choosing = 1;
    int selected = 0;
    int key;
    while (choosing)
    {
        drawBox(10, 40, 210, 87);
        drawText(" me arruma algo...", 10 * 3, 90, 0);
        drawText(" preciso de sua ajuda", 10 * 3, 100, 0);
        drawLetter(characters[37], 14 * 3, 90 + 10 * (selected % 2));
        key = getch();
        switch (key)
        {
        case 'j':
            choosing = 0;
            break;
        case 'w':
        case 's':
            selected = !selected;
            break;
        }
    }
    if (!selected)
    {
        drawBox(10, 40, 210, 87);
        drawText("arruma um plano maligno ai pra mim", 10 * 3, 90, 1);
        getch();
        drawBox(10, 40, 210, 87);
        drawText("que petulancia!", 10 * 3, 90, 1);
        getch();
        return 0;
    }
    else
    {
        drawBox(10, 40, 210, 87);
        drawText("senhora bruxa, boa tarde. preciso", 10 * 3, 90, 1);
        drawText("de ajuda para bolar um plano", 10 * 3, 100, 1);
        getch();
        drawBox(10, 40, 210, 87);
        drawText("maligno contra a humanidade", 10 * 3, 90, 1);
        getch();
        return 1;
    }
}

void cutscene3()
{
    drawBox(10, 40, 210, 87);
    drawText("jesus, maria e jose, um sapo", 10 * 3, 90, 0);
    drawText("magico", 10 * 3, 100, 0);
    getch();
}