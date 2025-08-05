
#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element {
  int number;    // The data stored in the node (can be any type)
  Element *next; // Pointer to the next node in the list
};

typedef struct List List;
struct List {
  Element *first; // Pointer to the first node in the list
};

List *initialize() {
  List *list = malloc(sizeof(*list)); // Allocate memory for the list structure
  Element *element =
      malloc(sizeof(*element)); // Allocate memory for the first node

  if (list == NULL || element == NULL) {
    exit(1); // Exit the program if memory allocation fails
  }

  element->number = 0;   // Initialize the value of the first element to 0
  element->next = NULL;  // It doesn't point to anything yet (end of list)
  list->first = element; // Point the list to this first element

  return list; // Return the initialized list
}

void insertFirstItem(List *list, int newNumber) {
  /* Create the new element */
  Element *newElement = malloc(sizeof(*newElement));
  if (list == NULL || newElement == NULL) {
    exit(1); // Exit if allocation failed
  }
  newElement->number = newNumber; // Set the value

  /* Insert at the beginning */
  newElement->next = list->first; // Point to the current first element
  list->first = newElement; // Update the list to point to the new first element
  printf("Item to add as first element: %d\n", newNumber);
}

void deleteFirstItem(List *list) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (list->first != NULL) {
    Element *toDelete = list->first; // Save the element to delete
    list->first =
        list->first->next; // Move the list's pointer to the second element
    free(toDelete);        // Free memory of the removed element
  }
}

void addItem(List *list, int index, int newValue) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (index <= 1) { // If adding first item (index 0 or 1 if one-based),
                    // forward to dedicated function
    insertFirstItem(list, newValue);
    return;
  }
  // Otherwise go on

  Element *current = list->first; // Start with the first element
  Element *previous = NULL; // Init pointer with default value to store it later

  int counter = 1; // Init with 0 would make it look like an off-by-one-error,
                   // so 1 for one-based
  while (current != NULL && counter < index) {
    previous = current; // Save previous item in a variable since we will need
                        // to update it's next value
    current = current->next; // Save looked index item in a var since we want to
                             // delete it
    counter++;
  }

  if (current == NULL) {
    fprintf(stderr, "Error: index %d is out of bounds.\n", index);
    exit(1);
  }

  printf("Item to add: %d (index: %d)\n", current->number,
         index); // Print the value
  printf("Previous item whose next value should be updated: %d\n",
         previous->number); // Print the value

  /* Create the new element */
  Element *newElement = malloc(sizeof(*newElement));
  if (list == NULL || newElement == NULL) {
    exit(1); // Exit if allocation failed
  }
  newElement->number = newValue; // Set the value
  newElement->next =
      current->next; // Set the next element (previously existing one)
  previous->next = newElement->next;
  printf("Item to add: %d (index: %d)\n", newValue, index);
}

void deleteItem(List *list, int index) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (index <= 1) { // If deleting first item (index 0 or 1 if one-based),
                    // forward to dedicated function
    deleteFirstItem(list);
    return;
  }
  // Otherwise go on

  Element *current = list->first; // Start with the first element
  Element *previous = NULL; // Init pointer with default value to store it later

  int counter = 1; // Init with 0 would make it look like an off-by-one-error,
                   // so 1 for one-based
  while (current != NULL && counter < index) {
    previous = current; // Save previous item in a variable since we will need
                        // to update it's next value
    current = current->next; // Save looked index item in a var since we want to
                             // delete it
    counter++;
  }

  if (current == NULL) {
    fprintf(stderr, "Error: index %d is out of bounds.\n", index);
    exit(1);
  }

  printf("Item to delete: %d (index: %d)\n", current->number,
         index); // Print the value
  printf("Previous item whose next value should be updated: %d\n",
         previous->number); // Print the value

  Element *toDelete = previous->next; // Save the element to delete
  previous->next = current->next;
  // previous->next = previous->next->next; /// Can also be written that way
  free(toDelete);
}

void updateItem(List *list, int index, int newValue) {
  if (list == NULL) {
    exit(1); // Cannot print a NULL list
  }

  Element *current = list->first; // Start with the first element

  int counter = 1; // Init with 0 would make it look like an off-by-one-error,
                   // so 1 for one-based
  while (current != NULL && counter < index) {
    current = current->next; // Move to the next node
    counter++;
  }
  if (current == NULL) {
    fprintf(stderr, "Error: index %d is out of bounds.\n", index);
    exit(1);
  }

  printf("Item to update: %d -> %d (index: %d)\n", current->number, newValue,
         index); // Print the value
  current->number = newValue;
}

void printItem(List *list, int index) {
  if (list == NULL) {
    exit(1); // Cannot print a NULL list
  }

  Element *current = list->first; // Start with the first element

  int counter = 1; // Init with 0 would make it look like an off-by-one-error,
                   // so 1 for one-based
  while (current != NULL && counter < index) {
    current = current->next; // Move to the next node
    counter++;
  }
  if (current == NULL) {
    fprintf(stderr, "Error: index %d is out of bounds.\n", index);
    exit(1);
  }

  printf("Item to print: %d (index: %d)\n", current->number,
         index); // Print the value
}

void printList(List *list) {
  if (list == NULL) {
    exit(1); // Cannot print a NULL list
  }

  Element *current = list->first; // Start with the first element

  while (current != NULL) {
    printf("%d -> ", current->number); // Print the value
    current = current->next;           // Move to the next node
  }
  printf("NULL\n"); // Indicate end of the list
}

void destroyList(List *list) {
  if (list == NULL) {
    return;
  }

  Element *current = list->first;
  while (current != NULL) {
    Element *toDelete = current;
    current = current->next;
    free(toDelete);
  }

  free(list); // Finally free the control structure
}

int main() {
  List *myList = initialize(); // Start with an initialized list

  // Adding elements
  insertFirstItem(myList, 4);  // Add element with value 4
  insertFirstItem(myList, 8);  // Add element with value 8
  insertFirstItem(myList, 15); // Add element with value 15
  printList(myList);           // Output: 15 -> 8 -> 4 -> 0 -> NULL
  printItem(myList, 2);        // Output: 8

  // Deleting elements
  deleteFirstItem(myList); // Remove the first element (15)
  printList(myList);       // Output: 8 -> 4 -> 0 -> NULL
  deleteItem(myList, 2);
  printList(myList); // Output: 8 -> 0 -> NULL

  // Updating element at index
  updateItem(myList, 1, 99);
  printList(myList); // Output: 99 -> 0 -> NULL

  // Adding element at index
  addItem(myList, 1, 55);
  printList(myList); // Output: 55 -> 99 -> 0 -> NULL
  addItem(myList, 3, 10);
  printList(myList); // Output: 10 -> 55 -> 99 -> 0 -> NULL

  // Prevent memoty leaks
  destroyList(myList);

  return 0;
}
