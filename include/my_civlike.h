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

#define MAX_TILES 512

typedef enum tile_type_e {
    PLAINS,
    GRASSLANDS,
    FOREST,
    DESERT,
    MOUNTAINS,
    OCEAN,
    WATER,
    SNOW,
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
    tile_t *tiles;
    sfVector2f *positions;
} graph_t;

typedef struct civlike_s {
    graph_t *graph;
} civlike_t;

#endif /* !MY_CIVLIKE_H_ */
