/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"
#include <stdio.h>

int load_map(civlike_t *civ)
{
    FILE *file = fopen("custom.map", "r");

    if (!file)
        return (-1);
    for (int i = 0; i < MAX_TILES; i++) {
        if (fread(&civ->graph->tiles[i]->type, 1, sizeof(tile_type_t), file) <= 0)
            break;
    }
    fclose(file);
    return (0);
}

int save_map(civlike_t *civ)
{
    FILE *file = fopen("custom.map", "w+");

    if (!file)
        return (-1);
    for (int i = 0; i < MAX_TILES; i++) {
        fwrite(&civ->graph->tiles[i]->type, 1, sizeof(tile_type_t), file);
    }
    fclose(file);
    return (0);
}
