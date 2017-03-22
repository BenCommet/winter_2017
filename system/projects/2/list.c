#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char *identifier;
    int occurences;
    struct node *next;
};
struct node *head;

void printList(){
    struct node *current = head;
    while(current != NULL){
        printf("%s: %d\n", current->identifier, current->occurences );
        current = current -> next;
    }
}

void initialize_list(char *_identifier){
    head = (struct node *) malloc(sizeof(struct node));
    head->identifier = _identifier;
    head->occurences = 1;
    head->next = NULL;
}

void push(char * _identifier){
    struct node * new_node;
    new_node = malloc(sizeof(struct node));
    new_node->occurences = 1;
    new_node->identifier = _identifier;
    new_node->next = head;
    head = new_node;
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

void add_identifier( char _identifier[]){
    struct node * current = head;
    struct node * previous = NULL;
    printf("%s : %s\n",_identifier, current->identifier );
    while(current != NULL){
        if(strcmp(_identifier, current->identifier) == 0){
            current->occurences++;
            move_to_front(current, previous);
            return;
        }
        previous = current;
        current = current -> next;
    }
    //We will only reach this point in the method if the identifier is currently not in the list
    push(_identifier);
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
