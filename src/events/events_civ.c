/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"
#include "my_ui.h"
#include <math.h>

int on_right(sfVector2f pos1, sfVector2f pos2, sfVector2f point)
{
    sfVector2f vector1 = {pos2.x - pos1.x, pos2.y - pos1.y};
    sfVector2f vector2 = {point.x - pos1.x, point.y - pos1.y};
    int res = vector1.x * vector2.y - vector1.y * vector2.x;

    if (res >= 0)
        return (1);
    return (0);
}

int in_tile(tile_t *tile, sfVector2f *vectors, sfVector2f point, sfConvexShape *shape)
{
    int res = 0;
    sfVector2f origin = sfConvexShape_getOrigin(shape);
    int point_count = sfConvexShape_getPointCount(shape);
    sfVector2f pos1 = {tile->pos.x - origin.x, tile->pos.y - origin.y};
    sfVector2f pos2 = {
        tile->pos.x - origin.x + vectors[1].x, tile->pos.y - origin.y + vectors[1].y};

    for (int i = 0; i < point_count; i++)
    {
        pos1.x = tile->pos.x - origin.x + vectors[i].x;
        pos1.y = tile->pos.y - origin.y + vectors[i].y;
        if (i + 1 < point_count)
        {
            pos2.x = tile->pos.x - origin.x + vectors[i + 1].x;
            pos2.y = tile->pos.y - origin.y + vectors[i + 1].y;
        }
        else
        {
            pos2.x = tile->pos.x - origin.x + vectors[0].x;
            pos2.y = tile->pos.y - origin.y + vectors[0].y;
        }
        res += on_right(pos1, pos2, point);
    }
    if (res == 0)
        return (1);
    return (0);
}

void check_keyboard_inputs(civlike_t *civ, sfEvent event)
{
    if (event.type != sfEvtKeyPressed)
        return;
    switch (event.key.code)
    {
    case sfKeyNumpad0:
        civ->graph->tiles[civ->selected_tile]->type = 0;
        break;
    case sfKeyNumpad1:
        civ->graph->tiles[civ->selected_tile]->type = 1;
        break;
    case sfKeyNumpad2:
        civ->graph->tiles[civ->selected_tile]->type = 2;
        break;
    case sfKeyNumpad3:
        civ->graph->tiles[civ->selected_tile]->type = 3;
        break;
    case sfKeyNumpad4:
        civ->graph->tiles[civ->selected_tile]->type = 4;
        break;
    case sfKeyNumpad5:
        civ->graph->tiles[civ->selected_tile]->type = 5;
        break;
    case sfKeyNumpad6:
        civ->graph->tiles[civ->selected_tile]->type = 6;
        break;
    case sfKeyNumpad7:
        civ->graph->tiles[civ->selected_tile]->type = 7;
        break;
    case sfKeyNumpad8:
        civ->graph->tiles[civ->selected_tile]->type = 8;
        break;
    default:
        break;
    }
    save_map(civ);
}

void check_mouse_events(civlike_t *civ, sfEvent event, sfVector2f mouse_rel)
{
    sfVector2f view_size = sfView_getSize(civ->graph->view);

    civ->graph->window_size = sfRenderWindow_getSize(civ->graph->window);
    if (event.type == sfEvtMouseButtonPressed)
    {
        if (handle_ui_click(civ, mouse_rel) == UI_EVENT_BLOCK)
        {
            return;
        }
        else if (handle_level_clicks(civ, event, mouse_rel) == true)
        {
            return;
        }
    }
    else if (event.type == sfEvtMouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0 && view_size.y > (civ->graph->window_size.y * pow(0.8, 4)))
            sfView_zoom(civ->graph->view, 0.8);
        else if (event.mouseWheelScroll.delta < 0 && view_size.y < (civ->graph->window_size.y * pow(1.2, 4)))
            sfView_zoom(civ->graph->view, 1.2);
        view_size = sfView_getSize(civ->graph->view);
        if (view_size.y < (civ->graph->window_size.y * pow(0.8, 4)))
            sfView_setSize(civ->graph->view, (sfVector2f){(civ->graph->window_size.x * pow(0.8, 4)), (civ->graph->window_size.y * pow(0.8, 4))});
        else if (view_size.y > (civ->graph->window_size.y * pow(1.2, 4)))
            sfView_setSize(civ->graph->view, (sfVector2f){(civ->graph->window_size.x * pow(1.2, 4)), (civ->graph->window_size.y * pow(1.2, 4))});
    }
}

void analyse_events(civlike_t *civ, sfEvent event)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(civ->graph->window);

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(civ->graph->window);
    check_mouse_events(civ, event, sfRenderWindow_mapPixelToCoords(civ->graph->window, mouse, civ->graph->view));
    check_keyboard_inputs(civ, event);
}
