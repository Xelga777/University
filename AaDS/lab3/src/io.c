#include "io.h"

void menu() {
  printf(
      "Добро пожаловать в программу обработки таблиц!\nВыберите 1 из "
      "пунктов меню:\n");
  printf(
      "1 - Инициализация новой таблицы\n2 - Добавление нового элемента\n3 - "
      "Удаление элемента по его ключу\n4 - Удаление элементов, находящихся в "
      "заданном диапазоне ключей\n5 - Вывод списка созданных таблиц\n6 - Вывод "
      "таблицы\n7 - Импорт таблицы из файла\nq - Выход из программы\n");
  while (1) input_menu_command();
}

void input_menu_command() {
  char choosing = getchar();
  if (!strchr(VALID_COMMANDS, choosing)) {
    err_handler(_UNKNOWN_COMMAND);
  } else {
    command_handler(choosing);
  }
}

void command_handler(char command) {
  switch (command) {
    case 'q':
      printf("Завершение работы программы...\n");
      exit(0);
      break;

    default:
      break;
  }
}