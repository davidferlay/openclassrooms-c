#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
  int number;
  struct Element *next;
} Element;

typedef struct Stack {
  Element *top;
} Stack;

Stack *initialize() {
  Stack *stack = malloc(sizeof(Stack));
  if (stack == NULL) {
    exit(EXIT_FAILURE);
  }
  stack->top = NULL;
  return stack;
}

void push(Stack *stack, int newNumber) {
  Element *new = malloc(sizeof(*new));
  if (stack == NULL || new == NULL)
    exit(EXIT_FAILURE);

  new->number = newNumber;
  new->next = stack->top;
  stack->top = new;
}

int pop(Stack *stack) {
  if (stack == NULL)
    exit(EXIT_FAILURE);

  int poppedNumber = 0;
  Element *popped = stack->top;

  if (stack->top != NULL) {
    poppedNumber = popped->number;
    stack->top = popped->next;
    free(popped);
  }

  return poppedNumber;
}

void displayStack(Stack *stack) {
  if (stack == NULL)
    exit(EXIT_FAILURE);

  Element *current = stack->top;
  while (current != NULL) {
    printf("%d\n", current->number);
    current = current->next;
  }
  printf("\n");
}

void destroyStack(Stack *stack) {
  if (stack == NULL) {
    return;
  }

  Element *current = stack->top;
  while (current != NULL) {
    Element *toDelete = current;
    current = current->next;
    free(toDelete);
  }

  free(stack); // Finally free the control structure
}

int main() {
  Stack *myStack = initialize(); // Assume this initializes the stack

  push(myStack, 4);
  push(myStack, 8);
  push(myStack, 15);
  push(myStack, 16);
  push(myStack, 23);
  push(myStack, 42);

  printf("\nStack state:\n");
  displayStack(myStack);

  printf("Popped: %d\n", pop(myStack));
  printf("Popped: %d\n", pop(myStack));

  printf("\nStack state:\n");
  displayStack(myStack);

  destroyStack(myStack);

  return 0;
}
