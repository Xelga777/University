#include <stdio.h>
#include <stdlib.h>
#include "node_0.h"

void input(int *n, node **array);
struct node *func(node *node);
void output(node *node);
struct node* init(int c);
struct node* add_ch(struct node* elem, int c);
struct node* remove_n(struct node* elem, struct node* root);

int main() {
    int n = 0;
    node *arr = NULL;
    input(&n, &arr);
    arr = func(arr);
    output(arr);
}

void input(int *n, node **array) {
    scanf("%d", n);
    int v = 0;
    *array = init(*n);
    node *ptr = *array;
    
    for (int i = 0; i < *n; i++) {
        scanf("%d", &v);
        *array = add_ch(*array, v);
    }
    *array = ptr;
}

struct node *func(node *node) {
    struct node *ptr = node;
    int min = 99999999;

    while (ptr -> next) {
        if (ptr->value <= min) min = ptr->value;
        ptr = ptr->next;
    }
    // printf("MIN: %d\n", min);
    ptr = node;
    while (ptr) {
        if (ptr->value == min) {
            ptr = remove_n(ptr, node);
        }
        ptr = ptr->next;
    }
    return node;
}

struct node* remove_n(struct node* elem, struct node* root) {
    struct node *temp = NULL;
    if (root) {
        temp = root;
        if (elem == root) {
            temp = temp -> next;
            free(root);
            return temp;
        }
        while (temp && (temp -> next != elem)) {
            temp = temp -> next;
        }
        if (temp) {
            temp -> next = elem -> next;
        }
        free(elem);
    }
    return temp;
}

void output(node *node) {
    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
}

struct node* init(int c) {
    struct node* Node = (struct node*)malloc(sizeof(struct node));
    Node -> value = c;
    Node -> next = NULL;
    return Node;
}

struct node* add_ch(struct node* elem, int c) {
    struct node *newEl, *temp;
    newEl = (struct node*)malloc(sizeof(struct node));
    temp = elem -> next;
    elem -> next = newEl;
    newEl -> value = c;
    newEl -> next = temp;
    return newEl;
}
