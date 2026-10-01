#include "gui.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

enum ui_state {
    UI_MAIN_MENU,
} ui_state = UI_MAIN_MENU;

int main(void) {
    init_gui();

    button join_button = {0};
    button host_button = {0};
    button edit_button = {0};
    button quit_button = {0};

    while(!WindowShouldClose()) {
        if(button_is_pressed(quit_button, MOUSE_BUTTON_LEFT)) {
            deinit_gui();
            exit(0);
        } else if(button_is_pressed(join_button, MOUSE_BUTTON_LEFT)) {
            printf("imagine you joined a game now...\n");
        } else if(button_is_pressed(host_button, MOUSE_BUTTON_LEFT)) {
            printf("imagine you could host a game now...\n");
        } else if(button_is_pressed(edit_button, MOUSE_BUTTON_LEFT)) {
            printf("imagine you could edit a game now...\n");
        }

        BeginDrawing();
        ClearBackground(GetColor(0x181818ff));

        const int w = GetScreenWidth();
        const int h = GetScreenHeight();

        make_label(w / 2, (h / 2) - 300, "BSZetGame");
        join_button = make_button(w / 2, (h / 2) - 200, 300, "Join Game");
        host_button = make_button(w / 2, (h / 2) - 150, 300, "Host Game");
        edit_button = make_button((w - 160) / 2, (h / 2) - 100, 140, "Edit Map");
        quit_button = make_button((w + 160) / 2, (h / 2) - 100, 140, "Quit");

        DrawFPS(2, 2);

        EndDrawing();
    }

    deinit_gui();
    
    return 0;
}
