#ifndef __LIB__BLIB_H__
#define __LIB__BLIB_H__

#include <stddef.h>
#include <stdint.h>

#define ALIGN_UP(x, a) ({ \
    typeof(x) value = x; \
    typeof(a) align = a; \
    if ((value & (align - 1)) != 0) { \
        value &= ~(align - 1); \
        value += align; \
    } \
    value; \
})

#define ALIGN_DOWN(x, a) ({ \
    typeof(x) value = x; \
    typeof(a) align = a; \
    if ((value & (align - 1)) != 0) { \
        value &= ~(align - 1); \
    } \
    value; \
})

uint8_t bcd_to_int(uint8_t val);

int cpuid(uint32_t leaf, uint32_t subleaf,
          uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

__attribute__((noreturn)) void panic(const char *fmt, ...);

void pit_sleep(uint64_t pit_ticks);
int pit_sleep_and_quit_on_keypress(uint32_t pit_ticks);

void brewind(size_t count);
void *balloc(size_t count);
void *balloc_aligned(size_t count, size_t alignment);

#define GETCHAR_CURSOR_LEFT  (-10)
#define GETCHAR_CURSOR_RIGHT (-11)
#define GETCHAR_CURSOR_UP    (-12)
#define GETCHAR_CURSOR_DOWN  (-13)

int getchar(void);
void gets(const char *orig_str, char *buf, size_t limit);
uint64_t strtoui(const char *s);

#define DIV_ROUNDUP(a, b) (((a) + ((b) - 1)) / (b))

typedef void *symbol[];

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

#endif
