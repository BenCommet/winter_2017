#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <time.h>
#include <ctype.h>


bool isNumber(char[]);
int main(int argc, char **argv){
	if(argc != 3){
		printf("Input 2 command line arguments in the following format, <number of elements>, <size of bits>.\n" );
	}
	if(!isNumber(argv[1]) || !isNumber(argv[2])){
		printf("Please input a valid numbers as arguments.");
	}

	return 0;
}

bool isNumber(char number[])
{
    //checking for negative numbers
    if (number[0] == '-')
        return false;
 	int i;
    for (i = 0; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}