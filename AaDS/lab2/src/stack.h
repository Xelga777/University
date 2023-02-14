#ifndef SRC_STACK_H_
#define SRC_STACK_H_


#ifdef __LIST_IMPLEMENTATION__
typedef struct {
    char value;
    Node* next;
} Node;

Node* init(const char *value);
Node* push(Node *node, const char *value);
Node* pop(Node *node);
void destroy(Node *node);
#endif  // __LIST_IMPLEMENTATION__


#ifdef __VECTOR_IMPLEMENTATION__

#endif  // __VECTOR_IMPLEMENTATION__

#endif  // SRC_STACK_H_
