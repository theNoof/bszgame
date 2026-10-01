#include "gui.h"
#include <stdio.h>
#include <stdlib.h>

const Color color_deep_abyss       = { .r = 0x08, .g = 0x0d, .b = 0x15, .a = 0xff };
const Color color_stormy_night     = { .r = 0x25, .g = 0x48, .b = 0x62, .a = 0xff };
const Color color_nightfall_blue   = { .r = 0x1f, .g = 0x29, .b = 0x37, .a = 0xff };
const Color color_midnight_thunder = { .r = 0x0d, .g = 0x15, .b = 0x26, .a = 0xff };
const Color color_twilight_blue    = { .r = 0x2c, .g = 0x54, .b = 0x84, .a = 0xff };
const Color color_pitch_black      = { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff };
const Color color_winter_sky       = { .r = 0xf3, .g = 0xf4, .b = 0xf6, .a = 0xff };
const Color color_slate_gray       = { .r = 0x83, .g = 0x8a, .b = 0x97, .a = 0xff };
const Color color_blaze_orange     = { .r = 0xff, .g = 0x90, .b = 0x00, .a = 0xff };
const Color color_lemon_zest       = { .r = 0xff, .g = 0xba, .b = 0x00, .a = 0xff };
const Color color_leafy_green      = { .r = 0x81, .g = 0xbe, .b = 0x83, .a = 0xff };
const Color color_dreamy_blue      = { .r = 0x6e, .g = 0xb0, .b = 0xff, .a = 0xff };
const Color color_crystal_blue     = { .r = 0x99, .g = 0xc7, .b = 0xff, .a = 0xff };
const Color color_sky_blue         = { .r = 0x45, .g = 0xb1, .b = 0xe8, .a = 0xff };
const Color color_moonlight_ocean  = { .r = 0x0c, .g = 0x14, .b = 0x20, .a = 0xff };
const Color color_rustic_red       = { .r = 0x54, .g = 0x0b, .b = 0x0c, .a = 0xff };
const Color color_ruby_glow        = { .r = 0xfa, .g = 0x79, .b = 0x70, .a = 0xff };
const Color color_walnut_brown     = { .r = 0x98, .g = 0x76, .b = 0x54, .a = 0xff };
const Color color_rustic_amber     = { .r = 0x9d, .g = 0x58, .b = 0x00, .a = 0xff };
const Color color_slate_purple     = { .r = 0xd2, .g = 0xa8, .b = 0xff, .a = 0xff };
const Color color_light_purple     = { .r = 0x75, .g = 0x33, .b = 0xbd, .a = 0xff };
const Color color_deep_purple      = { .r = 0x4c, .g = 0x17, .b = 0x85, .a = 0xff };

// ao color scheme
const Color color_bg             = color_deep_abyss;
const Color color_fg             = color_winter_sky;
const Color color_button_bg      = color_stormy_night;
const Color color_button_hovered = color_nightfall_blue;

Font font;

static const float font_size = 24.0f;
static const float font_spacing = 1.0f;

void init_gui(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "bszgame");
    SetExitKey(KEY_NULL);
    font = LoadFontEx("assets/agave/AgaveNerdFont-Regular.ttf", 120, NULL, 0);
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
        .min_x = cx - width / 2, .min_y = cy - (height + 1) / 2,
        .max_x = cx + width / 2, .max_y = cy + (height + 1) / 2,
    };
    int mx = GetMouseX();
    int my = GetMouseY();
    DrawRectangle(
        res.min_x, res.min_y,
        width, height,
        mx >= res.min_x && my >= res.min_y && mx <= res.max_x && my <= res.max_y ? color_button_bg : color_button_hovered
    );
    make_label(cx, cy, text);
    return res;
}

bool button_is_pressed(button b, int mouse_button) {
    int mx = GetMouseX();
    int my = GetMouseY();
    return IsMouseButtonPressed(mouse_button) && mx >= b.min_x && my >= b.min_y && mx <= b.max_x && my <= b.max_y;
}

void make_label(int cx, int cy, const char *text) {
    Vector2 measured = MeasureTextEx(font, text, font_size, font_spacing);
    DrawTextEx(font, text,
        (Vector2) { .x = cx - measured.x / 2, .y = cy - measured.y / 2 },
        font_size, font_spacing, color_fg
    );
}
