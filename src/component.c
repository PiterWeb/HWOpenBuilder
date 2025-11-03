#include "headers/component.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "headers/util.h"


struct components *get_components() {
    struct components *components = malloc(sizeof(struct components));
    components->n = 0;
 
    
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./components")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir(dir)) != NULL) {
        if (!str_ends_with(ent->d_name, ".lua")) {
            continue;
        }
        printf ("%s\n", ent->d_name);
      }
      closedir(dir);
    } else {
      /* could not open directory */
      perror("");
      return components;
    }
    
    components->n = 1;
    components->arr_component = malloc(sizeof(struct component));
    
    struct component c;
    c.name = "Test component";
    
    components->arr_component[0] = c;
    
    return components;
}