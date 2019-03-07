#include "linked_list.h"
#include "person.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ANSWER 10

int main(int argc, char *argv[]) {
  LinkedList *linkedList = linked_list_new();
  char answer[MAX_ANSWER+1];
  while (true) {
    printf("What to do?\n");
    printf("[add] person\n");
    printf("[remove] person\n");
    printf("[show] person\n");
    printf("> ");
    fgets(answer, MAX_ANSWER, stdin);
    if (strncmp(answer, "add", 3) == 0) {
      printf("name> ");
      char name[MAX_ANSWER+1];
      fgets(name, MAX_ANSWER, stdin);
      printf("age> ");
      int age;
      scanf("%d%*c", &age);
      Person *person = person_new(name, age);
      linked_list_append(linkedList, person);
    } else if (strncmp(answer, "remove", 6) == 0) {
      printf("index> ");
      int index;
      scanf("%d%*c", &index);
      person_free(linked_list_remove(linkedList, index));
    } else if (strncmp(answer, "show", 4) == 0) {
      printf("index> ");
      int index;
      scanf("%d%*c", &index);
      Person *person = linked_list_get(linkedList, index);
      if (person == NULL) {
        printf("no person\n");
        continue;
      }
      printf("%s %d\n", person->name, person->age);
    } else if (strncmp(answer, "exit", 4) == 0) {
      linked_list_free(linkedList, (DataFreer)person_free);
      break;
    }
    printf("\n");
  }
  return 0;
}
