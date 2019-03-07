#include "person.h"
#include <stddef.h>
#include <string.h>
//#include <stdlib.h>
#include "abmalloc.h"

Person *person_new(char *name, int age) {
  size_t nameLength = strnlen(name, PERSON_MAX_NAME_SIZE);
  Person *person = malloc(sizeof(Person) + nameLength + 1);
  person->age = age;
  strncpy(person->name, name, nameLength);
  return person;
}

void person_free(Person *person) {
  free(person);
}
