#include <cstdio>
#include <cstdlib>

#include "davelog/log.h"
#include "some_c.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    dave::log::InitLogger("demo_output.json");
    L(info, "This is the logger talking!");
    L(warning, "The number is %d, that is %s", 42, "great!");
    L(error, "%d is a bad return value", -1);
    foobs(); 
    L(very_verbose, "yadda yadda yadda");
    LOGGER << "Well this is another way to do it" << L_ENDL(debug);
    LOGGER << "We should probably die" << L_ENDL(fatal);
    L(info, "Is this working?");
    return 0;
}

