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

    drawText(player->name, 40 * 3, 20);
    drawText("vida", 40 * 3, 30);
    drawText(life, 75 * 3, 30);
    drawText("ataque", 40 * 3, 40);
    drawText(attack, 80 * 3, 40);
    drawText("defesa", 40 * 3, 50);
    drawText(defense, 80 * 3, 50);
    drawText("mana", 40 * 3, 60);
    drawText(mana, 80 * 3, 60);
    drawText("magia", 40 * 3, 70);
    drawText(magic, 80 * 3, 70);
    drawText("pressione qualquer tecla\n     para retornar", 40 * 3, 90);
    getch();
}

void save(PLAYER *player)
{
    FILE *f;
    f = fopen("playerData.dat", "wb");
    fwrite(player, sizeof(PLAYER), 1, f);
    fclose(f);
    clear();
    drawText("jogo salvo com sucesso", 50 * 3, 10);
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
        drawText("status", 140 * 3, 25);
        drawText("item", 140 * 3, 35);
        drawText("salvar", 140 * 3, 45);
        drawText("inicio", 140 * 3, 55);
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

int canMove(int world[7][14], int x, int y, int direction)
{
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
    else if (world[y - 1][x - 1] < 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void playerMove(int *key, int *reverse, int *isNotMoving, int *isOnTitle, PLAYER *player, int world[7][14], int *mapX, int *mapY)
{
    int turned = 0;
    if (*isNotMoving)
    {
        *key = getch();
    }

    switch (*key)
    {
    case 'w':
        if (canMove(world, *mapX, *mapY, 4))
        {
            player->y -= 8;
            if (!*isNotMoving)
            {
                *mapY -= 1;
            }
        }
        break;
    case 's':
        if (canMove(world, *mapX, *mapY, 2))
        {
            player->y += 8;
            if (!*isNotMoving)
            {
                *mapY += 1;
            }
        }
        break;
    case 'a':
        if (*reverse)
        {
            if (canMove(world, *mapX, *mapY, 3))
            {
                player->x -= 8 * 3;
                if (!*isNotMoving)
                {
                    *mapX -= 1;
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
            if (canMove(world, *mapX, *mapY, 1))
            {
                player->x += 8 * 3;
                if (!*isNotMoving)
                {
                    *mapX += 1;
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

    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 1000000000 / 30;
    nanosleep(&delay, NULL);
}

void nameScreen(PLAYER *player)
{
    int isOnName = 1;
    int key;
    char letter;
    unsigned int curLetter = 0;
    int index = 0;
    while (isOnName)
    {
        clear();
        drawText("jogo do sapo mago brabo", 45 * 3, 10);
        drawText("diga seu nome", 10 * 3, 40);
        curLetter = curLetter % 37;

        drawLetter(characters[curLetter], 15 * 3 + (index * 8 * 2), 50);
        drawText(player->name, 9 * 3, 50);
        key = getch();
        switch (key)
        {
        case 'j':
            if (curLetter < 26)
            {
                letter = 'a' + curLetter;
            }
            else if (curLetter < 36)
            {
                letter = '0' + curLetter - 26;
            }
            else
            {
                isOnName = 0;
                break;
            }
            player->name[index] = letter;
            player->name[index + 1] = '\0';
            index++;
            curLetter = (index < 8) ? 0 : 36;
            break;
        case 'h':
            if (index == 0)
            {
                break;
            }
            index--;
            curLetter = (player->name[index] >= 'a') ? player->name[index] - 'a' : player->name[index] - '0' + 26;
            player->name[index] = '\0';
            break;
        case 'w':
            curLetter = (curLetter == 0) ? 36 : curLetter - 1;
            break;
        case 's':
            curLetter++;
            break;
        }
    }
}

void load(PLAYER *player, int *isOnTitle, int *isStarting, int start, char *file)
{
    FILE *f;
    f = fopen(file, "rb");

    if (f)
    {
        fread(player, sizeof(PLAYER), 1, f);
        fclose(f);
        if (start)
        {
            *isOnTitle = 0;
            *isStarting = 0;
        }
    }
    else
    {
        clear();
        drawText("nenhum salvamento encontrado", 35 * 3, 10);
        drawText("pressione qualquer tecla\n     para retornar", 40 * 3, 80);
        getch();
    }
    return;
}

void records(int *isOnTitle)
{
    return;
}

void startingScreen(PLAYER *player, int *isOnTitle)
{
    int isStarting = 1;
    unsigned int selected = 0;
    int key;
    while (isStarting)
    {
        clear();
        drawText("jogo do sapo mago brabo", 45 * 3, 10);
        drawText("novo jogo", 80 * 3, 60);
        drawText("continuar", 80 * 3, 70);
        drawText("recordes", 80 * 3, 80);
        drawLetter(characters[37], 75 * 3, 60 + (selected % 3 * 10));

        key = getch();
        switch (key)
        {
        case 'j':
            if (selected % 3 == 0)
            {
                player->name[0] = '\0';
                load(player, isOnTitle, &isStarting, 0, "sapo.dat");
                nameScreen(player);
                *isOnTitle = 0;
                isStarting = 0;
            }
            else if (selected % 3 == 1)
            {
                load(player, isOnTitle, &isStarting, 1, "playerData.dat");
            }
            else
            {
                records(isOnTitle);
            }
            break;
        case 'h':
            isStarting = 0;
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

void credits()
{
    clear();
    drawText("esther mussi de castro", 40 * 3, 30);
    drawText("maria eduarda oliveira", 40 * 3, 40);
    drawText("rafael vieira da silva", 40 * 3, 50);
    drawText("pressione qualquer tecla\n     para retornar", 40 * 3, 80);
    getch();
}

void controls()
{
    clear();
    drawText("wasd  andar", 40 * 3, 30);
    drawText("j     confirmar", 40 * 3, 40);
    drawText("h     cancelar", 40 * 3, 50);
    drawText("k     menu", 40 * 3, 60);
    drawText("pressione qualquer tecla\n     para retornar", 40 * 3, 80);
    getch();
}

void titleScreen(PLAYER *player, int *key, unsigned int *selected, int *isOnTitle, int *mainLoop)
{
    if (!*isOnTitle)
    {
        return;
    }

    clear();
    drawText("jogo do sapo mago brabo", 45 * 3, 10);
    drawText("iniciar", 80 * 3, 60);
    drawText("creditos", 80 * 3, 70);
    drawText("controles", 80 * 3, 80);
    drawText("sair", 80 * 3, 90);
    drawText("wasd", 0, 100);
    drawText("j", 200 * 3, 100);
    drawLetter(characters[37], 75 * 3, 60 + (*selected % 4 * 10));
    *key = getch();

    switch (*key)
    {
    case 'j':
        if (*selected % 4 == 0)
        {
            // *isOnTitle = 0;
            startingScreen(player, isOnTitle);
        }
        else if (*selected % 4 == 1)
        {
            credits();
        }
        else if (*selected % 4 == 2)
        {
            controls();
        }
        else
        {
            *mainLoop = 0;
        }
        *selected = 0;
        break;
    case 'w':
        *selected -= 1;
        break;
    case 's':
        *selected += 1;
        break;
    }
}
