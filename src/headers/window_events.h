#ifndef PROJECT_WINDOW_EVENTS
    #define PROJECT_WINDOW_EVENTS
    #include <SDL_events.h>
    
    #ifndef NK_IMPLEMENTATION
    #include <nuklear.h>
    #endif
    
    #ifndef NK_SDL_RENDERER_IMPLEMENTATION
    #include <nuklear_sdl_renderer.h>
    #endif

    void handle_window_events(int *running, SDL_Event evt, SDL_Window *win);
#endif