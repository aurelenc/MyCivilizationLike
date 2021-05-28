/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#include "my_civlike.h"
#include <stdlib.h>

int init_tiles(graph_t *graph)
{
    sfVector2f pos = {0, 0};
    bool step = false;
    int x = 0;

    graph->tiles = calloc(sizeof(tile_t *), MAX_TILES + 1);
    if (!graph->tiles)
        return (-1);
    for (int i = 0; i < MAX_TILES; i++) {
        graph->tiles[i] = calloc(sizeof(tile_t), 1);
        if (!graph->tiles[i])
            return (-1);
        graph->tiles[i]->type = PLAINS;
        graph->tiles[i]->selected = false;
        graph->tiles[i]->pos = pos;
        if (x <= MAP_SIZE_X) {
            pos.x += 181;
            x += 1;
        } else {
            pos.x = 0;
            x = 0;
            pos.y += 52;
            if (step == false) {
                step = true;
                pos.x += 91;
            } else
                step = false;
        }
    }
    return (0);
}

int init_graph(civlike_t *civ)
{
    sfConvexShape *hex = civ->graph->hex;

    sfRenderWindow_setFramerateLimit(civ->graph->window, 60);
    sfConvexShape_setPointCount(hex, 6);
    civ->graph->hex_vectors[0] = (sfVector2f){0, 60};
    civ->graph->hex_vectors[1] = (sfVector2f){30, 112};
    civ->graph->hex_vectors[2] = (sfVector2f){90, 112};
    civ->graph->hex_vectors[3] = (sfVector2f){120, 60};
    civ->graph->hex_vectors[4] = (sfVector2f){90, 8};
    civ->graph->hex_vectors[5] = (sfVector2f){30, 8};
    for (int i = 0; i < 6; i++)
        sfConvexShape_setPoint(hex, i, civ->graph->hex_vectors[i]);
    // sfCircleShape_setRadius(hex, 60);
    sfConvexShape_setOrigin(hex, (sfVector2f){60, 60});
    // sfConvexShape_setRotation(hex, 30);
    sfConvexShape_setFillColor(hex, sfWhite);
    sfConvexShape_setOutlineColor(hex, sfBlack);
    sfConvexShape_setOutlineThickness(hex, 1);
    sfConvexShape_setPosition(hex, (sfVector2f){60, 60});
    return (0);
}

int create_graph(civlike_t *civ)
{
    sfVideoMode mode = {1920, 1080, 32};

    civ->graph = calloc(sizeof(graph_t), 1);
    if (!civ->graph)
        return (-1);
    civ->graph->window = sfRenderWindow_create(mode, "MyCivilizationLike", sfDefaultStyle, NULL);
    if (!civ->graph->window)
        return (-1);
    civ->graph->hex = sfConvexShape_create();
    if (!civ->graph->hex)
        return (-1);
    civ->graph->hex_vectors = calloc(sizeof(sfVector2f), 6 + 1);
    if (!civ->graph->hex_vectors)
        return (-1);
    civ->graph->tiles = calloc(sizeof(tile_t), MAX_TILES + 1);
    if (!civ->graph->tiles)
        return (-1);
    return (0);
}

int init_textures(civlike_t *civ)
{
    civ->graph->tile_base_textures = calloc(sizeof(sfTexture *), TILE_TYPE_COUNT + 1);
    civ->graph->tile_base_textures[PLAINS] = sfTexture_createFromFile("assets/textures/tiles/plains.jpg", NULL);
    civ->graph->tile_base_textures[GRASSLAND] = sfTexture_createFromFile("assets/textures/tiles/grassland.jpg", NULL);
    civ->graph->tile_base_textures[DESERT] = sfTexture_createFromFile("assets/textures/tiles/desert.jpg", NULL);
    civ->graph->tile_base_textures[TUNDRA] = sfTexture_createFromFile("assets/textures/tiles/tundra.jpg", NULL);
    civ->graph->tile_base_textures[SNOW] = sfTexture_createFromFile("assets/textures/tiles/snow.jpg", NULL);
    civ->graph->tile_base_textures[COAST] = sfTexture_createFromFile("assets/textures/tiles/coast.jpg", NULL);
    civ->graph->tile_base_textures[LAKE] = sfTexture_createFromFile("assets/textures/tiles/coast.jpg", NULL);
    civ->graph->tile_base_textures[OCEAN] = sfTexture_createFromFile("assets/textures/tiles/ocean.jpg", NULL);
    civ->graph->tile_base_textures[MOUNTAINS] = sfTexture_createFromFile("assets/textures/tiles/mountains.jpg", NULL);
    for (int i = 0; i < TILE_TYPE_COUNT; i++) {
        if (!civ->graph->tile_base_textures[i])
            return (-1);
    }
    civ->selected_tile = 0;
    return (0);
}

int init_view(civlike_t *civ)
{
    civ->graph->view = sfView_create();
    if (!civ->graph->view)
        return (-1);
    civ->graph->view_clock = sfClock_create();
    if (!civ->graph->view_clock)
        return (-1);
    sfView_setSize(civ->graph->view, (sfVector2f){1920, 1080});
    sfView_setCenter(civ->graph->view, (sfVector2f){1920 / 2, 1080 / 2});
    sfRenderWindow_setView(civ->graph->window, civ->graph->view);
    return (0);
}

int init_civ(civlike_t *civ)
{
    if (create_graph(civ) < 0)
        return (-1);
    if (init_graph(civ) < 0)
        return (-1);
    if (init_textures(civ) < 0)
        return (-1);
    if (init_tiles(civ->graph) < 0)
        return (-1);
    load_map(civ);
    if (init_view(civ) < 0)
        return (-1);
    return (0);
}
