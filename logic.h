#include <ncurses.h>

void playerMove(int key, int *x, int *y, int *reverse, int *isNotMoving)
{
    if (*isNotMoving)
    {
        key = getch();
    }

    switch (key)
    {
    case 'w':
        *y -= 14;
        break;
    case 's':
        *y += 14;
        break;
    case 'a':
        if (*reverse)
        {
            *x -= 14;
        }
        else
        {
            *reverse = 11;
        }
        break;
    case 'd':
        if (!*reverse)
        {

            *x += 14;
        }
        else
        {
            *reverse = 0;
        }
        break;
    }

    *isNotMoving = !*isNotMoving;
}
