/*
** EPITECH PROJECT, 2021
** B-MUL-200-NAN-2-1-myrpg-quentin.leroueil
** File description:
** delete_save
*/

#include "my_rpg.h"
#include <stdio.h>
#include <stdlib.h>

void reset_stats(rpg_t *rpg)
{
    rpg->characters[PLAYER].stat.max_hp = 50;
    rpg->characters[PLAYER].stat.atk = 10;
    rpg->characters[PAPS].stat.max_hp = 100;
    rpg->characters[PAPS].stat.atk = 10;
    rpg->characters[SANS].stat.max_hp = 150;
    rpg->characters[SANS].stat.atk = 15;
    rpg->characters[JEVIL].stat.max_hp = 200;
    rpg->characters[JEVIL].stat.atk = 25;
    for (int i = 0; i < 4; i++) {
        rpg->characters[i].stat.hp = rpg->characters[i].stat.max_hp;
    }
}

void delete_save(rpg_t *rpg)
{
    rpg->quests.quest[QUEST_ID_SPAGHETTI].res_type = QUEST_T_STARTED;
    rpg->quests.quest[QUEST_ID_HOTDOG].res_type = QUEST_T_NOT_STARTED;
    rpg->quests.quest[QUEST_ID_SCYTHE].res_type = QUEST_T_NOT_STARTED;
    rpg->quests.quest[QUEST_ID_ESCAPE].res_type = QUEST_T_NOT_STARTED;
    for (int i = 0; i < rpg->inventory.size; i++)
        reset_slot_from_inventory(&rpg->inventory, i);
    add_item_in_inventory(&rpg->inventory, ITEM_BUTTERSCOTCH_PIE);
    add_item_in_inventory(&rpg->inventory, ITEM_BUTTERSCOTCH_PIE);
    add_item_in_inventory(&rpg->inventory, ITEM_BUTTERSCOTCH_PIE);
    for (int i = 0; i < 9; i++)
        add_item_in_inventory(&rpg->inventory, ITEM_SNOWMAN_PIECE);
    reset_stats(rpg);
    for (int i = 0; i < 4; i++) {
        reset_character_animation(&(rpg->characters[i]), 0);
        sfRectangleShape_setTextureRect(rpg->characters[i].rect, \
        rpg->characters[i].anim[0].anim[0]);
    }
    rpg->characters[PLAYER].pos = (sfVector2f){600, 600};
    save_game(rpg);
}