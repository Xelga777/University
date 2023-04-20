#ifndef ITEM_H_
#define ITEM_H_

typedef struct item {
  // указатель на информацию
  char *info;
} Item;

// Организация ключей: A, B, ..., Z, AA, AB, ...
typedef struct key_space {
  // ключ элемента
  char *key;
  // указатель на информацию
  Item *info;
} KeySpace;

#endif  // ITEM_H_