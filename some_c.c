#include "davelog/c_helpers.h"

void foobs() {
    L_INFO("Hi from foobs!");
    L_ERROR("Something went wrong in C-land");
    L_NOTICE("Something requires notification from C-land");
};

