#ifndef ERR_HANDLER_H_
#define ERR_HANDLER_H_

#define _MEM_ERR -1
#define _OK 0
#define _UNKNOWN_COMMAND 1
#define _INVALID_ARG 2
#define _TBL_OVERFLOW 3
#define _MISSING_EL 4

#define VALID_COMMANDS "q1234567\n"
#define VALID_CONSTR "123\n"

#include <stdio.h>

void err_handler(int err_code);

#endif  // ERR_HANDLER_H_