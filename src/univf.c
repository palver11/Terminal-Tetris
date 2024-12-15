#include <stdbool.h>
#include <windows.h>

void clear_screen(bool mode) {
  if (mode) {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  }
  else {
    system("cls");
  }
}

