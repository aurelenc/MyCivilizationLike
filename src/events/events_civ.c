/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"

int on_right(sfVector2f pos1, sfVector2f pos2, sfVector2f point)
{
    sfVector2f vector1 = {pos2.x - pos1.x, pos2.y - pos1.y};
    sfVector2f vector2 = {point.x - pos1.x, point.y - pos1.y};
    int res = vector1.x * vector2.y - vector1.y * vector2.x;

    if (res >= 0)
        return (1);
    return (0);
}

int in_tile(tile_t tile, sfVector2f *vectors, sfVector2f point, sfConvexShape *shape)
{
    int res = 0;
    sfVector2f origin = sfConvexShape_getOrigin(shape);
    int point_count = sfConvexShape_getPointCount(shape);
    sfVector2f pos1 = {tile.pos.x - origin.x, tile.pos.y - origin.y};
    sfVector2f pos2 = { \
        tile.pos.x - origin.x + vectors[1].x, tile.pos.y - origin.y + vectors[1].y};

    for (int i = 0; i < point_count; i++) {
        pos1.x = tile.pos.x - origin.x + vectors[i].x;
        pos1.y = tile.pos.y - origin.y + vectors[i].y;
        if (i + 1 < point_count) {
            pos2.x = tile.pos.x - origin.x + vectors[i + 1].x;
            pos2.y = tile.pos.y - origin.y + vectors[i + 1].y;
        } else {
            pos2.x = tile.pos.x - origin.x + vectors[0].x;
            pos2.y = tile.pos.y - origin.y + vectors[0].y;
        }
        res += on_right(pos1, pos2, point);
    }
    if (res == 0)
        return (1);
    return (0);
}

void analyse_events(civlike_t *civ, sfEvent event)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(civ->graph->window);

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(civ->graph->window);
    if (event.type == sfEvtMouseButtonPressed)
        for (int i = 0; i < MAX_TILES; i++) {
            if (in_tile(civ->graph->tiles[i], civ->graph->hex_vectors, (sfVector2f){mouse.x, mouse.y}, civ->graph->hex))
                civ->graph->tiles[i].selected = true;
            else
                civ->graph->tiles[i].selected = false;
        }
}
