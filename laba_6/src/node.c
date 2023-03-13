#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct node* init(char c) {
    struct node* Node = (struct node*)malloc(sizeof(struct node));
    Node -> ch = c;
    Node -> next = NULL;
    return Node;
}

struct node* add_ch(struct node* elem, char c) {
    struct node *newEl, *temp;
    newEl = (struct node*)malloc(sizeof(struct node));
    temp = elem -> next;
    elem -> next = newEl;
    newEl -> ch = c;
    newEl -> next = temp;
    return newEl;
}

struct node* remove_ch(struct node* elem, struct node* root) {
    struct node *temp;
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

void destroy(struct node *root) {
    while (root) {
        root = remove_ch(root, root);
    }
}
