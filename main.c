#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Structure to represent a student
typedef struct Student {
  char name[100];
  int age;
  double grade;
  struct Student *next; // For chaining (collision handling)
} Student;

// A table called hashTable which is an array of pointers to Student item
Student *hashTable[TABLE_SIZE];

// Hash function: sum of ASCII characters modulo table size
int hash(char *name) {
  int hashValue = 0;
  for (int i = 0; name[i] != '\0'; i++) {
    hashValue += name[i];
  }
  return hashValue % TABLE_SIZE;
}

// Function to create a new item using Student struct
Student *createStudent(char *name, int age, double grade) {
  Student *newStudent =
      malloc(sizeof(Student)); // Allocate necessary memory for data struct
  if (!newStudent) {
    perror("malloc");
    exit(EXIT_FAILURE); // Throw error if dyn.alloc. fails
  }

  // Populate struct attributes
  strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
  // Copies the value of  99 chars (100 - 1, ie. name array length minus space
  // for string terminator key) from name arg to struct
  newStudent->name[sizeof(newStudent->name) - 1] =
      '\0'; // Adds the final null terminator to last index of namea array (0
            // based: 99)
  newStudent->age = age;
  newStudent->grade = grade;
  newStudent->next = NULL;
  return newStudent;
}

// Inserts a student into the hashtable
void insertStudent(char *name, int age, double grade) {
  int computedIndex = hash(name); // Hash the student’s name to get table index
  Student *newStudent = createStudent(
      name, age,
      grade); // Instanciate the student (data to struct via create func)

  // Handles colisions by setting any potential item already present at this
  // index as next value of new item
  newStudent->next = hashTable[computedIndex]; // If none, will take value NULL

  // Insert instanciated student to table at computed index
  hashTable[computedIndex] = newStudent;
}

// Search for student by name
Student *searchStudent(
    char *name) { // Returns a pointer to that student if found, or NULL
  int computedIndex = hash(name); // Hash the student’s name to get table index

  Student *current =
      hashTable[computedIndex]; // Get element stored exacly at that index

  // Traverse each element stored at this index, if multiple
  while (current != NULL) { // As long as next is not NULL
    if (strcmp(current->name, name) ==
        0) // Compare item name with searched name (arg), returns 0 if true
      return current; // When found, return pointer to found student element
    current = current->next; // Otherwise iterate of the next item of that index
  }
  return NULL; // Not found
}

// Print all of the hashtable content
void printStudents() {
  for (int i = 0; i < TABLE_SIZE;
       i++) { // Iterate over each index of array created

    // Intiate counter...
    Student *current = hashTable[i];
    // To iterate over each element that may be stored at same index
    while (current != NULL) {
      Student *temp = current; // Save current to handle later
      current =
          current->next; // Save replace current by current next to iterate
      printf("Index: %d, Name: %s, Age: %d, Average: %.2f\n", i, temp->name,
             temp->age, temp->grade);
    }
  }
}

// Free all memory
void freeHashTable() {
  for (int i = 0; i < TABLE_SIZE;
       i++) { // Iterate over each index of array created

    // Intiate counter...
    Student *current = hashTable[i];
    // To iterate over each element that may be stored at same index
    while (current != NULL) {
      Student *temp = current; // Save current to handle later
      current =
          current->next; // Save replace current by current next to iterate
      free(temp);        // Free current
    }
  }
}

int main() {
  // Insert some students
  insertStudent("Luc Doncieux", 21, 14.5);
  insertStudent("Yann Martinez", 22, 13.2);
  insertStudent("Julien Lefebvre", 20, 15.0);
  insertStudent("Aurélie Bassoli", 23, 12.8);

  // Setup user input
  char nameToFind[100];
  printf("Enter student name to search: ");
  fgets(nameToFind, sizeof(nameToFind), stdin);
  nameToFind[strcspn(nameToFind, "\n")] = '\0'; // Remove newline

  // Search for student
  Student *found = searchStudent(nameToFind);

  // Print result
  if (found) {
    printf("Found: %s, Age: %d, Average: %.2f\n", found->name, found->age,
           found->grade);
  } else {
    printf("Student '%s' not found.\n", nameToFind);
  }

  // Print all of the hashtable content
  printStudents();

  // Free memory
  freeHashTable();
  return 0;
}
