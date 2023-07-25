#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int levelUp(PLAYER *player)
{
    int choosing = 1;
    int key;
    unsigned int selected = 0;
    while (choosing)
    {
        clear();
        drawText("parabens, voce subiu de nivel!", 10 * 3, 20, 0);
        drawText("escolha uma habilidade para melhorar", 10 * 3, 30, 0);
        drawText("vida", 15 * 3, 40, 0);
        drawText("ataque", 15 * 3, 50, 0);
        drawText("defesa", 15 * 3, 60, 0);
        drawText("magia", 15 * 3, 70, 0);
        drawLetter(characters[37], 10 * 3, 40 + (selected * 10));

        drawText("pressione j para confirmar", 10 * 3, 90, 0);

        key = getch();

        switch (key)
        {
        case 'j':
            choosing = 0;
            switch (selected)
            {
            case 0:
                player->maxLife += 3;
                break;
            case 1:
                player->attack += 2;
                break;
            case 2:
                player->defense += 2;
                break;
            case 3:
                player->magic += 3;
                break;
            }
            break;
        case 'w':
            selected = (selected == 0) ? 3 : selected - 1;
            break;
        case 's':
            selected = (selected == 3) ? 0 : selected + 1;
            break;
        }
    }
}

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
        drawText("comer mosca?", 80 * 3, 90, 0);
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
                drawText("voce comeu uma mosca", 35 * 3, 90, 1);
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

void playerTurn(PLAYER *player, ENEMY *enemy, int *turn, int *fighting, int enemyType)
{
    int attacking = 1;
    int key;
    unsigned int selected = 0;
    int miss = 0;
    int attacked = 0;
    while (attacking)
    {
        drawBox(10, 40, 210, 87);
        drawText("o que voce vai fazer?", 58 * 3, 85, 0);
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
                    enemy->life -= (diceRoll(15)) ? 4 * player->attack / enemy->defense : 2 * player->attack / enemy->defense;
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
                    enemy->life -= (diceRoll(15)) ? 4 * player->magic / enemy->defense * 3 : 2 * player->magic / enemy->defense * 3;
                }
                magicAnimation(player, enemy, miss);
                drawBox(10, 40, 210, 87);
                player->mana -= 1;
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
                getch();
                player->xp += (enemyType == 0) ? 50 : 100;
                if (player->xp / 100 > player->lvl)
                {
                    player->lvl += 1;
                    levelUp(player);
                }
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

void fight(PLAYER *player, int enemyType, char *text, int textPos)
{
    ENEMY enemy;
    switch (enemyType)
    {
    case 0:
        enemy.life = 10;
        enemy.maxLife = 10;
        enemy.attack = 5;
        enemy.defense = 5;
        enemy.accuracy = 90;
        break;
    case 1:
        enemy.life = 5;
        enemy.maxLife = 5;
        enemy.attack = 10;
        enemy.defense = 10;
        enemy.accuracy = 80;
        break;
    case 2:
        enemy.life = 50;
        enemy.maxLife = 50;
        enemy.attack = 30;
        enemy.defense = 30;
        enemy.accuracy = 95;
        break;
    }

    clear();
    drawBattleInfo(player, &enemy);
    drawSprite(&player->sprites[2], 45 * 3, 30, 0);
    if (enemyType == 2)
    {
        drawSprite(&assets[10], 150 * 3, 20, 0);
        drawSprite(&assets[9], 150 * 3, 36, 0);
    }
    else
    {

        drawSprite(&assets[3], 150 * 3, 30, 1);
    }
    drawBox(10, 40, 210, 87);
    drawText(text, textPos * 3, 90, 1);
    int turn = diceRoll(50);
    int key = getch();
    unsigned int selected = 0;
    int miss = 0;
    int fighting = 1;
    while (fighting)
    {
        drawBattleInfo(player, &enemy);
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
                    playerTurn(player, &enemy, &turn, &fighting, enemyType);
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
            miss = diceRoll(100 - enemy.accuracy);
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

            player->life -= (diceRoll(15)) ? enemy.attack / player->defense * 2 : enemy.attack / player->defense;

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
    if (enemyType == 2)
    {
        if (player->life > 0)
        {
            player->lvl = -2;
        }
        else
        {
            clear();
            drawText("voce nao foi forte o bastante para", 15 * 3, 40, 0);
            drawText("derrotar um humano, quem sabe", 15 * 3, 50, 0);
            drawText("se treinasse mais...", 15 * 3, 60, 0);
            getch();
        }
    }
}