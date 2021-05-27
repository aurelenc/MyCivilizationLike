/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** destroy_scene.c
*/

#include "my_rpg.h"
#include <stdlib.h>

void destroy_fight(fight_t *fight)
{
    if (fight->text)
        sfText_destroy(fight->text);
    for (int i = 0; fight->hud_objects && i < fight->nb_hud; i++) {
        if (fight->hud_objects[i].rect)
            sfRectangleShape_destroy(fight->hud_objects[i].rect);
    }
    if (fight->hud_objects)
        free(fight->hud_objects);
}

void destroy_menu(scene_t *scene)
{
    for (int i = 0; scene->button_tab && i < scene->buttons_nbr; i++) {
        if (scene->button_tab[i].rect)
            sfRectangleShape_destroy(scene->button_tab[i].rect);
        if (scene->button_tab[i].text)
            sfText_destroy(scene->button_tab[i].text);
    }
    if (scene->button_tab)
        free(scene->button_tab);
    if (scene->menu_text)
        sfText_destroy(scene->menu_text);
    if (scene->overlay)
        sfRectangleShape_destroy(scene->overlay);
}

void destroy_scene(scene_t *scenes)
{
    destroy_menu(&scenes[MAIN_MENU_SCENE]);
    destroy_menu(&scenes[DEATH_SCENE]);
    destroy_menu(&scenes[SETTINGS_SCENE]);
    destroy_menu(&scenes[OVERWORLD_SCENE]);
    destroy_fight(&scenes[BATTLE_SCENE].fight);
    destroy_menu(&scenes[BATTLE_SCENE]);
}