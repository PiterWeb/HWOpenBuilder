#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "headers/component.h"
#include "headers/util.h"

static int count_components_in_folder() {
        
    int n_components = 0;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./components")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir(dir)) != NULL) {
        if (!str_ends_with(ent->d_name, ".component.lua")) {
            continue;
        }
        n_components += 1;  
      }
      closedir(dir);
    } else {
      /* could not open directory */
      perror("");
      return 0;
    }
    
    return n_components;
    
}

struct components *get_components() {
    struct components *components = malloc(sizeof(struct components));
    components->n = 0;

    int n_components_in_folder = count_components_in_folder();
    
    // Allocate components
    components->arr_component = malloc(sizeof(struct component) * n_components_in_folder);
    
    const int dot_component_dot_lua_len = strlen(".component.lua");
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./components")) != NULL) {
      /* print all the .lua files within directory */
      while ((ent = readdir(dir)) != NULL) {
        if (!str_ends_with(ent->d_name, ".component.lua")) {
            continue;
        }
        
        const int d_name_len = strlen(ent->d_name);
        
        char *base_name = malloc(sizeof(ent->d_name) - sizeof(".component.lua"));
        strncpy(base_name, ent->d_name, (d_name_len - dot_component_dot_lua_len));
        
        components->arr_component[components->n].name = base_name;
        
        components->n = components->n + 1;  
      }
      closedir(dir);
    } else {
      /* could not open directory */
      perror("");
      return components;
    }
    
    return components;
}

void free_components(struct components *components) {
    
    for (uint32_t n = 0; n < components->n; n++) {
        struct component c = components->arr_component[n];
        printf("Free component[%d] name [%s]\n", n, c.name);
        free(c.name);
    }
    
    printf("Free components arr\n");
    free(components->arr_component);
    
    printf("Free components struct\n");
    free(components);
    
}

void refresh_components(struct components **components) {
    free_components(*components);
    *components = get_components();
}