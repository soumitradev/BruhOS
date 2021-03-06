#include <stdbool.h>

#include <kernel/cpu/ports.hpp>
#include <kernel/drivers/keyboard.hpp>
#include <kernel/drivers/screen.hpp>
#include <kernel/shell/commands.hpp>

void print_chr(char c) {
  char n[] = {c, '\0'};
  print(n);
}

char keyMap[] = {' ', ' ', '1',  '2',  '3',  '4', '5', '6',  '7', '8', '9', '0',
                 '-', '=', '\b', '\t', 'q',  'w', 'e', 'r',  't', 'y', 'u', 'i',
                 'o', 'p', '[',  ']',  ' ',  ' ', 'a', 's',  'd', 'f', 'g', 'h',
                 'j', 'k', 'l',  ';',  '\'', '`', ' ', '\\', 'z', 'x', 'c', 'v',
                 'b', 'n', 'm',  ',',  '.',  '/', ' ', ' ',  ' ', ' '};

char capKeyMap[] = {' ',  ' ', '!', '@',  '#',  '$',  '%', '^', '&', '*',
                    '(',  ')', '_', '+',  '\b', '\t', 'Q', 'W', 'E', 'R',
                    'T',  'Y', 'U', 'I',  'O',  'P',  '{', '}', ' ', ' ',
                    'A',  'S', 'D', 'F',  'G',  'H',  'J', 'K', 'L', ':',
                    '\'', '~', ' ', '\\', 'Z',  'X',  'C', 'V', 'B', 'N',
                    'M',  '<', '>', '?',  ' ',  ' ',  ' ', ' '};

static bool upkey = false;

void keyboard_handler(registers_t *r) {
  uint8_t keycode = port_byte_in(0x60);

  switch (keycode) {
    case 0xaa:  // left shift up
      upkey = false;
      break;
    case 0x2a:  // left shift down
      upkey = true;
      break;
    case 0xf:  // tab
      for (int i = 0; i < 4; i++) print_chr(' ');
      break;
    case 0xe:  // backspace
      if (get_offset_col(get_cursor_offset()) > 1) {
        backspace_handler();
      }
      break;
    case 0x1c:  // enter
      print("\n");
      process_cmd(get_offset_row(get_cursor_offset()) - 1);
      print("\n>");
      break;
    default:
      if (keycode <= 128) {
        if (upkey) {
          print_chr(capKeyMap[keycode]);
          break;
        }
        print_chr(keyMap[keycode]);
      }
  }
}
