// Lua
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Nuklear
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_ASSERT
#include <nuklear.h>
#define NK_SDL_RENDERER_IMPLEMENTATION
#include <nuklear_sdl_renderer.h>
#include "SDL_video.h"

// Project
#include <stdio.h>
#include "window_events.c"
#include "node.c"
#include "component.c"

int main() {
    lua_State *L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L);               // Load standard Lua libraries

    // Execute Lua script
    if (luaL_dofile(L, "./components/main.lua")) {
        printf("Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // Close the Lua state

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("HWOpenBuilder",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    struct nk_context *ctx = nk_sdl_init(win, renderer);

    // Cargar fuente
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_default(atlas, 13, NULL);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &font->handle);

    struct components* components = get_components();

    int running = 1;
    while (running) {
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            handle_window_events(&running, evt, win);
        }
        nk_input_end(ctx);

        node_editor(ctx, components);

        // UI de ejemplo
        // if (nk_begin(ctx, "Main", nk_rect(50, 50, 220, 220),
        //     NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE)) {
        //     nk_layout_row_dynamic(ctx, 0, 1);
        //     nk_label(ctx, "Presiona F11 para pantalla completa", NK_TEXT_CENTERED);
        // }
        // nk_end(ctx);
        // Renderizar
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_RenderPresent(renderer);
    }

    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;

}
