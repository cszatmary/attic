#include "color.h"
#include <stdlib.h>

// Support for NO_COLOR env var
// https://no-color.org/
bool no_color = false;

void color_init(void) {
    char *nc = getenv("NO_COLOR");
    // The standard says the value doesn't matter, only whether or not it's set
    if (nc != NULL && nc[0] != '\0') {
        no_color = true;
    }
}

bool color_enabled(void) {
    return !no_color;
}
