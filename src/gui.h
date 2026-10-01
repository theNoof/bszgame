#pragma once

#include <raylib.h>
#include <stddef.h>

void init_gui(void);
void deinit_gui(void);

/** buttons **/
typedef struct button {
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    bool is_clicked;
} button;

void make_button(button *b, int cx, int cy, int width, const char *text);

/** labels **/
void make_label(int cx, int cy, const char *text);
void make_label_left(int x, int cy, const char *text);

/** text fields **/
typedef struct text_field {
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    char *text;
    size_t text_count;
    size_t text_capacity;
    int cursor_pos; // < 0 -> not selected.
} text_field;
static const text_field default_text_field = {
    .min_x = 0,
    .min_y = 0,
    .max_x = 0,
    .max_y = 0,
    .text = NULL,
    .text_count = 0,
    .text_capacity = 0,
    .cursor_pos = -1,
};
void make_text_field(text_field *t, int cx, int cy, int width);
