#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
const Color color_bg            = color_deep_abyss;
const Color color_fg            = color_winter_sky;
const Color color_elem_bg       = color_stormy_night;
const Color color_elem_hovered  = color_nightfall_blue;
const Color color_elem_selected = color_midnight_thunder;

const size_t margin = 3;

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

void make_button(button *b, int cx, int cy, int width, const char *text) {
    static const int height = 36;
    b->min_x = cx - width / 2;
    b->min_y = cy - height / 2;
    b->max_x = cx + (width + 1) / 2;
    b->max_y = cy + (height + 1) / 2;
    int mx = GetMouseX();
    int my = GetMouseY();
    b->is_clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mx >= b->min_x && my >= b->min_y
        && mx <= b->max_x && my <= b->max_y;
    DrawRectangle(
        b->min_x, b->min_y,
        width, height,
        /*b->is_clicked ? color_elem_selected : */ mx >= b->min_x && my >= b->min_y && mx <= b->max_x && my <= b->max_y ? color_elem_bg : color_elem_hovered
    );
    make_label(cx, cy, text);
}

void make_label(int cx, int cy, const char *text) {
    Vector2 measured = MeasureTextEx(font, text, font_size, font_spacing);
    DrawTextEx(font, text,
        (Vector2) { .x = cx - measured.x / 2, .y = cy - measured.y / 2 },
        font_size, font_spacing, color_fg
    );
}

void make_label_left(int x, int cy, const char *text) {
    Vector2 measured = MeasureTextEx(font, text, font_size, font_spacing);
    DrawTextEx(font, text,
        (Vector2) { .x = x, .y = cy - measured.y / 2 },
        font_size, font_spacing, color_fg
    );
}

void make_text_field(text_field *t, int cx, int cy, int width) {
    static const int height = 36;
    t->min_x = cx - width / 2;
    t->min_y = cy - height / 2;
    t->max_x = cx + (width + 1) / 2;
    t->max_y = cy + (height + 1) / 2;

    int mx = GetMouseX();
    int my = GetMouseY();
    // if cursor is in area of text field
    bool inr = mx >= t->min_x && my >= t->min_y && mx <= t->max_x && my <= t->max_y;

    if(t->cursor_pos >= 0) {
        const int k = GetCharPressed();
        // exit from field if escape pressed or clicked outside.
        if(IsKeyPressed(KEY_ESCAPE)
           || (!inr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            t->cursor_pos = -1;
        } else if(IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) { // backspace
            if(t->text_count > 0)
                t->text[--t->text_count] = 0;
        } else if(IsKeyPressed(KEY_LEFT)) {
            if(t->cursor_pos > 0)
                t->cursor_pos--;
        } else if(IsKeyPressed(KEY_RIGHT)) {
            if(t->cursor_pos < (int) t->text_count)
                t->cursor_pos++;
        } else if(k != KEY_NULL) {
            if(t->text_count + 1 >= t->text_capacity) { // extend array in text field
                t->text_capacity += 32;
                t->text = realloc(t->text, t->text_capacity);
                for(size_t i = t->text_count; i < t->text_capacity; i++)
                    t->text[i] = '\0';
            }
            t->text[t->text_count++] = k;
            t->cursor_pos++;
        }
    }
    if(inr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        t->cursor_pos = t->text == NULL ? 0 : strlen(t->text) - 2;
    DrawRectangle(
        t->min_x, t->min_y,
        width, height,
        t->cursor_pos >= 0 ? color_elem_selected : inr ? color_elem_bg : color_elem_hovered
    );
    make_label_left(cx + margin - width / 2, cy, t->text);
    if(t->cursor_pos >= 0) { // draw cursor
        char text[t->cursor_pos + 1];
        strncpy(text, t->text, t->cursor_pos);
        const Vector2 offset = MeasureTextEx(font, text, font_size, font_spacing);
        printf("offset.x = %f\n", offset.x);
        DrawRectangle(cx + margin + (int) offset.x - width / 2, cy - (height / 2 + 1) + 4, 2, font_size + 4, color_fg);
    }
}
