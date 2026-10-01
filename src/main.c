#include "gui.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

enum ui_state {
    UI_MAIN_MENU,
    UI_HOST_GAME,
} ui_state = UI_MAIN_MENU;

button mm_join_button = {0};
button mm_host_button = {0};
button mm_edit_button = {0};
button mm_quit_button = {0};

void render_main_menu(void) {
    const int w = GetScreenWidth();
    const int h = GetScreenHeight();

    make_label(w / 2, (h / 2) - 300, "BSZetGame");
    make_button(&mm_join_button, w / 2, (h / 2) - 200, 300, "Join Game");
    make_button(&mm_host_button, w / 2, (h / 2) - 150, 300, "Host Game");
    make_button(&mm_edit_button, (w - 160) / 2, (h / 2) - 100, 140, "Edit Map");
    make_button(&mm_quit_button, (w + 160) / 2, (h / 2) - 100, 140, "Quit");
}

text_field hm_port_in = default_text_field;

void render_host_menu(void) {
    const int w = GetScreenWidth();
    const int h = GetScreenHeight();

    make_text_field(&hm_port_in, w / 2, h / 2, 300);
}

int main(void) {
    init_gui();

    while(!WindowShouldClose()) {
        if(mm_quit_button.is_clicked) {
            deinit_gui();
            exit(0);
        } else if(mm_join_button.is_clicked) {
            printf("imagine you joined a game now...\n");
        } else if(mm_host_button.is_clicked) {
            ui_state = UI_HOST_GAME;
        } else if(mm_edit_button.is_clicked) {
            printf("imagine you could edit a game now...\n");
        }

        BeginDrawing();
        ClearBackground(GetColor(0x181818ff));

        DrawFPS(2, 2);

        switch(ui_state) {
            case UI_MAIN_MENU: render_main_menu(); break;
            case UI_HOST_GAME: render_host_menu(); break;
        }

        EndDrawing();
    }

    deinit_gui();
    
    return 0;
}
