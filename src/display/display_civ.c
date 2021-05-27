/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"

void display_civ(civlike_t *civ)
{
    for (int i = 0; i < MAX_TILES; i++) {
        if (civ->graph->tiles[i].selected)
            sfConvexShape_setFillColor(civ->graph->hex, sfGreen);
        else
            sfConvexShape_setFillColor(civ->graph->hex, sfWhite);
        sfConvexShape_setPosition(civ->graph->hex, civ->graph->tiles[i].pos);
        sfRenderWindow_drawConvexShape(civ->graph->window, civ->graph->hex, NULL);
    }
}