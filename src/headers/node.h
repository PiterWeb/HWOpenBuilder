#include <stdint.h>

struct HW_NODE {
    uintmax_t instance;
    char *id;
    uint8_t n_input_signals;
    uint8_t n_output_signals;
    char **inputs_signals;
    char **output_signals;
};