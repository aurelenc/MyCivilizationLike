/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** menu_events
*/

#include "my_rpg.h"

void analyse_events_menu(rpg_t *rpg, sfEvent event)
{
    button_id_t buttons = rpg->scenes[rpg->active_scene].buttons_nbr;

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight) {
        if (rpg->scenes[rpg->active_scene].selected_button < buttons - 1)
            rpg->scenes[rpg->active_scene].selected_button++;
        else
            rpg->scenes[rpg->active_scene].selected_button = 0;
        sfSound_play(rpg->audio.sounds[SOUND_MENU_SWITCH]);
    } else if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft) {
        if (rpg->scenes[rpg->active_scene].selected_button > 0)
            rpg->scenes[rpg->active_scene].selected_button--;
        else
            rpg->scenes[rpg->active_scene].selected_button = buttons - 1;
        sfSound_play(rpg->audio.sounds[SOUND_MENU_SWITCH]);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEnter) {
        rpg->scenes[rpg->active_scene].button_tab\
        [rpg->scenes[rpg->active_scene].selected_button].callback(rpg);
        sfSound_play(rpg->audio.sounds[SOUND_CLICK]);
    }
}
