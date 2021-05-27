/*
** EPITECH PROJECT, 2021
** B-MUL-200-NAN-2-1-myrpg-quentin.leroueil
** File description:
** check_collision
*/

#include "my_rpg.h"

void check_collision_paps\
(sfIntRect player_rect, sfIntRect enemy_rect, rpg_t *rpg)
{
    if (sfIntRect_intersects(&player_rect, &enemy_rect, NULL) && \
    rpg->quests.quest[QUEST_ID_SPAGHETTI].res_type != QUEST_T_DONE) {
        rpg->scenes[BATTLE_SCENE].fight.enemy = PAPS;
        set_scene_battle(rpg, MUSIC_PAPS_THEME);
    }
}

void check_collision_sans\
(sfIntRect player_rect, sfIntRect enemy_rect, rpg_t *rpg)
{
    if (rpg->quests.quest[QUEST_ID_SPAGHETTI].res_type == QUEST_T_DONE && \
    sfIntRect_intersects(&player_rect, &enemy_rect, NULL) && \
    rpg->quests.quest[QUEST_ID_HOTDOG].res_type != QUEST_T_DONE) {
        rpg->scenes[BATTLE_SCENE].fight.enemy = SANS;
        set_scene_battle(rpg, MUSIC_SANS_THEME);
    }
}

void check_collision_jevil\
(sfIntRect player_rect, sfIntRect enemy_rect, rpg_t *rpg)
{
    if (rpg->quests.quest[QUEST_ID_HOTDOG].res_type == QUEST_T_DONE && \
    sfIntRect_intersects(&player_rect, &enemy_rect, NULL) && \
    rpg->quests.quest[QUEST_ID_SCYTHE].res_type != QUEST_T_DONE) {
        rpg->scenes[BATTLE_SCENE].fight.enemy = JEVIL;
        set_scene_battle(rpg, MUSIC_JEVIL_THEME);
    }
}

void check_collisions(rpg_t *rpg)
{
    sfIntRect player_rect = {rpg->characters[PLAYER].pos.x, \
        rpg->characters[PLAYER].pos.y, rpg->characters[PLAYER].size.x, \
        rpg->characters[PLAYER].size.y};
    sfIntRect sans_rect = {rpg->characters[SANS].pos.x, \
        rpg->characters[SANS].pos.y, rpg->characters[SANS].size.x, \
        rpg->characters[SANS].size.y};
    sfIntRect paps_rect = {rpg->characters[PAPS].pos.x, \
        rpg->characters[PAPS].pos.y, rpg->characters[PAPS].size.x, \
        rpg->characters[PAPS].size.y};
    sfIntRect jevil_rect = {rpg->characters[JEVIL].pos.x, \
        rpg->characters[JEVIL].pos.y, rpg->characters[JEVIL].size.x, \
        rpg->characters[JEVIL].size.y};

    check_collision_paps(player_rect, paps_rect, rpg);
    check_collision_sans(player_rect, sans_rect, rpg);
    check_collision_jevil(player_rect, jevil_rect, rpg);
}