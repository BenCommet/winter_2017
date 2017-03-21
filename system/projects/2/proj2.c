#include <stdio.h>
#include "list.h"
int main(){
    FILE *file_in;
    char buf[1000];
    int isSingleLineComment = 0;
    int isMultiLineComment = 0;
    int isString = 0;
    file_in = fopen("sample.c", "r");
    if(!file_in){
        printf("File failed to open");
        return 1;
    }
    while(fgets(buf, 1000, file_in)!=NULL){
        printf("(%s)\n", buf);
    }
    fclose(file_in);
    return 0;

}
