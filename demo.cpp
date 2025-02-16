#include <cstdio>
#include <cstdlib>

#include "davelog/log.h"
#include "some_c.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    dave::log::InitLogger("demo_output.json");
    L_INFO("This is the logger talking!");
    L_WARNING("The number is %d, that is %s", 42, "great!");
    L_ERROR("%d is a bad return value", -1);
    foobs(); 
    L_VVERBOSE("yadda yadda yadda");
    dave::log::Logger_c::Get() << "Well this is another way to do it" << L_ENDL_DEBUG;
    dave::log::Logger_c::Get() << "We should probably die" << L_ENDL_FATAL;
    return 0;
}

