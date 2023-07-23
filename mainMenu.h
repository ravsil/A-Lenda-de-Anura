#include <stdio.h>
#include <ncurses.h>

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
        drawText("a lenda de anura", 65 * 3, 10);
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
        drawText("a lenda de anura", 65 * 3, 10);
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
            selected = (selected == 0) ? 2 : selected - 1;
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
    drawText("a lenda de anura", 65 * 3, 10);
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
