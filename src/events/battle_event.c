/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** battle_event.c
*/

#include "my_rpg.h"

void player_choosing_action_event(rpg_t *rpg, sfEvent event)
{
    if (event.key.code == sfKeyLeft)
        rpg->scenes[BATTLE_SCENE].fight.button--;
    if (event.key.code == sfKeyRight)
        rpg->scenes[BATTLE_SCENE].fight.button++;
    if (rpg->scenes[BATTLE_SCENE].fight.button < ATK_BUTTON)
        rpg->scenes[BATTLE_SCENE].fight.button = GUARD_BUTTON;
    if (rpg->scenes[BATTLE_SCENE].fight.button > GUARD_BUTTON)
        rpg->scenes[BATTLE_SCENE].fight.button = ATK_BUTTON;
    if (event.key.code == sfKeyZ || event.key.code == sfKeyEnter)
        rpg->scenes[BATTLE_SCENE].fight.choosing_action = CHOOSED;
}

void player_item_event(rpg_t *rpg, sfEvent event)
{
    if (event.key.code == sfKeyDown || event.key.code == sfKeyUp || \
        event.key.code == sfKeyLeft || event.key.code == sfKeyRight)
        sfSound_play(rpg->audio.sounds[SOUND_MENU_SWITCH]);
    if (event.key.code == sfKeyDown)
        rpg->inventory.selected_item++;
    if (event.key.code == sfKeyUp)
        rpg->inventory.selected_item--;
    if (event.key.code == sfKeyRight)
        rpg->inventory.selected_item += 4;
    if (event.key.code == sfKeyLeft)
        rpg->inventory.selected_item -= 4;
    if (rpg->inventory.selected_item >= rpg->inventory.size)
        rpg->inventory.selected_item -= rpg->inventory.size;
    else if (rpg->inventory.selected_item < 0)
        rpg->inventory.selected_item += rpg->inventory.size;
    if ((event.key.code == sfKeyX || event.key.code == sfKeyRShift))
        rpg->scenes[BATTLE_SCENE].fight.choosing_action = CHOOSING;
    if ((event.key.code == sfKeyEnter) && ITEM_EMPTY != \
        rpg->inventory.items[rpg->inventory.selected_item].type)
        heal_player_item(rpg);
}

void player_act_event(rpg_t *rpg, sfEvent event)
{
    if ((event.key.code == sfKeyZ || event.key.code == sfKeyEnter) \
    && rpg->scenes[BATTLE_SCENE].fight.entity_mov_phase == 1) {
        rpg->scenes[BATTLE_SCENE].fight.entity_mov_phase = 2;
        sfSound_play(rpg->audio.sounds[SOUND_CLICK]);
    }
}

void analyse_events_battle(rpg_t *rpg, sfEvent event)
{
    if (rpg->scenes[BATTLE_SCENE].fight.turn == 0)
        return;
    if (event.type == sfEvtKeyPressed && \
    rpg->scenes[BATTLE_SCENE].fight.choosing_action == CHOOSED) {
        if (rpg->scenes[BATTLE_SCENE].fight.action == ITEM)
            player_item_event(rpg, event);
        if (rpg->scenes[BATTLE_SCENE].fight.action == ACT)
            player_act_event(rpg, event);
    } else if (event.type == sfEvtKeyPressed && \
    rpg->scenes[BATTLE_SCENE].fight.choosing_action == CHOOSING) {
        player_choosing_action_event(rpg, event);
    }
}
