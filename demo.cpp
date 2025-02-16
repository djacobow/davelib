#include <cstdio>
#include <cstdlib>

#include "davelog/log.h"
#include "some_c.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    dave::log::InitLogger("demo_output.json");
    L_INFO("This is the logger talking!");
    foobs(); 
    L_FATAL("Oh, no!");
    return 0;
}

