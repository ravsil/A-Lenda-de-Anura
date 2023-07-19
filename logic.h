#include <ncurses.h>
#include <time.h>

void playerMove(int *key, int *x, int *y, int *reverse, int *isNotMoving)
{
    int turned = 0;
    if (*isNotMoving)
    {
        *key = getch();
    }

    switch (*key)
    {
    case 'w':
        *y -= 8;
        break;
    case 's':
        *y += 8;
        break;
    case 'a':
        if (*reverse)
        {
            *x -= 8 * 3;
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

            *x += 8 * 3;
        }
        else
        {
            *reverse = 0;
            turned = 1;
        }
        break;
    default:
        if (*isNotMoving)
        {
            return;
        }
    }

    if (!turned)
    {
        *isNotMoving = !*isNotMoving;
    }

    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 1000000000 / 30;
    nanosleep(&delay, NULL);
}

void credits(long long int *characters)
{
    clear();
    drawText(characters, "blabla nome1", 40 * 3, 30);
    drawText(characters, "blabla nome2", 40 * 3, 40);
    drawText(characters, "blabla nome3", 40 * 3, 50);
    drawText(characters, "pressione qualquer tecla\n      para retornar", 40 * 3, 80);
    getch();
}

void controls(long long int *characters)
{
    clear();
    drawText(characters, "wasd  andar", 40 * 3, 30);
    drawText(characters, "j     confirmar", 40 * 3, 40);
    drawText(characters, "h     cancelar", 40 * 3, 50);
    drawText(characters, "k     menu", 40 * 3, 60);
    drawText(characters, "pressione qualquer tecla\n      para retornar", 40 * 3, 80);
    getch();
    return;
}

void titleScreen(long long int *characters, int *key, unsigned int *selected, int *isOnTitle, int *mainLoop)
{
    if (!*isOnTitle)
    {
        return;
    }

    clear();
    drawText(characters, "jogo do sapo mago brabo", 40 * 3, 10);
    drawText(characters, "iniciar", 80 * 3, 60);
    drawText(characters, "creditos", 80 * 3, 70);
    drawText(characters, "controles", 80 * 3, 80);
    drawText(characters, "sair", 80 * 3, 90);
    drawLetter(characters[36], 75 * 3, 60 + (*selected % 4 * 10));
    *key = getch();

    switch (*key)
    {
    case 'j':
        if (*selected % 4 == 0)
        {
            *isOnTitle = 0;
        }
        else if (*selected % 4 == 1)
        {
            credits(characters);
        }
        else if (*selected % 4 == 2)
        {
            controls(characters);
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
