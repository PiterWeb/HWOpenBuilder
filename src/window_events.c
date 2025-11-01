#include "headers/window_events.h"

void handle_window_events(int *running, SDL_Event evt, SDL_Window *win) {
    if (evt.type == SDL_QUIT) {
        *running = 0;
    } else if (evt.type == SDL_KEYDOWN) {
        if (evt.key.keysym.sym == SDLK_F11) {
            Uint32 flags = SDL_GetWindowFlags(win);
            if (flags & SDL_WINDOW_FULLSCREEN) {
                SDL_SetWindowFullscreen(win, 0);
            } else {
                SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
        }
    } else if (evt.type == SDL_WINDOWEVENT) {
        if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
            int new_width = evt.window.data1;
            int new_height = evt.window.data2;
            printf("Ventana redimensionada: %dx%d\n", new_width, new_height);
        }
    }
    nk_sdl_handle_event(&evt);
}
