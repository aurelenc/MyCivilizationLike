/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"

void check_move_camera(civlike_t *civ)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(civ->graph->window);
    civ->graph->window_size = sfRenderWindow_getSize(civ->graph->window);
    int size_x = civ->graph->window_size.x;
    int size_y = civ->graph->window_size.y;

    if (!sfRenderWindow_hasFocus(civ->graph->window))
        return;
    if (sfKeyboard_isKeyPressed(sfKeyLeft) && sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){-1 * (size_x / 100), -1 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyLeft) && sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){-1 * (size_x / 100), 1 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){1 * (size_x / 100), -1 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){1 * (size_x / 100), 1 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyRight))
        sfView_move(civ->graph->view, (sfVector2f){1 * (size_x / 100), 0 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyLeft))
        sfView_move(civ->graph->view, (sfVector2f){-1 * (size_x / 100), 0 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){0 * (size_x / 100), -1 * (size_y / 100)});
    else if (sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){0 * (size_x / 100), 1 * (size_y / 100)});
    if (mouse.x <= size_x / 10 && mouse.x >= 0)
        sfView_move(civ->graph->view, (sfVector2f){-1 * (size_x / 100), 0 * (size_y / 100)});
    if (mouse.x >= size_x - size_x / 10 && mouse.x <= size_x)
        sfView_move(civ->graph->view, (sfVector2f){1 * (size_x / 100), 0 * (size_y / 100)});
    if (mouse.y <= size_y / 10 && mouse.y >= 0)
        sfView_move(civ->graph->view, (sfVector2f){0 * (size_x / 100), -1 * (size_y / 100)});
    if (mouse.y >= size_y - size_y / 10 && mouse.y <= size_y)
        sfView_move(civ->graph->view, (sfVector2f){0 * (size_x / 100), 1 * (size_y / 100)});
    sfClock_restart(civ->graph->view_clock);
}
