#include "../err_handler.h"
#include "table.h"

int is_tbl(Table *tbl) {
  if (!tbl || !tbl->ks)
    return _NOT_VALID_ARG;
  else
    return _OK;
}

int delete_tbl(Table *tbl) {
  int err_code = _OK;
  if (!tbl)
    return _NOT_VALID_ARG;  // Нельзя использовать is_tbl, потому что таблица
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
