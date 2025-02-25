#include <cstdio>
#include <cstdlib>
#include <random>

#include "dlog/log.h"
#include "derr/valueor.hpp"
#include "some_c.h"

bool randomBoolean() {
  static std::default_random_engine generator(std::random_device{}());
  static std::bernoulli_distribution distribution(0.5);
  return distribution(generator);
}

struct bloop_t {
    int32_t aaa;
    std::string bbb;
};

derr::ValueOr<bloop_t> bloopify() {
    if (randomBoolean()) {
        return bloop_t{.aaa = 42, .bbb = "everything is fine!" };
    }
    return derr::Error(derr::errors_e::loss, "data was lost");
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {

    const dlog::InitList_t initlist = {
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
    for (uint32_t i=0; i<10; i++) {
        auto rv = bloopify();
        if (rv.ok()) {
            L(info, std::format("bloop_t: {}, {}", rv.value().aaa, rv.value().bbb));
        } else {
            L(error, rv.why());
        }
    }
    L(vverbose, "yadda yadda yadda");
    L(debug, "this is a debug message");
    LOGGER << "Well this is another way to do it" << L_ENDL(debug);
    LOGGER << "Die! Die! Die!" << L_ENDL(fatal);
    L(info, "and now we're leaving, bye!");

    return 0;
}

