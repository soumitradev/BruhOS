#pragma once
#include <stdint.h>

uint64_t strlen(const char *str);

int strcmp(const char *str0, const char *str1);

char *strcpy(char *dest, const char *src);
char *concat(char *str1, const char *str2);
char *itob(uint64_t num, uint64_t base);

void rev_str(char *s);
