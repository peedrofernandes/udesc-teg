#include <stdio.h>
#include <stdlib.h>
#include "../headers/structs.h"

Stack *createStack() {
  Stack *newStack = malloc(sizeof(Stack));
  newStack->qtdNodes = 0;
  newStack->head = NULL;
  return newStack;
}

void push(Stack *stack, void *elem) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = elem;
  newNode->prev = stack->head;
  stack->head = newNode;
  stack->qtdNodes++;
}

void *pop(Stack *stack) {
  if (stack->head == NULL)
    return 0;

  Node *node = stack->head;
  stack->head = stack->head->prev;
  void *data = node->data;
  free(node);

  stack->qtdNodes--;
  return data;
}

void destroyStack(Stack* stack) {
  Node *node = stack->head;

  while (node != NULL) {
    Node *prev = node->prev;
    free(node);
    node = prev;
  }

  free(stack);
}