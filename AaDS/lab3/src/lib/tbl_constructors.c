#include "../err_handler.h"
#include "table.h"

int init_empt_table(Table *new_tbl, size_t max_tbl_size) {
  new_tbl = NULL;

  new_tbl = (Table *)malloc(sizeof(Table));
  if (!new_tbl) return _MEM_ERR;

  new_tbl->msize = max_tbl_size;
  new_tbl->ks = (KeySpace *)calloc(max_tbl_size, sizeof(KeySpace));
  if (!new_tbl->ks) return _MEM_ERR;

  return _OK;
}

/* int init_file_table(Table *new_tbl, FILE *fp) {
  new_tbl = NULL;

  fopen(fp, "r");
  if (!fp) return _INVALID_ARG;

  new_tbl = (Table *)malloc(sizeof(Table));
  if (!new_tbl) return _MEM_ERR;
} */
