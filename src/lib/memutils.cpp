#include <lib/memutils.hpp>

void memset(void *src, int64_t data, uint64_t count) {
    asm volatile("rep stosb" : "=D"(src),"=c"(count) : "0"(src), "a"(data), "1"(count) : "memory");
}
