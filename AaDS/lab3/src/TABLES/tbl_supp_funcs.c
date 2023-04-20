#include "../err_handler.h"
#include "table.h"

int is_tbl(Table *tbl) {
  if (!tbl || !tbl->ks)  // is tbl or key_space undefined?
    return _INVALID_ARG;
  else
    return _OK;
}

int is_tbl_full(Table *tbl) {
  int count = 0;
  for (size_t i = 0; i < tbl->msize; i++) {
    if (tbl->ks[i].key) count++;
  }

  if (count == tbl->msize)
    return _TBL_OVERFLOW;  // means that count of els in tbl equals max tbl size
  else
    return _OK;
}

int delete_tbl(Table *tbl) {
  int err_code = _OK;
  if (!tbl)
    return _INVALID_ARG;  // Нельзя использовать is_tbl, потому что таблица
                          // может быть определена, а пространство ключей нет

  if (tbl->ks) {
    for (int i = 0; i < tbl->msize; i++) {
      if (tbl->ks[i].info->info) free(tbl->ks[i].info->info);
      if (tbl->ks[i].info) free(tbl->ks[i].info);
      if (tbl->ks[i].key) free(tbl->ks[i].key);
    }

    free(tbl->ks);
  }

  free(tbl);

  return err_code;
}

int search_free_key(Table *tbl, char *free_key) {
  int err_code = 0;
  // Нужен для определения есть ли в таблице ключ, который я сгенерила
  int flag = 0;

  // Checking errors
  if (err_code = is_tbl(tbl)) return err_code;

  // Ключ, который будем менять, делая уникальным
  char *new_key = (char *)calloc(10, sizeof(char));
  *new_key = 'A';

  // Выйдем из цикла, как только ключ станет уникальным
  while (!flag) {
    flag = 1;
    for (int i = 0; i < tbl->msize; i++) {
      // Ключ не уникален, дальше нет смысла проверять
      // Выходим и будем менять ключ
      if (new_key == tbl->ks[i].key) {
        flag = 0;
        break;
      }
    }

    // Не дошли до последней буквы, значит сдвигаем (A->B)
    if (!flag && *new_key != 'Z') {
      *new_key++;
    } else if (!flag && *new_key == 'Z') {  // Дошли до последней буквы, значит
                                            // добавляем еще 1 (AZ->AAA)

      // Если закончилась выделенная на ключ память, даем еще
      if (strlen(new_key) == 10)
        new_key = realloc(new_key, strlen(new_key) * 2);

      *new_key = 'A';
      new_key++;
      *new_key = 'A';
    }
  }

  free_key = new_key;
  return err_code;
}
