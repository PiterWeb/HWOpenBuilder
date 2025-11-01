#include <stdio.h>

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
#include <nuklear.h>
#define NK_SDL_RENDERER_IMPLEMENTATION
#include <nuklear_sdl_renderer.h>

int main() {
    lua_State *L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L);               // Load standard Lua libraries

    // Execute Lua script
    if (luaL_dofile(L, "./scripts/script.lua")) {
        printf("Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // Close the Lua state

    // Inicializar SDL2
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Nuklear + SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    // Inicializar Nuklear
    struct nk_context *ctx = nk_sdl_init(win, renderer);

    // --- CARGAR UNA FUENTE ---
    // Usar la fuente por defecto de Nuklear
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_default(atlas, 13, NULL);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &font->handle);
    // --- FIN DE CARGA DE FUENTE ---

    // Variables para la UI
    int slider_value = 50;
    int checkbox_value = 0;
    int running = 1;

    // Bucle principal
    while (running) {
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                running = 0;
            }
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        // Dibujar UI
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 220, 220),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE)) {

            nk_layout_row_dynamic(ctx, 30, 1);
            nk_label(ctx, "Slider:", NK_TEXT_LEFT);
            nk_slider_int(ctx, 0, &slider_value, 100, 1);

            nk_layout_row_dynamic(ctx, 25, 1);
            nk_checkbox_label(ctx, "Checkbox", &checkbox_value);

            nk_layout_row_dynamic(ctx, 25, 1);
            nk_label(ctx, slider_value > 50 ? "Mayor que 50" : "Menor que 50", NK_TEXT_LEFT);
        }
        nk_end(ctx);

        // Renderizar
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;

}
