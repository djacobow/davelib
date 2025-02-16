#pragma once

#include <ranges>

// Generate a C++20 "range" iterating from the enum value `first` to `last`,
// inclusive, to be used in modern C++ range-based for loops.
// - This is also using the C++20 feature of "abbreviated function templates",
//   or "template argument deduction for functions", where `auto` can be used
//   for all input parameter types and for the return type in place of making
//   this a function template.
constexpr auto enum_range(auto first, auto last) {
    auto enum_range = std::views::iota(
                          static_cast<std::underlying_type_t<decltype(first)> >(first),
                          static_cast<std::underlying_type_t<decltype(last)> >(last) + 1
                      )
        | std::views::transform([](auto enum_val) {
                          return static_cast<decltype(first)>(enum_val);
                      });

    return enum_range;
};
