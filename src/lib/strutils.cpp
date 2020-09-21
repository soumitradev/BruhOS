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

void rev_str(char *s) {
  int i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    s[i] ^= s[j];
    s[j] ^= s[i];
    s[i] ^= s[j];
  }
}

char *concat(char *str1, const char *str2) {
  uint64_t l1 = strlen(str1);
  uint64_t l2 = strlen(str2);
  strcpy(&str1[l1], str2);
  return str1;
}