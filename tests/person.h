#ifndef _PERSON_H
# define _PERSON_H

#define PERSON_MAX_NAME_SIZE 100

typedef struct Person {
  int age;
  char name[];
} Person;

Person *person_new(char *name, int age);
void person_free(Person *person);

#endif // _PERSON_H


