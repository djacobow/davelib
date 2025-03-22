#pragma once

#include <array>
#include <string>

/*

These macros are kind of an abomination, but they address an annoying shortcoming
in c++, which is that we can't get reflected strings for the names of enums.
To make easier debugging, it's nice to get the enums real names.

These macros can be used to create the enum and to create a function that
returns the name of the value given the enum. Templates are not much use here,
either.

Use:

Let's say you want to make an enum of colors. First, make a macro that lists all
the members, but each as an argument to another macro which will be passed into
the list later:

    #define COLORS_LIST(X) X(red) X(orange) X(yellow) X(green) X(blue) X(indigo) X(violet)

Then create the type like this. Note that the last two arguments are the first
and last elements of the list and there's no macro-ish way to get them so you
have to provide them. These are used to make the enum iterable, which is a useful
thing to have:

    EH_DECL_EUM(Colors_e, COLORS_LIST, red, violet);

Finally, you can instantiate the function to get the strings:

    EH_IMPL_ENUM_STRINGIFRER(get_colors_strs, Colors_e, COLORS_LIST);

(There is also an EH_DECL_ENUM_STRINGIFIER to put into header files);

*/

#define EH_MAKE_VAL(V) V,
#define EH_MAKE_STR(V) #V,

#define EH_DECL_ENUM(TYPENAME, LIST, FIRST, LAST) \
    enum class TYPENAME { LIST(EH_MAKE_VAL) begin = (FIRST), end = (LAST) }

#define EH_DECL_ENUM_STRINGIFIER(NAME, TYPENAME) const std::string NAME(TYPENAME t)

#define EH_IMPL_ENUM_STRINGIFIER(NAME, TYPENAME, LIST) \
    EH_DECL_ENUM_STRINGIFIER(NAME, TYPENAME) { \
        static const std::array names = {LIST(EH_MAKE_STR)}; \
        auto idx = static_cast<std::underlying_type_t<decltype(t)> >(t); \
        return std::string(names[static_cast<unsigned>(idx)]); \
    }
