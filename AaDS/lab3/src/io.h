#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err_handler.h"

void command_handler(char command);
int input_menu_command();
void menu();

#endif  // IO_H_
