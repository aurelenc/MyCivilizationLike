/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"
#include <math.h>

bool handle_level_clicks(civlike_t *civ, sfEvent event, sfVector2f mouse_rel)
{
    bool event_handled = false;

    for (int i = 0; i < MAX_TILES; i++)
    {
        if (in_tile(civ->graph->tiles[i], civ->graph->hex_vectors, mouse_rel, civ->graph->hex))
        {
            civ->graph->tiles[i]->selected = true;
            civ->selected_tile = i;
            event_handled = true;
        }
        else
            civ->graph->tiles[i]->selected = false;
    }
    return event_handled;
}
