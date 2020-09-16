#pragma once


#include <stdint.h>

namespace kernel {

void memset(void *src, int64_t data, uint64_t count);

}