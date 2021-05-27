/*
** EPITECH PROJECT, 2020
** B-MUL-200-NAN-2-1-myrpg-quentin.leroueil
** File description:
** rpg_destroy.c
*/

#include "my_rpg.h"
#include <stdlib.h>

int destroy_sound_buffers_to(audio_t *audio)
{
    for (int i = 0; i < SOUND_COUNT; i++)
        if (audio->sound_buffers[i])
            sfSoundBuffer_destroy(audio->sound_buffers[i]);
    destroy_music_to(audio);
    return (-1);
}

void terminate_particles(rpg_t *rpg)
{
    delete_particle_list(rpg->particles.list);
    if (rpg->particles.clock)
        sfClock_destroy(rpg->particles.clock);
    if (rpg->particles.presets) {
        if (rpg->particles.presets[PARTICLE_SNOW])
            sfRectangleShape_destroy(rpg->particles.presets[PARTICLE_SNOW]);
        if (rpg->particles.presets[PARTICLE_HIT])
            sfRectangleShape_destroy(rpg->particles.presets[PARTICLE_HIT]);
        free(rpg->particles.presets);
    }
}

void graph_destroy(graph_t *graph)
{
    if (graph->window)
        sfRenderWindow_destroy(graph->window);
    for (int i = 0; graph->textures && i < 8; i++) {
        if (graph->textures[i])
            sfTexture_destroy(graph->textures[i]);
    }
    if (graph->textures)
        free(graph->textures);
    if (graph->snowdin_texture)
        sfTexture_destroy(graph->snowdin_texture);
    if (graph->player_camera)
        sfView_destroy(graph->player_camera);
    if (graph->font)
        sfFont_destroy(graph->font);
}

void destroy_map(rpg_t *rpg)
{
    while (rpg->list_map->size > 0) {
        if (!rpg->list_map->first)
            return;
        if (rpg->list_map->first->object->shape)
            sfRectangleShape_destroy(rpg->list_map->first->object->shape);
        if (rpg->list_map->first->object)
            free(rpg->list_map->first->object);
        rpg->list_map->first = rpg->list_map->first->next;
        rpg->list_map->size--;
    }
    if (rpg->list_map)
        free(rpg->list_map);
}

void rpg_destroy(rpg_t *rpg)
{
    destroy_character_other(rpg);
    sfClock_destroy(rpg->main_clock);
    if (rpg->characters) {
        for (int i = 0; i < 4; i++)
            characters_destroy(&(rpg->characters[i]));
    }
    if (rpg->characters)
        free(rpg->characters);
    destroy_scene(rpg->scenes);
    if (rpg->scenes)
        free(rpg->scenes);
    terminate_particles(rpg);
    destroy_music_sound(&rpg->audio);
    destroy_inventory(&rpg->inventory);
    destroy_quests(&rpg->quests);
    destroy_map(rpg);
    graph_destroy(&rpg->graph);
}