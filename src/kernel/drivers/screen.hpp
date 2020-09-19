#pragma once

#include <stdint.h>

#define VGA_ADDRESS (char *)0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define VGA_CHAR(character, color) \
  ((uint16_t)(character) | (uint16_t)(color) << 8)

#define VGA_COLOR(background, foreground) \
  ((uint8_t)(foreground) | (uint8_t)(background) << 4)

#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_PURPLE 5
#define VGA_BROWN 6
#define VGA_GRAY 7
#define VGA_DARK_GRAY 8
#define VGA_LIGHT_BLUE 9
#define VGA_LIGHT_GREEN 10
#define VGA_LIGHT_CYAN 11
#define VGA_LIGHT_RED 12
#define VGA_LIGHT_PURPLE 13
#define VGA_YELLOW 14
#define VGA_WHITE 15

#define REG_SCR_CTRL 0x3d4
#define REG_SCR_DAT 0x3d5

void panic();
// void panic(char* message);
void clr_scr();

void flood(char chr, char attr);
void flood(char chr);

void print(const char str[], char attr);
void print(const char str[]);

void set_cursor(int col, int row);
void set_cursor(int offset);

void print_at(const char str[], int col, int row, char attr);
void print_at(const char str[], int col, int row);
void print_at(const char str[], int offset, char);
void print_at(const char str[], int offset);

void backspace_handler();

int get_cursor_offset();
int get_offset_col(int offset);
int get_offset_row(int offset);
int get_offset(int col, int row);

int print_char(char chr, int col, int row, char attr);
int print_char(char chr, int col, int row);
int print_char(char chr, int offset, char attr);
int print_char(char chr, int offset);