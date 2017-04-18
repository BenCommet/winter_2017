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

/*******************************************************************************
* This method iterates over the list and saves it to an external file
*******************************************************************************/
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

/*******************************************************************************
* This method is called when the user tries to add an element to the linked
* list when there is not currently a head. It creates a new node, points the
* global head variable at it and set's its identifier and occurences
* @param{char []} _identifier - this char array holds the string that needs to
* be added to the head
*******************************************************************************/
void initialize_list(char *_identifier){
    head = (struct node *) malloc(sizeof(struct node));
    head->identifier = _identifier;
    head->occurences = 1;
    head->next = NULL;
}

/*******************************************************************************
* This method adds a new node to the linked list with the given identifier. It
* will also increment that nodes occurences property by one to keep track of the
* number of instances
* @param{char[]} _identifier - this char array holds the string that needs to
* be added to the list
*******************************************************************************/
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

/*******************************************************************************
* This method will search over the linked list until it hits a node with an
* identifier that is equal to the passed string. When it does it will remove
* the node from the linked list
* @param{char[]} _identifier - the identifier of a node we are trying to remove
* @return{int} 0/false is returned if the method fails to remove a node, 1 for
* the reverse
*******************************************************************************/
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

/*******************************************************************************
* This method will return the number of instances a certain identifier has had
* in the linked list
* @param{char[]} _identifier - string we want to find the number of instances of
* @return{int} - the number of instances of the identifier in the list
*******************************************************************************/
int get_identifier_instances(char * _identifier){
  struct node * current = head;
  while(current != NULL){
    if(strcmp(_identifier, current->identifier) == 0){
      return current->occurences;
    }
    return 0;
  }
}

/*******************************************************************************
* This function will move a node to the front of the list
* @param{node *} current - the node we will be moving to the front
* @param{node *} previous - the node prior to the current node, we will need it
* to keep the list linked
*******************************************************************************/
void move_to_front(struct node * current, struct node * previous){
    //if previous is null then we are at head and don't need to do anything
    if(previous == NULL){
        return;
    }
    //Skip over the current node and then set the current node to be the head
    previous->next = current->next;
    current->next = head;
    head = current;
}

/*******************************************************************************
* This function takes an identifier and either adds it to the list if the
* identifer has not yet been added, or increments an existing node's occurences
* property to show there was an additional instance of the identifer
* @param{char[]} _identifier - the string we are checking either adding to or
* incrementing in the list
*******************************************************************************/
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
