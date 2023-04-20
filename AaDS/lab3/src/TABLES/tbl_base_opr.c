#include "../err_handler.h"
#include "table.h"

int insert_el(Table *tbl, Item *new_el) {
  // Checking errors
  int err_code = _OK;
  if (err_code = is_tbl(tbl)) return err_code;
  if (err_code = is_tbl_full(tbl)) return err_code;

  // Searching a unique key
  char *new_key = NULL;
  err_code = search_free_key(tbl, new_key);

  // Inserting new element
  for (size_t i = 0; i < tbl->msize; i++) {
    if (!tbl->ks[i].key) {
      tbl->ks[i].key = new_key;
      tbl->ks[i].info = new_el;
    }
  }

  return err_code;
}

int remove_el(Table *tbl, char *key) {
  // Checking errors
  int err_code = _OK;
  if (err_code = is_tbl(tbl)) return err_code;

  // Считаю количество элементов в таблице
  int count = get_els_count(tbl);

  // Нужен для определения есть ли вообще заданный ключ в таблице
  int flag = 0;

  for (size_t i = 0; i < count; i++) {
    if (tbl->ks[i].key == key) {
      flag = 1;  // El is here!

      // Чищу память и зануляю, чтобы мусор не валялся
      free(tbl->ks[i].key);
      if (tbl->ks[i].info) free(tbl->ks[i].info);
      tbl->ks[i].info = NULL;
      tbl->ks[i].key = NULL;
    }
  }

  // Checking is opr successful
  if (!flag) err_code = _MISSING_EL;

  return err_code;
}

int select_el_by_key(Table *tbl, char *key, Item *result) {
  result = NULL;

  // Checking errors
  int err_code = _OK;
  if (err_code = (is_tbl(tbl) || !key)) return err_code;

  // Считаю количество элементов в таблице
  int count = get_els_count(tbl);

  // Нужен для определения есть ли вообще заданный ключ в таблице
  int flag = 0;

  for (size_t i = 0; i < count; i++) {
    if (tbl->ks[i].key == key) {
      flag = 1;  // El is here!
      result = tbl->ks[i].info;
      break;
    }
  }

  if (!flag) err_code = _MISSING_EL;  // Не нашли...
  return err_code;
}

int select_els_by_key_range(Table *tbl, char *key_bg, char *key_end,
                            Table *result) {}

int output(Table *tbl) {}

int import(Table *tbl, FILE *file) {}
