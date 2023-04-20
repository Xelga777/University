#include "../err_handler.h"
#include "table.h"

int insert_el(Table *tbl, Item new_el) {}

int remove_el(Table *tbl, char *key) {}

int select_el_by_key(Table *tbl, char *key, Table *result) {}

int select_els_by_key_range(Table *tbl, char *key_bg, char *key_end,
                            Table *result) {}

int output(Table *tbl) {}

int import(Table *tbl, FILE *file) {}
