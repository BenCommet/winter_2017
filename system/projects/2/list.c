#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IDENTIFIER_LENGTH 31
#define true 1
#define false 0

struct node{
    char *identifier;
    int occurences;
    struct node *next;
};
struct node *head = NULL;

void printList(){
    FILE *file_out;
    file_out = fopen("output.txt", "w");
    struct node *current = head;
    while(current != NULL){
        // printf("%s: %d\n", current->identifier, current->occurences );
        fprintf(file_out, "%s: %d\n", current->identifier, current->occurences );
        current = current -> next;
    }

}

void initialize_list(char *_identifier){
    head = (struct node *) malloc(sizeof(struct node));
    head->identifier = _identifier;
    head->occurences = 1;
    head->next = NULL;
}

void push(char _identifier[]){
    if(head == NULL){
      initialize_list(_identifier);
    }
    else{
      struct node * new_node;
      new_node = malloc(sizeof(struct node));
      new_node->occurences = 1;
      new_node->identifier = _identifier;
      new_node->next = head;
      head = new_node;
      return;
    }
}

int remove_by_identifier(char * _identifier){
  struct node * current = head;
  struct node * previous = NULL;

  if(strcmp(head->identifier, _identifier)){
    head = head->next;
    return true;
  }

  while(current != NULL){
    if(strcmp(_identifier, current->identifier) == 0){
      previous->next = current->next;
    }
    previous = current;
    current = current->next;
    return true;
  }
  return false;
}

void move_to_front(struct node * current, struct node * previous){
    //if previous is null then we are at head and don't need to do anything
    if(previous == NULL){
        return;
    }
    previous->next = current->next;
    current->next = head;
    head = current;
}

void add_identifier( char *_identifier){
    //make local copy of string
    char *copy = malloc(1 + strlen(_identifier));
    if(copy){ strcpy(copy, _identifier);}
    struct node * current = head;
    struct node * previous = NULL;
    while(current != NULL){
        if(strcmp(copy, current->identifier) == 0){
            current->occurences++;
            move_to_front(current, previous);

            return;
        }
        previous = current;
        current = current -> next;
    }
    //We will only reach this point in the method if the identifier is currently not in the list
    push(copy);
}

// int main() {
//     initialize_list("squeesh");
//     add_identifier("deesh");
//     add_identifier("famish");
//     add_identifier("deesh");
//     add_identifier("deesh");
//     add_identifier("famish");
//     printList();
//     return 0;
// }
