/*
** github.com/aurelenc, 2021
** MyCivilizationLike
** File description:
** my_civlike
*/

#ifndef MY_UI_H_
#define MY_UI_H_

typedef enum ui_event_type_e
{
    UI_EVENT_NONE,
    UI_EVENT_BLOCK,
    UI_EVENT_PASSTHROUGH_SELF,
    UI_EVENT_PASSTHROUGH_SELF_CHILDREN,
} ui_event_type_t;

typedef enum ui_elem_type_e
{
    UI_ELEM_INERT,
    UI_ELEM_CLICKABLE,
} ui_elem_type_t;

typedef struct ui_elem_s
{
    ui_elem_type_t type;
    void *(*on_click)(void *);
    sfVector2f pos;
    sfConvexShape *shape;
} ui_elem_t;

#endif
