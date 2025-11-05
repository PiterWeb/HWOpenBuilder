// Lua
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Project
#include <stdlib.h>
#include <string.h>
#include "headers/component.h"
#include "headers/run_lua.h"

int run_lua_components(struct components *components) {
    
    lua_State *L = luaL_newstate();  // Crear un nuevo estado Lua
    luaL_openlibs(L);  // Abrir las bibliotecas estándar de Lua
    luaL_loadfile(L, "./components/component.lua");
    
    for (uint32_t n = 0; n < components->n; ++n) {
        // Cargar el archivo que devuelve la instancia del componente
        char *file_name = malloc(sizeof("./components/") + sizeof(components->arr_component[n].name) + sizeof(".component.lua"));
        strcpy(file_name, "./components/");
        strcat(file_name, components->arr_component[n].name);
        strcat(file_name,".component.lua");
        
        if (luaL_dofile(L, (const char*)file_name) != LUA_OK) {
            fprintf(stderr, "Error loading %s: %s\n", file_name ,lua_tostring(L, -1));
            return 1;
        }
    
        // Ahora, la instancia del componente está en la parte superior de la pila
    
        // Obtener el método update de la instancia del componente
        lua_getfield(L, -1, "update");
    
        // Pasamos self como argumento
        lua_pushvalue(L, -2);
        
        // Llamar al método update
        if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
            fprintf(stderr, "Error calling update: %s\n", lua_tostring(L, -1));
            return 1;
        }
    }

    // Cerrar el estado Lua
    lua_close(L);
    return 0;
    
}