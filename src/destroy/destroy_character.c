/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** destroy_character.c
*/

#include "my_rpg.h"
#include <stdlib.h>

void characters_destroy(character_t *character)
{
    if (character->move_clock)
        sfClock_destroy(character->move_clock);
    if (character->anim_clock)
        sfClock_destroy(character->anim_clock);
    if (character->rect)
        sfRectangleShape_destroy(character->rect);
    for (int i = 0; i < character->nb_anim; i++) {
        if (character->anim[i].anim)
            free(character->anim[i].anim);
    }
    if (character->anim)
        free(character->anim);
}

void destroy_character_other(rpg_t *rpg)
{
    if (rpg->characters[PLAYER].stat.hp_bar)
        sfRectangleShape_destroy(rpg->characters[PLAYER].stat.hp_bar);
    if (rpg->characters[PLAYER].stat.hp_bar_background)
        sfRectangleShape_destroy\
        (rpg->characters[PLAYER].stat.hp_bar_background);
    if (rpg->characters[PLAYER].stat.hp_shape)
        sfRectangleShape_destroy(rpg->characters[PLAYER].stat.hp_shape);
}

void destroy_inventory(inventory_t *inv)
{
    if (inv->background)
        sfRectangleShape_destroy(inv->background);
    if (inv->selector)
        sfRectangleShape_destroy(inv->selector);
    if (inv->items)
        free(inv->items);
    if (inv->ui.inv_text)
        sfText_destroy(inv->ui.inv_text);
    for (int i = 0; inv->ui.item_texts && inv->ui.item_texts[i]; i++) {
        if (inv->ui.item_texts[i])
            sfText_destroy(inv->ui.item_texts[i]);
    }
    if (inv->ui.item_texts)
        free(inv->ui.item_texts);
}

void destroy_quests(quests_t *quests)
{
    if (quests->background)
        sfRectangleShape_destroy(quests->background);
    if (quests->quests_text)
        sfText_destroy(quests->quests_text);
    for (int i = 0; quests->quest && quests->quest[i].text; i++) {
        if (quests->quest[i].text)
            sfText_destroy(quests->quest[i].text);
    }
    if (quests->quest)
        free(quests->quest);
}
