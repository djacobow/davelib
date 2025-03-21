#pragma once

#include <string>
#include <vector>
#include <cstdio>

#include "dave/inc/log/levels.h"
#include "dave/inc/log/styles.h"

namespace dave::log {

struct InitInfo_t {
    std::string name;
    FILE *file_ptr;
    LevelMask_c level_mask;
    Style_e style;
};

using InitList_t = std::vector<InitInfo_t>;

// Logger is initialized via a list of file pointers.
// The init struct takes:
//  - a name
//  - a pointer
//  - a mask of levels ot print (a mask is used so the list can be non-contiguous)
//  - what formatting style to use
void Init(const InitList_t &initlist);

} // namespace dave::log
