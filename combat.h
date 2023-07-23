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

void useItem(PLAYER *player, int *turn)
{
    drawBox(10, 40, 210, 87);
    if (player->potions == 0)
    {
        drawText("voce nao tem itens", 60 * 3, 90, 1);
        getch();
        return;
    }

    int usingItem = 1;
    unsigned int selected = 0;
    int key;
    while (usingItem)
    {
        drawBox(10, 40, 210, 87);
        drawText("usar pocao", 80 * 3, 90, 0);
        drawText("sim", 80 * 3, 100, 0);
        drawText("nao", 115 * 3, 100, 0);
        drawLetter(characters[37], 78 * 3 + 35 * (selected % 2) * 3, 100);
        key = getch();
        switch (key)
        {
        case 'j':
            if (selected % 2 == 0)
            {
                player->potions -= 1;
                player->life = (player->life + 20 > player->maxLife) ? player->maxLife : player->life + 20;
                *turn = 0;
                usingItem = 0;
                drawBox(10, 40, 210, 87);
                drawText("voce se curou com uma pocao", 35 * 3, 90, 1);
                getch();
            }
            else
            {
                usingItem = 0;
            }
        case 'h':
            usingItem = 0;
            break;
        case 'a':
            selected--;
            break;
        case 'd':
            selected++;
            break;
        }
    }
}

void playerTurn(PLAYER *player, ENEMY *enemy, int *turn, int *fighting)
{
    int attacking = 1;
    int key;
    unsigned int selected = 0;
    int miss = 0;
    int attacked = 0;
    while (attacking)
    {
        drawBox(10, 40, 210, 87);
        drawText("o que voce vai fazer", 58 * 3, 85, 0);
        drawText("bater", 30 * 3, 100, 0);
        drawText("magia", 65 * 3, 100, 0);
        drawText("cegar", 100 * 3, 100, 0);
        drawText("intimidar", 135 * 3, 100, 0);
        drawLetter(characters[37], 28 * 3 + 35 * (selected % 4) * 3, 100);
        key = getch();
        switch (key)
        {
        case 'j':
            if (selected % 4 == 0)
            {
                miss = diceRoll(10);
                if (!miss)
                {
                    enemy->life -= (diceRoll(15)) ? 2 * player->attack / enemy->defense : player->attack / enemy->defense;
                }
                drawBox(10, 40, 210, 87);
                drawText("voce bateu no inimigo", 50 * 3, 90, 1);
                getch();
            }
            else if (selected % 4 == 1)
            {
                miss = diceRoll(10);
                if (!miss)
                {
                    enemy->life -= (diceRoll(15)) ? 2 * player->magic / enemy->defense * 3 : player->magic / enemy->defense * 3;
                }
                magicAnimation(player, enemy, miss);
                drawBox(10, 40, 210, 87);
                drawText("voce feriu o inimigo usando\n   poderes sobrenaturais", 35 * 3, 90, 1);
                getch();
            }
            else if (selected % 4 == 2)
            {
                enemy->accuracy = (enemy->accuracy > 5) ? enemy->accuracy - 10 : 5;
                drawBox(10, 40, 210, 87);
                drawText("a visao do inimigo foi\n     comprometida", 50 * 3, 90, 1);
                getch();
            }
            else if (selected % 4 == 3)
            {
                enemy->defense = (enemy->defense > 0) ? enemy->defense - 2 : 1;
                drawBox(10, 40, 210, 87);
                drawText("o inimigo esta com medo", 45 * 3, 90, 1);
                getch();
            }
            if (miss)
            {
                drawBox(10, 40, 210, 87);
                drawText("voce errou", 80 * 3, 90, 1);
                getch();
            }
            if (enemy->life <= 0)
            {
                drawBox(10, 40, 210, 87);
                drawText("o inimigo foi derrotado", 45 * 3, 90, 1);
                *fighting = 0;
            }
            *turn = 0;
            attacking = 0;
            break;
        case 'h':
            attacking = 0;
        case 'a':
            selected--;
            break;
        case 'd':
            selected++;
            break;
        }
    }
}

void fight(PLAYER *player, ENEMY *enemy, char *text, int textPos)
{
    clear();
    drawBattleInfo(player, enemy);
    drawSprite(&player->sprites[0], 45 * 3, 30, 0);
    drawSprite(&goomba, 150 * 3, 30, 1);
    drawBox(10, 40, 210, 87);
    drawText(text, textPos * 3, 90, 1);
    int turn = diceRoll(50);
    int key = getch();
    unsigned int selected = 0;
    int miss = 0;
    int fighting = 1;
    while (fighting)
    {
        drawBattleInfo(player, enemy);
        drawBox(10, 40, 210, 87);
        drawText("o que voce vai fazer", 58 * 3, 85, 0);
        drawText("lutar", 60 * 3, 100, 0);
        drawText("item ", 95 * 3, 100, 0);
        drawText("correr", 130 * 3, 100, 0);
        drawLetter(characters[37], 58 * 3 + 35 * (selected % 3) * 3, 100);

        if (turn)
        {
            key = getch();

            switch (key)
            {
            case 'j':
                if (selected % 3 == 0)
                {
                    playerTurn(player, enemy, &turn, &fighting);
                }
                else if (selected % 3 == 1)
                {
                    useItem(player, &turn);
                }
                else
                {
                    fighting = (diceRoll(20));
                    if (!fighting)
                    {
                        drawBox(10, 40, 210, 87);
                        drawText("voce fugiu", 75 * 3, 85, 1);
                        turn = 0;
                        getch();
                    }
                    else
                    {
                        drawBox(10, 40, 210, 87);
                        drawText("a fuga falhou", 70 * 3, 85, 1);
                        turn = 0;
                        getch();
                    }
                }
                break;
            case 'a':
                selected = (selected == 0) ? 2 : selected - 1;
                break;
            case 'd':
                selected++;
                break;
            }
        }
        else
        {
            miss = diceRoll(100 - enemy->accuracy);
            if (miss)
            {
                turn = !turn;
                drawBox(10, 40, 210, 87);
                drawText("o inimigo tentou bater em voce", 30 * 3, 90, 1);
                getch();
                drawBox(10, 40, 210, 87);
                drawText("o inimigo errou", 65 * 3, 90, 1);
                getch();

                continue;
            }
            drawBox(10, 40, 210, 87);
            drawText("voce foi ferido pelo inimigo", 35 * 3, 90, 1);
            getch();

            player->life -= (diceRoll(15)) ? enemy->attack / player->defense * 2 : enemy->attack / player->defense;

            if (player->life <= 0)
            {
                drawBox(10, 40, 210, 87);
                drawText("voce morreu", 74 * 3, 90, 1);
                getch();
                fighting = 0;
            }
            else
            {
                turn = !turn;
            }
        }
    }
}