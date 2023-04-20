#include "err_handler.h"

void err_handler(int err_code) {
  switch (err_code) {
    case -1:
      printf("Ошибка выделения памяти, попробуйте еще раз\n");
      break;
    case 1:
      printf("Неизвестная команда, проверьте введенные данные\n");
      break;
    case 2:
      //   printf();
      break;
    default:
      break;
  }
}
