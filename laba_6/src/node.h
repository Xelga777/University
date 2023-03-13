#ifndef NODE_H_
#define NODE_H_

typedef struct node {
    char ch;
    struct node* next;
} node;

struct node* init(char c);
struct node* add_ch(struct node* elem, char c);
struct node* remove_ch(struct node* elem, struct node* root);
void destroy(struct node *root);

#endif  // NODE_H_
