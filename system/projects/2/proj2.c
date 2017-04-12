#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
//31 is the maximum recommended identifier length for c so we will cap identifiers
//at that length
#define MAX_IDENTIFIER_LENGTH 31
#define true 1
#define false 0
/*******************************************************************************
* This method is responsible for determining what to do with a given char. It
* is responsible for determining if the current identifier is over and if it is
* the string will be passed to the linked list.
* @param{char []} currentString - The string of characters the program has added
* to the identifier so far.
* @param{char} newChar - The char we will either append to the end of the string
* if we determine that it is a valid char for an identifier, or we will add it
* to the linked list using the add_identifier function we have included from
* list.h
*******************************************************************************/
void handleChar(char currentString[], char newChar){
  currentString[strcspn(currentString, "\r\n")] = 0;
  int len = strlen(currentString);
  //If we are the first character we need to ensure that the character has no
  //numbers, _ is also a valid char
  if(len == 0){
    if(isalpha(newChar) || newChar == '_'){
      currentString[0] = newChar;
    }
  }
  //Now that we are past the first char the identifier can contain digits
  else if(isalpha(newChar) || newChar == '_' || isdigit(newChar)){
    currentString[len] = newChar;
  }
  //If we get to this point and the length is not 0, then we can add it to the list
  else if(len != 0){
    //Remove any endline chars
    currentString[strcspn(currentString, "\r\n")] = 0;
    add_identifier(currentString);
    memset(currentString, 0, MAX_IDENTIFIER_LENGTH);
  }
}

/*******************************************************************************
* This is the main method of our program. The user will supply two command line
* arguments. The first determines the file the program will be parsing, the
* second determines the file we will be outputting to.
* @param{int} argc - number of command line arguments
* @param{argv} - array of command line arguments
*******************************************************************************/
int main(int argc, char **argv){
  //Make sure the number of command line arguments is valid
    if(argc != 3){
      printf("The number of inputs is incorrect\n");
      printf("Please type the input file followed by the output file");
      exit(1);
    }

    char currentIdentifier[MAX_IDENTIFIER_LENGTH];
    currentIdentifier[0] = 's';
    FILE *file_in;
    char buf[1000];
    //These integers are responsible for determining if we are currently in a
    //comment or string.
    int isSingleLineComment = false;
    int isMultiLineComment = false;
    int isString = false;
    //open the file the user passed in
    file_in = fopen(argv[1], "r");
    if(!file_in){
        printf("File failed to open");
        return true;
    }
    //Iterate over each line of the file till we get to the end.
    while(fgets(buf, 1000, file_in)!=NULL){
        isSingleLineComment = 0;
        int i;
        for(i = 0; i < strlen(buf); i++){
          //If we are already in a comment or string don't look for beginning characters
          if(!isSingleLineComment && !isMultiLineComment && !isString){
            //Check if we are in a single or multi-line comment
            if(buf[i] == '/'){
              if(buf[i + 1] == '/'){
                isSingleLineComment = true;
              }
              if(buf[i + 1] == '*'){
                isSingleLineComment = false;
                isMultiLineComment = true;
              }
            }
            //Check if we are in a string
            else if(buf[i] == '"'){
               isString = true;
             }

          }
          //If we are already in a comment or string, check for ending characters
          else{
            //Check for end of mulitline comment
            if(isMultiLineComment && buf[i] == '*' && buf[i + 1] == '/'){
              isMultiLineComment = false;
            }
            //Check for end of string
            else if(isString && buf[i] == '"'){
              isString = false;
            }
          }
          //If we are not in a comment or string send the character over to the
          //method that handles what to do with potentially valid identifier chars
          if(!isSingleLineComment && !isMultiLineComment && !isString){
            handleChar(currentIdentifier, buf[i]);
          }
        }
    }
    fclose(file_in);

    //Print the results to the output file supplied by the user.
    print_list(argv[2]);
    return false;

}
