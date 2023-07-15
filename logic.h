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
