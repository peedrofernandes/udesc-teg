#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct node {
  void *data;
  struct node *prev;
} Node;

typedef struct stack {
  Node *head;
  int qtdNodes;
} Stack;

Stack *createStack();

void push(Stack *stack, void *elem);
void *pop(Stack *stack);

void destroyStack(Stack *stack);

#endif