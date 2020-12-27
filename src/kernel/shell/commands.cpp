#include <kernel/drivers/screen.hpp>
#include <kernel/shell/commands.hpp>
#include <lib/strutils.hpp>

void test() { print("\nTest command"); }
void hi() { print("\nh"); }

char* commands[] = {">test", ">panic", ">hi"};
func cmd_funcs[] = {&test, &panic, &hi};

void process_cmd(const int row) {
  char command_string[MAX_COLS];
  // Flood screen with char and attr
  char* vid = VGA_ADDRESS;
  int j;
  for (j = 0; j < MAX_COLS; j++) {
    command_string[j] = vid[(row * MAX_COLS + j) * 2];
  }
  print(command_string, VGA_COLOR(VGA_BLACK, VGA_LIGHT_BLUE));
  int i;
  for (i = 0; i < 3; i++) {
    if (strcmp(command_string, commands[i]) == 0) {
      cmd_funcs[i]();
    }
  }
}