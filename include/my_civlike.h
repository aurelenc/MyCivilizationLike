/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#ifndef MY_CIVLIKE_H_
#define MY_CIVLIKE_H_

#include <SFML/Graphics.h>
#include <stdbool.h>

#define MAX_TILES 516

typedef enum tile_type_e {
    PLAINS,
    GRASSLAND,
    DESERT,
    TUNDRA,
    SNOW,
    COAST,
    LAKE,
    OCEAN,
    MOUNTAINS,
    TILE_TYPE_COUNT
} tile_type_t;

typedef struct tile_s {
    tile_type_t type;
    bool is_building;
    bool is_civil_unit;
    bool is_military_unit;
    bool selected;
    sfVector2f pos;
    sfConvexShape *hex;
    sfVector2f *positions;
} tile_t;

typedef struct graph_s {
    sfRenderWindow *window;
    sfConvexShape *hex;
    sfVector2f *hex_vectors;
    tile_t **tiles;
    sfVector2f *positions;
    sfTexture **tile_base_textures;
    sfView *view;
    sfClock *view_clock;
} graph_t;

typedef struct civlike_s {
    graph_t *graph;
    int selected_tile;
} civlike_t;

#endif /* !MY_CIVLIKE_H_ */
