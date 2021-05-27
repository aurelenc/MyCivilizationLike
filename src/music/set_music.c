/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** set_music
*/

#include "my_rpg.h"

void set_active_music(audio_t *audio, music_id_t music)
{
    for (int i = 0; i < MUSIC_COUNT; i++)
        sfMusic_stop(audio->music[i]);
    sfMusic_play(audio->music[music]);
    sfMusic_setLoop(audio->music[music], sfTrue);
}