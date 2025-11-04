#ifndef PROJECT_COMPONENT
    #define PROJECT_COMPONENT
    
    #include <stdint.h>
    struct component {
      char *name;
    };
    
    struct components {
        struct component *arr_component;
        uint32_t n;
    };
    
   struct components *get_components();
   
   void free_components(struct components * components);
    
 #endif