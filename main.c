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

  if (list == NULL) {
    exit(1); // Exit the program if memory allocation fails
  }

  list->first = NULL; // Initialize with no elements
  return list;        // Return the initialized empty list
}

void addItemFirst(List *list, int newValue) {
  Element *newElement = malloc(sizeof(*newElement)); // Create the new element
  if (list == NULL || newElement == NULL) { // Check that both list exist and
                                            // new element created successfuly
    exit(1);                                // Exit if not
  }

  newElement->number = newValue;  // Set the value
  newElement->next = list->first; // Point to the current first element

  list->first = newElement; // Update the list to point to the new first element
  printf("Item to add: %d (first)\n", newValue);
}

void addItemLast(List *list, int newValue) {
  if (list == NULL) { // Check that list exists
    exit(1);          // Exit if not
  }

  if (list->first == NULL) { // If list is empty, new element is the first
    addItemFirst(list, newValue);
    return;
  }

  Element *newElement = malloc(sizeof(*newElement)); // Create the new element
  if (newElement == NULL) { // Check that new element was created successfuly
    exit(1);                // Exit if not
  }

  Element *current = list->first; // Start with the first element
  while (current->next != NULL) { // Iterate over list till last element
    current = current->next;      // Move to the next node
  }

  newElement->number = newValue; // Set the value
  newElement->next = NULL;       // NULL for end of list

  printf("Previous item whose next value should be updated: %d\n",
         current->number);
  current->next = newElement; // Update last item to point to new element
  printf("Item to add: %d (last)\n", newValue);
}

void addItem(List *list, int index, int newValue) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (index <= 1) { // If adding first item (index 0 or 1 if one-based), forward
                    // to dedicated function
    addItemFirst(list, newValue);
    return; // Otherwise go on
  }

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

  printf("Item to add: %d (index: %d)\n", newValue, index);
  printf("Previous item whose next value should be updated: %d\n",
         previous->number);

  Element *newElement = malloc(sizeof(*newElement)); // Create the new element
  if (list == NULL || newElement == NULL) {
    exit(1); // Exit if allocation failed
  }
  newElement->number = newValue; // Set the value
  newElement->next =
      previous->next; // Set the next element (previously existing one)
  previous->next = newElement;
}

void deleteItemFirst(List *list) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (list->first != NULL) {
    Element *toDelete = list->first; // Save the element to delete
    list->first =
        list->first->next; // Move the list's pointer to the second element
    printf("Item to delete: %d (first)\n", toDelete->number);
    free(toDelete); // Free memory of the removed element
  }
}

void deleteItemLast(List *list) {
  if (list == NULL) { // Check that list exists
    exit(1);          // Exit if not
  }

  if (list->first == NULL) { // If list is empty, new element is the first
    printf("Item to delete: None (list is already empty)\n");
    return;
  }

  Element *current = list->first; // Start with the first element
  Element *previous = NULL;       // Case where there is only one item in list
  Element *toDelete = NULL;       // Start with the first element

  while (current->next != NULL) { // Iterate over list till last element
    previous = current; // Save previous item in a variable since we will need
                        // to update it's next value
    current = current->next; // Move to the next node
  }

  if (current == list->first) {
    printf("Previous item whose next value should be updated: list control\n");
    toDelete = list->first; // Save the element to delete
    list->first = NULL;
  } else {
    toDelete = previous->next;      // Save the element to delete
    previous->next = current->next; // Should always take value NULL
    printf("Previous item whose next value should be updated: %d\n",
           previous->number);
  }
  printf("Item to delete: %d (last)\n", toDelete->number);
  free(toDelete);
}

void deleteItem(List *list, int index) {
  if (list == NULL) {
    exit(1); // Cannot work with a NULL list
  }

  if (index <= 1) { // If deleting first item (index 0 or 1 if one-based),
                    // forward to dedicated function
    deleteItemFirst(list);
    return; // Otherwise go on
  }

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

  printf("Item to delete: %d (index: %d)\n", current->number, index);
  printf("Previous item whose next value should be updated: %d\n",
         previous->number);

  Element *toDelete = previous->next; // Save the element to delete
  previous->next = current->next; // previous->next = previous->next->next; ///
                                  // Can also be written that way
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
         index);
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

  printf("Item to print: %d (index: %d)\n", current->number, index);
}

void printList(List *list) {
  if (list == NULL) {
    exit(1); // Cannot print a NULL list
  }

  Element *current = list->first; // Start with the first element

  while (current != NULL) {
    printf("%d -> ", current->number);
    current = current->next; // Move to the next node
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
  printList(myList);           // Output: NULL

  // Adding elements
  addItemLast(myList, 77);
  printList(myList);
  addItemFirst(myList, 4);
  addItemFirst(myList, 8);
  addItemFirst(myList, 15);
  printList(myList);
  addItemLast(myList, 66);
  printList(myList);
  printItem(myList, 2);

  // Updating element at index
  updateItem(myList, 1, 99);
  printList(myList);

  // Adding element at index
  addItem(myList, 1, 55);
  printList(myList);
  addItem(myList, 3, 10);
  printList(myList);
  addItem(myList, 2, 20);
  printList(myList);

  // Deleting elements
  deleteItemFirst(myList);
  printList(myList);
  deleteItem(myList, 2);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);
  deleteItemLast(myList);
  printList(myList);

  // Prevent memoty leaks
  destroyList(myList);

  return 0;
}
