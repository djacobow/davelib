#include <cstdio>
#include <format>
#include <random>
#include <ranges>

#include "dave/error.h"
#include "dave/log.h"
#include "dave/valueor.hpp"
#include "some_c.h"


auto randomBoolean() -> bool {
  static std::default_random_engine generator(std::random_device{}());
  static std::bernoulli_distribution distribution(0.5);
  return distribution(generator);
}

struct bloop_t {
    int32_t aaa;
    std::string bbb;
};

auto bloopify(int i) -> dave::err::ValueOr<bloop_t> {
    if (randomBoolean()) {
        return bloop_t{.aaa = i, .bbb = "everything is fine!" };
    }
    return E_(data_loss, "data was lost");
}

auto makeTrue() -> dave::err::ValueOr<bool> {
    if (randomBoolean()) {
        return true;
    }
    return E_(aborted, "we don't like false");
}

void demo_valueor() {
    for (auto i : std::ranges::views::iota(0,10)) {
        auto rv0 = bloopify(i);
        if (rv0.ok()) {
            L_(info, std::format("bloop_t: {}, {}", rv0.v().aaa, rv0.v().bbb));
        } else {
            L_(error, rv0.why());
        }
        auto rv1 = makeTrue();
        if (rv1.ok()) {
            L_(info, std::format("value was: {}", rv1.v()));
        } else {
            L_(error, rv1.why());
        }
    }
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {

    const dave::log::InitList_t initlist = {
        dave::log::InitInfo_t{
            "console",
            stdout,
            dave::log::LevelMask_c().AtOrAbove(dave::log::Level_e::debug),
            dave::log::Style_e::tight
        },
        dave::log::InitInfo_t{
            "logfile",
            fopen("demo_output.json", "ae"),
            dave::log::LevelMask_c().All(),
            dave::log::Style_e::json
        },
    };

    dave::log::Init(initlist);

    L_(info, "This is the logger talking!");
    L_(info, "Nothing special here, kinda boring.");
    L_(debug, "but maybe not as boring as this?");
    L_(warning, "The number is %d, that is %s", 42, "great!");
    L_(error, "%d is a bad return value", -1);
    foobs(); 
    demo_valueor();

    L_(vverbose, "yadda yadda yadda");
    L_(debug, "this is a debug message");
    LOGGER << "Well this is another way to do it" << L_ENDL(debug);
    LOGGER << "Die! Die! Die!" << L_ENDL(fatal);
    L_(info, "and now we're leaving, bye!");

    return 0;
}

