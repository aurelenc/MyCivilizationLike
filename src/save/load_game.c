/*
** EPITECH PROJECT, 2021
** B-MUL-200-NAN-2-1-myrpg-quentin.leroueil
** File description:
** save_game
*/

#include "my.h"
#include "my_rpg.h"
#include <stdio.h>
#include <unistd.h>

int load_stats(rpg_t *rpg, FILE *file)
{
    int max_hp = 0;
    int atk = 0;
    char delim = 0;

    if (fread(&max_hp, sizeof(int), 1, file) <= 0)
        return (-1);
    rpg->characters[PLAYER].stat.max_hp = max_hp;
    if (fread(&atk, sizeof(int), 1, file) <= 0)
        return (-1);
    rpg->characters[PLAYER].stat.atk = atk;
    if (fread(&delim, sizeof(char), 1, file) <= 0)
        return (-1);
    return (0);
}

int load_pos(rpg_t *rpg, FILE *file)
{
    float pos = 0.00;
    char delim = 0;

    if (fread(&pos, sizeof(float), 1, file) <= 0)
        return (-1);
    rpg->characters[PLAYER].pos.x = pos;
    if (fread(&pos, sizeof(float), 1, file) <= 0)
        return (-1);
    rpg->characters[PLAYER].pos.y = pos;
    if (fread(&delim, sizeof(char), 1, file) <= 0)
        return (-1);
    sfRectangleShape_setPosition(rpg->characters[PLAYER].rect, \
    rpg->characters[PLAYER].pos);
    load_stats(rpg, file);
    return (0);
}

int load_quests(rpg_t *rpg, FILE *file)
{
    int quests = 0;
    size_t read_ret = 0;
    char delim = 0;

    for (int i = 0; i < 4; i++) {
        read_ret = fread(&quests, sizeof(int), 1, file);
        if (read_ret <= 0)
            return (-1);
        rpg->quests.quest[i].res_type = quests;
    }
    read_ret = fread(&delim, sizeof(char), 1, file);
    if (read_ret <= 0)
        return (-1);
    load_pos(rpg, file);
    return (0);
}

int load_game(rpg_t *rpg)
{
    FILE *file = fopen("1.sav", "r");
    int item = 0;
    char delim = 0;

    if (!file) {
        my_putstr("Save file invalid, creating new one\n");
        delete_save(rpg);
        return (-1);
    }
    for (int i = 0; i < rpg->inventory.size; i++) {
        if (fread(&item, sizeof(int), 1, file) <= 0)
            return (-1);
        rpg->inventory.items[i].type = ITEM_EMPTY;
        rpg->inventory.items[i].type = item;
    }
    if (fread(&delim, sizeof(char), 1, file) <= 0)
        return (-1);
    load_quests(rpg, file);
    fclose(file);
    return (0);
}