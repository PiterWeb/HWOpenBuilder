#include "headers/component.h"
#include <stdlib.h>

struct components *get_components() {
    struct components *components = malloc(sizeof(struct components));
    components->n = 1;
    components->arr_component = malloc(sizeof(struct component));
    
    struct component c;
    c.name = "Test component";
    
    components->arr_component[0] = c;
    
    return components;
}