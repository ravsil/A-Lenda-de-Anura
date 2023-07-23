#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int diceRoll(int chance)
{
    srand(time(NULL));

    if (rand() % 100 <= chance)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void playerTurn(PLAYER *player, ENEMY *enemy, int *turn)
{
    int attacking = 1;
    int key;
    unsigned int selected = 0;
    int miss = 0;
    while (attacking)
    {
        switch (key)
        {
        case 'j':
            if (selected % 4 == 0)
            {
                enemy->life -= (diceRoll(15)) ? 2 * player->attack / enemy->defense : player->attack / enemy->defense;
            }
            else if (selected % 4 == 1)
            {
                enemy->life -= (diceRoll(15)) ? 2 * player->magic / enemy->defense * 3 : player->magic / enemy->defense * 3;
            }
            else if (selected % 4 == 2)
            {
                enemy->accuracy = (enemy->accuracy > 5) ? enemy->accuracy - 5 : 5;
            }
            else
            {
                enemy->defense = (enemy->defense > 0) ? enemy->defense - 2 : 1;
            }
            *turn = 0;
            break;
        case 'h':
            attacking = 0;
        case 'w':
            selected--;
            break;
        case 's':
            selected++;
            break;
        }
    }
}

void fight(PLAYER *player, ENEMY *enemy)
{
    int turn = diceRoll(50);
    int key;
    unsigned int selected = 0;
    int miss = 0;
    int fighting = 1;
    while (fighting)
    {
        if (turn)
        {
            key = getch();

            switch (key)
            {
            case 'j':
                if (selected % 3 == 0)
                {
                    playerTurn(player, enemy, &turn);
                }
                else if (selected % 3 == 1)
                {
                    // use item
                }
                else
                {
                    fighting = (diceRoll(95)) ? 0 : 1;
                    if (!fighting)
                    {
                        // print not fighting message
                    }
                    else
                    {
                        // print still fighting message
                    }
                }
                break;
            case 'w':
                selected = (selected == 0) ? 2 : selected - 1;
                break;
            case 's':
                selected++;
                break;
            }

            // do something
        }
        else
        {
            miss = diceRoll(100 - enemy->accuracy);
            if (miss)
            {
                turn = !turn;
                continue;
            }

            player->life -= (diceRoll(15)) ? enemy->attack / player->defense * 2 : enemy->attack / player->defense;

            if (player->life <= 0)
            {
                // gameover
            }
            else
            {
                turn = !turn;
            }
        }
    }
}