#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
  int number;
  struct Element *next;
} Element;

typedef struct Queue {
  Element *first;
} Queue;

Queue *initialize() {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    exit(EXIT_FAILURE);
  }
  queue->first = NULL;
  return queue;
}

void enqueue(Queue *queue, int newNumber) {
  Element *new = malloc(sizeof(*new));
  if (queue == NULL || new == NULL)
    exit(EXIT_FAILURE);

  new->number = newNumber;
  new->next = NULL;

  if (queue->first != NULL) {
    Element *current = queue->first;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new;
  } else {
    queue->first = new;
  }
}
int dequeue(Queue *queue) {
  if (queue == NULL)
    exit(EXIT_FAILURE);

  int dequeuedNumber = 0;

  if (queue->first != NULL) {
    Element *removed = queue->first;
    dequeuedNumber = removed->number;
    queue->first = removed->next;
    free(removed);
  }

  return dequeuedNumber;
}
void displayQueue(Queue *queue) {
  if (queue == NULL)
    exit(EXIT_FAILURE);

  Element *current = queue->first;
  while (current != NULL) {
    printf("%d ", current->number);
    current = current->next;
  }
  printf("\n");
}

void destroyQueue(Queue *queue) {
  if (queue == NULL) {
    return;
  }

  Element *current = queue->first;
  while (current != NULL) {
    Element *toDelete = current;
    current = current->next;
    free(toDelete);
  }

  free(queue); // Finally free the control structure
}

int main() {
  Queue *myQueue = initialize(); // Initializes the queue

  enqueue(myQueue, 4);
  enqueue(myQueue, 8);
  enqueue(myQueue, 15);
  enqueue(myQueue, 16);
  enqueue(myQueue, 23);
  enqueue(myQueue, 42);

  printf("Queue state:\n");
  displayQueue(myQueue);

  printf("Dequeued: %d\n", dequeue(myQueue));
  printf("Dequeued: %d\n", dequeue(myQueue));

  printf("Queue state:\n");
  displayQueue(myQueue);

  destroyQueue(myQueue);

  return 0;
}
