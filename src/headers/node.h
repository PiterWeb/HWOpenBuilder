#ifndef PROJECT_NODE
    #define PROJECT_NODE
    #include <stdint.h>
    #include <math.h>
    #include <stdio.h>
    #include <string.h>
    
    #ifndef NK_IMPLEMENTATION
        #include <nuklear.h>
    #endif

    
    struct node {
       int ID;
       char name[32];
       struct nk_rect bounds;
       uint8_t input_count;
       uint8_t output_count;
       struct node *next;
       struct node *prev;
    };
   
    struct node_link {
        int input_id;
        int input_slot;
        int output_id;
        int output_slot;
        struct nk_vec2 in;
        struct nk_vec2 out;
    };
    
    struct node_linking {
        int active;
        struct node *node;
        int input_id;
        int input_slot;
    };
    
    struct node_editor {
        int initialized;
        struct node node_buf[32];
        struct node_link links[64];
        struct node *begin;
        struct node *end;
        int node_count;
        int link_count;
        struct nk_rect bounds;
        struct node *selected;
        int show_grid;
        struct nk_vec2 scrolling;
        struct node_linking linking;
    };
    
    static struct node_editor nodeEditor;
    
#endif