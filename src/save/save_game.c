/*
** EPITECH PROJECT, 2021
** B-MUL-200-NAN-2-1-myrpg-quentin.leroueil
** File description:
** save_game
*/

#include "my.h"
#include "my_rpg.h"
#include <stdio.h>

int save_stats(rpg_t *rpg, FILE *file)
{
    int max_hp = rpg->characters[PLAYER].stat.max_hp;
    int atk = rpg->characters[PLAYER].stat.atk;

    fwrite(&max_hp, sizeof(int), 1, file);
    fwrite(&atk, sizeof(int), 1, file);
    fwrite(";", sizeof(char), 1, file);
    return (0);
}

int save_pos(rpg_t *rpg, FILE *file)
{
    float pos = 0;

    pos = rpg->characters[PLAYER].pos.x;
    fwrite(&pos, sizeof(float), 1, file);
    pos = rpg->characters[PLAYER].pos.y;
    fwrite(&pos, sizeof(float), 1, file);
    fwrite(";", sizeof(char), 1, file);
    return (0);
}

int save_quests(rpg_t *rpg, FILE *file)
{
    int quests = 0;

    for (int i = 0; i < 4; i++) {
        quests = rpg->quests.quest[i].res_type;
        fwrite(&quests, sizeof(int), 1, file);
    }
    fwrite(";", sizeof(char), 1, file);
    return (0);
}

int save_game(rpg_t *rpg)
{
    FILE *file = fopen("1.sav", "w+");
    int item = 0;

    if (!file) {
        my_putstr("Error: save failed, please check if the 'save' file at the \
        \b\b\b\b\b\b\b\broot of the repository can be read and edited\n");
        return (-1);
    }
    for (int i = 0; i < rpg->inventory.size; i++) {
        item = rpg->inventory.items[i].type;
        fwrite(&item, sizeof(int), 1, file);
    }
    fwrite(";", sizeof(char), 1, file);
    save_quests(rpg, file);
    save_pos(rpg, file);
    save_stats(rpg, file);
    fclose(file);
    return (0);
}