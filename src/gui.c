#include "gui.h"
#include <stdio.h>
#include <stdlib.h>

const Color color_bg             = { .r = 0x18, .g = 0x18, .b = 0x18, .a = 0xff };
const Color color_fg             = { .r = 0xe4, .g = 0xe4, .b = 0xef, .a = 0xff };
const Color color_button_hovered = { .r = 0x45, .g = 0x3d, .b = 0x41, .a = 0xff };
const Color color_button_bg      = { .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff };

Font font;

static const float font_size = 24.0f;
static const float font_spacing = 1.0f;

void init_gui(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "bszgame");
    SetExitKey(KEY_NULL);
    font = LoadFontEx("assets/agave/AgaveNerdFont-Regular.ttf", font_size, NULL, 0);
    if(!IsFontValid(font)) {
        fprintf(stderr, "ERROR: invalid font.");
        exit(69);
    }
    SetTargetFPS(60);
}

void deinit_gui(void) {
    CloseWindow();
}

button make_button(int cx, int cy, int width, const char *text) {
    static const int height = 36;
    button res = {
        .min_x = cx - (width / 2), .min_y = cy - (height / 2),
        .max_x = cx + (width / 2), .max_y = cy + (height / 2),
    };
    int mx = GetMouseX();
    int my = GetMouseY();
    DrawRectangle(
        res.min_x, res.min_y,
        width, height,
        mx >= res.min_x && my >= res.min_y && mx <= res.max_x && my <= res.max_y ? color_button_hovered : color_button_bg
    );
    Vector2 measured = MeasureTextEx(font, text, font_size, font_spacing);
    DrawTextEx(font, text,
        (Vector2) { .x = cx - measured.x / 2, .y = cy - measured.y / 2 },
        font_size, font_spacing, color_fg
    );
    return res;
}

bool is_pressed(button b, int mouse_button) {
    int mx = GetMouseX();
    int my = GetMouseY();
    return IsMouseButtonPressed(mouse_button) && mx >= b.min_x && my >= b.min_y && mx <= b.max_x && my <= b.max_y;
}

