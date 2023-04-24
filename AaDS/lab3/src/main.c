#include "io.h"
#include "lib/table.h"

int main() {
  size_t tbl_count = 0;
  Table **tbls = NULL;
  while (1) {
    menu();
    input_menu_command(tbls);  
  }
  
  return 0;
}
