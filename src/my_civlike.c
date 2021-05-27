/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"
#include <stdlib.h>



int run_game(civlike_t *civ)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(civ->graph->window)) {
        // rpg->time = sfClock_restart(rpg->main_clock);
        while (sfRenderWindow_pollEvent(civ->graph->window, &event))
            analyse_events(civ, event);
        sfRenderWindow_clear(civ->graph->window, sfBlack);
        display_civ(civ);
        sfRenderWindow_display(civ->graph->window);
    }
    return (0);
}

int my_civlike(void)
{
    civlike_t *civ = calloc(sizeof(civlike_t), 1);

    if (!civ)
        return (84);
    if (init_civ(civ) < 0)
        return (84);
    if (run_game(civ) < 0)
        return (84);
    // destroy_civ(civ);
    return (0);
}