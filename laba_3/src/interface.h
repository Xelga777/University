#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#define true 1
#define false 0
#define success "SUCKS_ASS"
#define fail "FAILED"

void display_menu(int mode);
void display_result(int code_result);
void clear_screen();
void menu(int* chooser);

#endif  // _INTERFACE_H_
