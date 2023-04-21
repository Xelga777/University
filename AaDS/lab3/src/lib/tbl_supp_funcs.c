#include "../err_handler.h"
#include "table.h"

int is_tbl(Table *tbl) {
  if (!tbl || !tbl->ks)  // is tbl or key_space undefined?
    return _INVALID_ARG;
  else
    return _OK;
}

size_t get_els_count(Table *tbl) {
  size_t count = 0;
  for (size_t i = 0; i < tbl->msize; i++) {
    if (tbl->ks[i].key) count++;
  }

  return count;
}

int is_tbl_full(Table *tbl) {
  int err_code = _OK;
  size_t count = get_els_count(tbl);

  if (count == tbl->msize)
    err_code = _TBL_OVERFLOW;  // means that count of els in tbl equals max tbl size
  
  return err_code;
}

int delete_tbl(Table *tbl) {
  int err_code = _OK;
  if (!tbl)
    return _INVALID_ARG;  // Нельзя использовать is_tbl, потому что таблица
                          // может быть определена, а пространство ключей нет

  if (tbl->ks) {
    for (size_t i = 0; i < tbl->msize; i++) {
      if (tbl->ks[i].info->info) free(tbl->ks[i].info->info);
      if (tbl->ks[i].info) free(tbl->ks[i].info);
      if (tbl->ks[i].key) free(tbl->ks[i].key);
    }

    free(tbl->ks);
  }

  free(tbl);

  return err_code;
}

int search_free_key(Table *tbl, char **free_key) {
  int err_code = _OK;
  // Нужен для определения есть ли в таблице ключ, который я сгенерила
  int flag = 0;

  // Checking errors
  if ((err_code = is_tbl(tbl)) != 0) return err_code;

  // Считаю количество элементов в таблице
  size_t count = get_els_count(tbl);

  // Ключ, который будем менять, делая уникальным
  size_t new_key = 1;

  // Выйдем из цикла, как только ключ станет уникальным
  while (!flag) {
    flag = 1;

    // Пробегаемся по всей таблице, сравнивая сгенеренный ключ и все ключи,
    // которые есть в таблице
    for (size_t i = 0; i < count; i++) {
      // Ключ не уникален, дальше нет смысла проверять
      // Выходим и будем менять ключ
      if (!strcmp(itoa(new_key), tbl->ks[i].key)) {
        flag = 0;
        break;
      }
    }

    // Key isnt unique -> add 1 to get new value
    if (!flag) new_key++;
  }

  // key is char* so get it from size_t
  *free_key = itoa(new_key);
  return err_code;
}

char *itoa(size_t number) {
  int len = num_len(number);  // Считаем длину числа
  char *str = (char *)calloc(len + 1, sizeof(char));  // +1 для '\0'

  do {
    str[len] = number % 10 + '0';
  } while ((number /= 10) > 0);

  // Строка получилась перевернутой
  reverse_str(str);
  return str;
}

void reverse_str(char *str) {
  char c = 0;

  for (size_t i = 0, j = strlen(str) - 1; i < j; i++, j--) {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

int num_len(int num) {
  int len = 0;
  do {
    num /= 10;
    len += 1;
  } while (num);

  return len;
}

void get_max_symb_count(Table *tbl, size_t *max_key_len, size_t *max_info_len) {
  size_t count = get_els_count(tbl);
  *max_info_len = -1;
  *max_key_len = -1;

  size_t key_len = 0;
  size_t info_len = 0;

  for (size_t i = 0; i < count; i++) {
    key_len = strlen(tbl->ks[i].key);
    info_len = strlen(tbl->ks[i].info->info);
    if (key_len > *max_key_len) *max_key_len = key_len;
    if (info_len > *max_info_len) *max_info_len = info_len;
  }
}
