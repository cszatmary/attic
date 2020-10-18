#ifndef ATTIC_COLOR_H
#define ATTIC_COLOR_H

#include <stdbool.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[39m"

// color_init initializes any color configuration from the environment.
void color_init(void);

// color_enabled whether or not color is allowed to be used.
bool color_enabled(void);

// GREEN creates a green colored string.
#define GREEN(s) color_enabled() ? COLOR_GREEN s COLOR_RESET : s

#endif  // ATTIC_COLOR_H
