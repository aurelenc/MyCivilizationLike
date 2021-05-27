/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** destroy_music_sound.c
*/

#include <stdlib.h>
#include "my_rpg.h"

int destroy_music_to(audio_t *audio)
{
    for (int i = 0; i < MUSIC_COUNT; i++)
        if (audio->music[i])
            sfMusic_destroy(audio->music[i]);
    return (-1);
}

void destroy_music(sfMusic **music)
{
    for (int i = 0; i < MUSIC_COUNT; i++)
        if (music[i])
            sfMusic_destroy(music[i]);
    if (music)
        free(music);
}

void destroy_soundbuffer(sfSoundBuffer **buff)
{
    for (int i = 0; i < SOUND_COUNT; i++)
        if (buff[i])
            sfSoundBuffer_destroy(buff[i]);
    if (buff)
        free(buff);
}

void destroy_sound(sfSound **sounds)
{
    for (int i = 0; i < SOUND_COUNT; i++)
        if (sounds[i])
            sfSound_destroy(sounds[i]);
    if (sounds)
        free(sounds);
}

void destroy_music_sound(audio_t *audio)
{
    if (audio->music)
        destroy_music(audio->music);
    if (audio->sound_buffers)
        destroy_soundbuffer(audio->sound_buffers);
    if (audio->sounds)
        destroy_sound(audio->sounds);
}
