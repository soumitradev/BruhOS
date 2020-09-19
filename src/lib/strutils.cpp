#include <lib/strutils.hpp>

char *itob(uint64_t num, uint64_t base) {
  static char hold[] = "0123456789ABCDEF";
  static char buffer[50];
  char *str;

  str = &buffer[49];
  *str = '\0';

  do {
    *--str = hold[num % base];
    num /= base;
  } while (num != 0);

  return str;
}

uint64_t strlen(const char *str) {
  uint64_t len = 0;
  while (str[len]) len++;
  return len;
}

int strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return (int)(*str1) - (int)(*str2);
}

char *strcpy(char *dest, const char *src) {
  uint64_t i;

  for (i = 0; src[i]; i++) dest[i] = src[i];

  dest[i] = 0;

  return dest;
}
