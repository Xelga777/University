#ifndef TABLE_H_
#define TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

typedef struct table {
  // указатель на пространство ключей
  KeySpace *ks;
  // размер области пространства ключей
  size_t msize;
} Table;

// todo Конструктор на файле и на вводе пользователя
// CONSTRUCTORS //

// Пустой конструктор, принимает на вход указатель, куда запишется таблица и
// максимальный размер пространства ключей
int init_empt_table(Table *new_tbl, size_t max_tbl_size);
// Конструктор на файле
int init_file_table(Table *new_tbl, FILE *fp);

// BASE OPERATIONS //

// Включение нового элемента в таблицу
int insert_el(Table *tbl, Item *new_el);
// Удаление из таблицы элемента по заданному значению ключа
int remove_el(Table *tbl, char *key);
// Поиск в таблице элемента по заданному значению ключа, результатом поиска
// являются копия найденного элемента
int select_el_by_key(Table *tbl, char *key, Item *result);
// поиск элементов, заданных диапазоном ключей; в таблице могут отсутствовать
// элементы с ключами, задающими диапазон; результатом поиска является новая
// таблица, содержащая найденные элементы.
int select_els_by_key_range(Table *tbl, char *key_bg, char *key_end,
                            Table *result);
// Вывод содержимого таблицы в стандартный поток
int output(Table *tbl);
// Импорт данных из текстового файла
int import(Table *tbl, FILE *fp);

// SUPPORTING FUNCS //

// Проверка существования таблицы
int is_tbl(Table *tbl);
// Считаю количество элементов в таблице
int get_els_count(Table *tbl);
// Проверяю заполнена ли таблица
int is_tbl_full(Table *tbl);
// Полное удаление таблицы
int delete_tbl(Table *tbl);
// Поиск уникального, еще не использованного ключа
int search_free_key(Table *tbl, char *free_key);
// Перевод числа в строку
char *itoa(size_t number);
// Переворачиваем строку: abc->cba
void reverse_str(char *str);
// Считаем сколько цифр в числе
int num_len(int num);
// Ищем в таблице строку максимальной длины
// Все для кросоты вывода
void get_max_symb_count(Table *tbl, size_t *max_key_len, size_t *max_info_len);

#endif  // TABLE_H_