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

int in_tile(tile_t *tile, sfVector2f *vectors, sfVector2f point, sfConvexShape *shape)
{
    int res = 0;
    sfVector2f origin = sfConvexShape_getOrigin(shape);
    int point_count = sfConvexShape_getPointCount(shape);
    sfVector2f pos1 = {tile->pos.x - origin.x, tile->pos.y - origin.y};
    sfVector2f pos2 = { \
        tile->pos.x - origin.x + vectors[1].x, tile->pos.y - origin.y + vectors[1].y};

    for (int i = 0; i < point_count; i++) {
        pos1.x = tile->pos.x - origin.x + vectors[i].x;
        pos1.y = tile->pos.y - origin.y + vectors[i].y;
        if (i + 1 < point_count) {
            pos2.x = tile->pos.x - origin.x + vectors[i + 1].x;
            pos2.y = tile->pos.y - origin.y + vectors[i + 1].y;
        } else {
            pos2.x = tile->pos.x - origin.x + vectors[0].x;
            pos2.y = tile->pos.y - origin.y + vectors[0].y;
        }
        res += on_right(pos1, pos2, point);
    }
    if (res == 0)
        return (1);
    return (0);
}

void check_move_camera(civlike_t *civ)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(civ->graph->window);

        if (!sfRenderWindow_hasFocus(civ->graph->window))
    return;
    if (sfKeyboard_isKeyPressed(sfKeyLeft) && sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){-1 * 1920 / 100, -1 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyLeft) && sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){-1 * 1920 / 100, 1 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){1 * 1920 / 100, -1 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){1 * 1920 / 100, 1 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyRight))
        sfView_move(civ->graph->view, (sfVector2f){1 * 1920 / 100, 0 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyLeft))
        sfView_move(civ->graph->view, (sfVector2f){-1 * 1920 / 100, 0 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyUp))
        sfView_move(civ->graph->view, (sfVector2f){0 * 1920 / 100, -1 * 1080 / 100});
    else if (sfKeyboard_isKeyPressed(sfKeyDown))
        sfView_move(civ->graph->view, (sfVector2f){0 * 1920 / 100, 1 * 1080 / 100});
    if (mouse.x <= 108)
        sfView_move(civ->graph->view, (sfVector2f){-1 * 1920 / 100, 0 * 1080 / 100});
    if (mouse.x >= 1920 - 108)
        sfView_move(civ->graph->view, (sfVector2f){1 * 1920 / 100, 0 * 1080 / 100});
    if (mouse.y <= 108)
        sfView_move(civ->graph->view, (sfVector2f){0 * 1920 / 100, -1 * 1080 / 100});
    if (mouse.y >= 1080 - 108)
        sfView_move(civ->graph->view, (sfVector2f){0 * 1920 / 100, 1 * 1080 / 100});
    sfClock_restart(civ->graph->view_clock);
}

void check_keyboard_inputs(civlike_t *civ, sfEvent event)
{
    if (event.type != sfEvtKeyPressed)
        return;
    if (event.key.code == sfKeyNumpad0)
        civ->graph->tiles[civ->selected_tile]->type = 0;
    else if (event.key.code == sfKeyNumpad1)
        civ->graph->tiles[civ->selected_tile]->type = 1;
    else if (event.key.code == sfKeyNumpad2)
        civ->graph->tiles[civ->selected_tile]->type = 2;
    else if (event.key.code == sfKeyNumpad3)
        civ->graph->tiles[civ->selected_tile]->type = 3;
    else if (event.key.code == sfKeyNumpad4)
        civ->graph->tiles[civ->selected_tile]->type = 4;
    else if (event.key.code == sfKeyNumpad5)
        civ->graph->tiles[civ->selected_tile]->type = 5;
    else if (event.key.code == sfKeyNumpad6)
        civ->graph->tiles[civ->selected_tile]->type = 6;
    else if (event.key.code == sfKeyNumpad7)
        civ->graph->tiles[civ->selected_tile]->type = 7;
    else if (event.key.code == sfKeyNumpad8)
        civ->graph->tiles[civ->selected_tile]->type = 8;
}

void check_mouse_events(civlike_t *civ, sfEvent event, sfVector2f mouse_rel)
{
    sfVector2f view_size = sfView_getSize(civ->graph->view);

    if (event.type == sfEvtMouseButtonPressed) {
        for (int i = 0; i < MAX_TILES; i++) {
            if (in_tile(civ->graph->tiles[i], civ->graph->hex_vectors, mouse_rel, civ->graph->hex)) {
                civ->graph->tiles[i]->selected = true;
                civ->selected_tile = i;
            } else
                civ->graph->tiles[i]->selected = false;
        }
    }
    if (event.type == sfEvtMouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0 && view_size.y > 442.368)
            sfView_zoom(civ->graph->view, 0.8);
        else if (event.mouseWheelScroll.delta < 0 && view_size.y < 2239.488)
            sfView_zoom(civ->graph->view, 1.2);
        view_size = sfView_getSize(civ->graph->view);
        if (view_size.y < 442.368)
            sfView_setSize(civ->graph->view, (sfVector2f){786.432, 442.368});
        else if (view_size.y > 2239.488)
            sfView_setSize(civ->graph->view, (sfVector2f){3981.312, 2239.488});
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
