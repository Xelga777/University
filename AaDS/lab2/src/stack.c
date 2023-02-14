#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


#ifdef __LIST_IMPLEMENTATION__
Node* init(const char *value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> value = *value;
    node -> next = NULL;
    return node;
}

Node* push(Node *node, const char *value) {
    Node* newEl = (Node*)malloc(sizeof(Node));
    newEl -> next = node;
    newEl -> value = *value;
    return newEl;
}

Node* pop(Node *node) {
    Node *temp = node -> next;
    free(node);
    return temp;
}

void destroy(Node *node) {
    while (node) node = pop(node);
}
#endif  // __LIST_IMPLEMENTATION__

#ifdef __VECTOR_IMPLEMENTATION__

#endif  // __VECTOR_IMPLEMENTATION__
