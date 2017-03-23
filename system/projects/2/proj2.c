#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#define MAX_IDENTIFIER_LENGTH 31
#define true 1
#define false 0

void handleChar(char currentString[], char newChar){
  currentString[strcspn(currentString, "\r\n")] = 0;
  int len = strlen(currentString);
  if(len == 0){
    if(isalpha(newChar) || newChar == '_'){
      currentString[0] = newChar;
    }
  }
  else if(isalpha(newChar) || newChar == '_' || isdigit(newChar)){
    currentString[len] = newChar;
  }
  else if(len != 0){
    currentString[strcspn(currentString, "\r\n")] = 0;
    add_identifier(currentString);
    memset(currentString, 0, MAX_IDENTIFIER_LENGTH);
  }
}

int main(){
    char currentIdentifier[MAX_IDENTIFIER_LENGTH];
    currentIdentifier[0] = 's';
    FILE *file_in;
    char buf[1000];
    int isSingleLineComment = false;
    int isMultiLineComment = false;
    int isString = false;
    file_in = fopen("sample.c", "r");
    if(!file_in){
        printf("File failed to open");
        return true;
    }
    while(fgets(buf, 1000, file_in)!=NULL){
        isSingleLineComment = 0;
        int i;
        for(i = 0; i < strlen(buf); i++){
          //If we are already in a comment or string don't look for beginning characters
          if(!isSingleLineComment && !isMultiLineComment && !isString){
            if(buf[i] == '/'){
              if(buf[i + 1] == '/'){
                isSingleLineComment = true;
              }
              if(buf[i + 1] == '*'){
                isSingleLineComment = false;
                isMultiLineComment = true;
              }
            }
            else if(buf[i] == '"'){
               isString = true;
             }
          }else{
            if(isMultiLineComment && buf[i] == '*' && buf[i + 1] == '/'){
              isMultiLineComment = false;
            }
            else if(isString && buf[i] == '"'){
              isString = false;
            }
          }
          if(!isSingleLineComment && !isMultiLineComment && !isString){
            handleChar(currentIdentifier, buf[i]);
          }
        }
    }
    fclose(file_in);

    printList();
    return false;

}
