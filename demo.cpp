#include <cstdio>
#include <cstdlib>

#include "dlog/log.h"
#include "some_c.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {

    dlog::InitList_t initlist = {
        dlog::InitInfo_t{
            "console",
            stdout,
            dlog::LevelMask_c().AtOrAbove(dlog::Level_e::debug),
            dlog::Style_e::tight
        },
        dlog::InitInfo_t{
            "logfile",
            fopen("demo_output.json", "a"),
            dlog::LevelMask_c().All(),
            dlog::Style_e::json
        },
    };

    dlog::Init(initlist);

    L(info, "This is the logger talking!");
    L(info, "Nothing special here, kinda boring.");
    L(debug, "but maybe not as boring as this?");
    L(warning, "The number is %d, that is %s", 42, "great!");
    L(error, "%d is a bad return value", -1);
    foobs(); 
    L(vverbose, "yadda yadda yadda");
    L(debug, "this is a debug message");
    LOGGER << "Well this is another way to do it" << L_ENDL(debug);
    LOGGER << "Die! Die! Die!" << L_ENDL(fatal);
    L(info, "and now we're leaving, bye!");
    return 0;
}

