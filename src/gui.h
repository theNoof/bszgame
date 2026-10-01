#pragma once

#include <raylib.h>

typedef struct button {
    int min_x;
    int min_y;
    int max_x;
    int max_y;
} button;

void init_gui(void);
void deinit_gui(void);

/** buttons **/
button make_button(int cx, int cy, int width, const char *text);
bool button_is_pressed(button b, int mouse_button); // MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT, MOUSE_BUTTON_MIDDLE

/** labels **/
void make_label(int cx, int cy, const char *text);
