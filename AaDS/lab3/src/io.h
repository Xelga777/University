#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err_handler.h"

// Обработка выбора пользователя, сделанного в меню
void command_handler(char command, Table **tbls);
// Обработка ввода пользователя с клавиатуры
void input_menu_command();
// Выбор конструктора для новой таблицы
void choose_tbl_constr(Table **tbls);
// Интерфейс программы
void menu();

#endif  // IO_H_
