#ifndef TABLE_H_
#define TABLE_H_

#include <stdio.h>
#include <stdlib.h>

#include "item.h"

typedef struct table {
  // указатель на пространство ключей
  KeySpace *ks;
  // размер области пространства ключей
  size_t msize;
} Table;

// CONSTRUCTORS //

// Пустой конструктор, принимает на вход указатель, куда запишется таблица и
// максимальный размер пространства ключей
int init_empt_table(Table *new_tbl, size_t max_tbl_size);

// END CONSTRUCTORS //

// BASE OPERATIONS //

// Включение нового элемента в таблицу
int insert_el(Table *tbl, Item new_el);
// Удаление из таблицы элемента по заданному значению ключа
int remove_el(Table *tbl, char *key);
// Поиск в таблице элемента по заданному значению ключа, результатом поиска
// являются копии всех найденных элементов со значениями ключей
int select_el_by_key(Table *tbl, char *key, Table *result);
// поиск элементов, заданных диапазоном ключей; в таблице могут отсутствовать
// элементы с ключами, задающими диапазон; результатом поиска является новая
// таблица, содержащая найденные элементы.
int select_els_by_key_range(Table *tbl, char *key_bg, char *key_end,
                            Table *result);
// Вывод содержимого таблицы в стандартный поток
int output(Table *tbl);
// Импорт данных из текстового файла
int import(Table *tbl, FILE *file);

// END BASE OPERATIONS //

// SUPPORTING FUNCS //

// Проверка существования таблицы
int is_tbl(Table *tbl);
// Полное удаление таблицы
int delete_tbl(Table *tbl);

// END SUPPORTING FUNCS //

#endif  // TABLE_H_