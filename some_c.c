#include "dave/c_helpers.h"

void foobs(void) {
    L_(info, "Hi from foobs!");
    L_(error, "Something went wrong in C-land");
    L_(notice, "Something requires notification from C-land");
}

