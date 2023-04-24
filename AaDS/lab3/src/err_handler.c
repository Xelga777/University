#include "err_handler.h"

void err_handler(int err_code) {
  switch (err_code) {
    case -1:
      printf("Ошибка выделения памяти, попробуйте еще раз\n");
      break;
    case 0:
      printf("Операция выполнена успешно!\n");
      break;
    case 1:
      printf("Неизвестная команда, проверьте введенные данные\n");
      break;
    case 2:
      printf("Невалидные входные данные!\n");
      break;
    case 3:
      printf("Переполнение выбранной таблицы\n");
      break;
    case 4:
      printf("Не найдено подходящих элементов\n");
      break;
    default:
      break;
  }
}
