#include "gui.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

enum ui_state {
    UI_MAIN_MENU,
} ui_state = UI_MAIN_MENU;

int main(void) {
    init_gui();

    button start_button = {0};
    button quit_button = {0};

    while(!WindowShouldClose()) {
        if(is_pressed(quit_button, MOUSE_BUTTON_LEFT)) {
            deinit_gui();
            exit(0);
        } else if(is_pressed(start_button, MOUSE_BUTTON_LEFT)) {
            printf("button pressed!\n");
        }

        BeginDrawing();
        ClearBackground(GetColor(0x181818ff));

        const int w = GetScreenWidth();
        const int h = GetScreenHeight();

        start_button = make_button(w / 2, (h / 2) - 100, 300, "Start Game");
        quit_button = make_button(w / 2, (h / 2) - 50, 300, "Quit");

        DrawFPS(2, 2);

        EndDrawing();
    }

    deinit_gui();
    
    return 0;
}
