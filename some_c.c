#include "dlog/c_helpers.h"

void foobs() {
    L(info, "Hi from foobs!");
    L(error, "Something went wrong in C-land");
    L(notice, "Something requires notification from C-land");
};

