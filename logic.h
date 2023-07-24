#include <ncurses.h>
#include <time.h>
#include <string.h>

void status(PLAYER *player)
{
    clear();
    char life[10];
    char maxLife[10];
    char attack[10];
    char defense[10];
    char mana[10];
    char magic[10];

    snprintf(life, 10, "%d", player->life);
    snprintf(maxLife, 10, "%d", player->maxLife);
    snprintf(attack, 10, "%d", player->attack);
    snprintf(defense, 10, "%d", player->defense);
    snprintf(mana, 10, "%d", player->mana);
    snprintf(magic, 10, "%d", player->magic);
    strcat(life, "/");
    strcat(life, maxLife);

    drawText(player->name, 40 * 3, 20, 0);
    drawText("vida", 40 * 3, 30, 0);
    drawText(life, 75 * 3, 30, 0);
    drawText("ataque", 40 * 3, 40, 0);
    drawText(attack, 80 * 3, 40, 0);
    drawText("defesa", 40 * 3, 50, 0);
    drawText(defense, 80 * 3, 50, 0);
    drawText("mana", 40 * 3, 60, 0);
    drawText(mana, 80 * 3, 60, 0);
    drawText("magia", 40 * 3, 70, 0);
    drawText(magic, 80 * 3, 70, 0);
    drawText("pressione qualquer tecla\n     para retornar", 40 * 3, 90, 0);
    getch();
}

void save(PLAYER *player)
{
    FILE *f;
    f = fopen("bin/playerData.dat", "wb");
    fwrite(player, sizeof(PLAYER), 1, f);
    fclose(f);
    clear();
    drawText("jogo salvo com sucesso", 50 * 3, 10, 0);
    getch();
}

void menu(int *isOnTitle, PLAYER *player)
{
    int isOnMenu = 1;
    int key;
    unsigned int selected = 0;

    while (isOnMenu)
    {
        drawBox(100, 10, 150, 60);
        drawText("status", 140 * 3, 25, 0);
        drawText("item", 140 * 3, 35, 0);
        drawText("salvar", 140 * 3, 45, 0);
        drawText("inicio", 140 * 3, 55, 0);
        drawLetter(characters[37], 138 * 3, 25 + (selected % 4 * 10));

        key = getch();
        switch (key)
        {
        case 'j':
            if (selected % 4 == 0)
            {
                status(player);
            }
            else if (selected % 4 == 1)
            {
                // item();
            }
            else if (selected % 4 == 2)
            {
                save(player);
            }
            else
            {
                *isOnTitle = 1;
            }
        case 'k':
            isOnMenu = 0;
            break;
        case 'w':
            selected--;
            break;
        case 's':
            selected++;
            break;
        }
    }
}

void seekNewPos(PLAYER *player)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (screens[player->curScreen].world[i][j] == 22 || screens[player->curScreen].world[i][j] == 23)
            {
                player->mapX = j + 1;
                player->mapY = i + 1;
                player->x = 16 * 3 * j;
                player->y = 16 * i;
                return;
            }
        }
    }
}

void distributeStats(PLAYER *player)
{
    player->mana = 20;
    int totalStats = 5;
    int distributing = 1;
    int key;
    unsigned int selected = 0;
    int stats[] = {0, 0, 0, 0};
    while (distributing)
    {
        clear();
        drawText("distribua suas habilidades", 10 * 3, 20, 0);
        drawText("vida    1", 10 * 3, 30, 0);
        drawText("ataque ", 10 * 3, 40, 0);
        drawText("defesa ", 10 * 3, 50, 0);
        drawText("magia  ", 10 * 3, 60, 0);
        drawLetter(characters[26 + stats[0]], 63 * 3, 30);
        drawLetter(characters[30 + stats[1]], 62 * 3, 40);
        drawLetter(characters[30 + stats[2]], 62 * 3, 50);
        drawLetter(characters[30 + stats[3]], 62 * 3, 60);
        drawLetter(characters[37], 52 * 3, 30 + (selected * 10));
        drawText("pontos disponiveis ", 10 * 3, 70, 0);
        drawLetter(characters[26 + totalStats], 117 * 3, 70);

        if (totalStats == 0)
        {
            drawText("pressione j para confirmar", 10 * 3, 90, 0);
        }

        key = getch();

        switch (key)
        {
        case 'j':
            if (totalStats == 0)
            {
                distributing = 0;
            }
            break;
        case 'w':
            selected = (selected == 0) ? 3 : selected - 1;
            break;
        case 's':
            selected = (selected == 3) ? 0 : selected + 1;
            break;
        case 'a':
            if (stats[selected] != 0)
            {
                stats[selected] -= 1;
                totalStats++;
            }
            break;
        case 'd':
            if (totalStats > 0)
            {
                stats[selected] += 1;
                totalStats--;
            }
        }

        player->life = 10 + stats[0];
        player->attack = 5 + stats[1];
        player->defense = 5 + stats[2];
        player->magic = 5 + stats[3];
    }
}

int canMove(int world[7][14], int x, int y, int direction, PLAYER *player, int *isNotMoving, int reverse)
{
    int canBattle = !*isNotMoving;
    switch (direction)
    {
    // >
    case 1:
        x++;
        break;
    // v
    case 2:
        y++;
        break;
    // <
    case 3:
        x--;
        break;
    // ^
    case 4:
        y--;
        break;
    }

    if (x == 0 || y == 0 || x == 15 || y == 8)
    {
        return 0;
    }
    else if (world[y - 1][x - 1] != 1)
    {
        if (diceRoll(25) && canBattle && player->curScreen >= 2)
        {
            fight(player, diceRoll(50), "uma cobra selvagem apareceu", 35);
        }

        switch (world[y - 1][x - 1])
        {
        case 21:
            cutscene();
            distributeStats(player);
            world[y - 1][x - 1] = 0;
            switch (direction)
            {
            case 1:
                player->x -= 8 * 3;
                player->mapX -= 1;
                break;
            case 2:
                player->y -= 8;
                player->mapY -= 1;
                break;
            case 3:
                player->x += 8 * 3;
                player->mapX += 1;
                break;
            case 4:
                player->y += 8;
                player->mapY += 1;
                break;
            }
            return 0;
            break;
        case 22:
        case 23:
            if (reverse)
            {
                player->curScreen -= 1;
            }
            else
            {

                player->curScreen += 1;
            }
            seekNewPos(player);
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

void playerMove(int *key, int *reverse, int *isNotMoving, int *isOnTitle, PLAYER *player, int world[7][14])
{
    int turned = 0;
    if (*isNotMoving)
    {
        *key = getch();
    }

    switch (*key)
    {
    case 'w':
        if (canMove(world, player->mapX, player->mapY, 4, player, isNotMoving, *reverse))
        {
            player->y -= 8;
            if (!*isNotMoving)
            {
                player->mapY -= 1;
            }
        }
        break;
    case 's':
        if (canMove(world, player->mapX, player->mapY, 2, player, isNotMoving, *reverse))
        {
            player->y += 8;
            if (!*isNotMoving)
            {
                player->mapY += 1;
            }
        }
        break;
    case 'a':
        if (*reverse)
        {
            if (canMove(world, player->mapX, player->mapY, 3, player, isNotMoving, *reverse))
            {
                player->x -= 8 * 3;
                if (!*isNotMoving)
                {
                    player->mapX -= 1;
                }
            }
        }
        else
        {
            *reverse = 1;
            turned = 1;
        }
        break;
    case 'd':
        if (!*reverse)
        {
            if (canMove(world, player->mapX, player->mapY, 1, player, isNotMoving, *reverse))
            {
                player->x += 8 * 3;
                if (!*isNotMoving)
                {
                    player->mapX += 1;
                }
            }
        }
        else
        {
            *reverse = 0;
            turned = 1;
        }
        break;
    case 'k':
        menu(isOnTitle, player);
        break;
    default:
        if (*isNotMoving)
        {
            return;
        }
    }

    if (!turned && *key != 'k')
    {
        *isNotMoving = !*isNotMoving;
    }

    if (world[player->mapY - 1][player->mapX - 1] == 3)
    {
        world[player->mapY - 1][player->mapX - 1] = 0;
        player->potions += 1;
    }

    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 1000000000 / 30;
    nanosleep(&delay, NULL);
}