/*******************************************************************************
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int num_bits;

void complementer(char *);
void incrementer(char *);
int isNumber(char[]);
void adder(char *, char *);
int main(int argc, char **argv){
	//pipes for communicating between processes
	int com_to_inc[2];
	int inc_to_adder[2];
	char *file1;
	char *file2;
	int num_elements;
	FILE *fin1;
	FILE *fin2;
	pid_t incrementerPid;
	pid_t adderPid;

	pipe(com_to_inc);
	pipe(inc_to_adder);
	if(argc != 5){
		printf("Input 2 command line arguments in the following format, <file1>, <file2> <number of elements>, <size of bits>.\n" );
		exit(1);
	}
	if(!isNumber(argv[3]) || !isNumber(argv[4])){
		printf("Please input valid numbers as arguments.");
		exit(1);
	}

	file1 = argv[1];
	file2 = argv[2];
	num_elements = atoi(argv[3]);
	num_bits = atoi(argv[4]);

	//Open the file
	fin1 = fopen (file1, "r");
	fin2 = fopen(file2, "r");
	//Check to see if file exists
	if ( fin1 == NULL )
	{
		printf ("Cannot open file 1.\n");
		exit(1);
	}

	if ( fin2 == NULL )
	{
		printf ("Cannot open file 2.\n");
		exit(1);
	}
	incrementerPid = fork();
	//Incrementor process
	if(incrementerPid){
			char binary_string[num_bits + 1];
			while(fgets(binary_string, num_bits + 3, fin1) != NULL){
				complementer(binary_string);
				binary_string[strcspn(binary_string, "\r\n")] = 0;
				close(com_to_inc[0]);
				write(com_to_inc[1], binary_string, sizeof(binary_string) + 1);
			}
	}
	else{
		adderPid = fork();
		//Subtractor process;
		if(adderPid){
			int i;
			for(i = 0; i < num_elements; i++){
				close(com_to_inc[1]);
				char binary_string[num_bits + 1];
				read(com_to_inc[0], binary_string, sizeof(binary_string) + 1);
				incrementer(binary_string);
				close(inc_to_adder[0]);
				write(inc_to_adder[1], binary_string, sizeof(binary_string) +1);
			}

		}
		//Adder process
		else{
			int i;
			for(i = 0; i < num_elements; i++){
				close(inc_to_adder[1]);
				char binary_string_0[num_bits + 1];
				char binary_string_1[num_bits + 1];
				read(inc_to_adder[0], binary_string_0, sizeof(binary_string_0) + 1);
				if(fgets(binary_string_1, num_bits + 3, fin2) == NULL){
					fprintf(stderr, "Error: file 2 length is not equal to the user supplied parameter");
				}
				adder(binary_string_0, binary_string_1);
			}
		}
	}
	return 0;
}

/*******************************************************************************
*
*******************************************************************************/
int isNumber(char *number)
{
    //checking for negative numbers
    if (number[0] == '-')
        return 0;
 	  int i;
    for (i = 0; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

/*******************************************************************************
*
*******************************************************************************/
void complementer(char *binary_string){
	int i;
	//Iterate through the loop flipping bits
	for(i = 0; i < num_bits; i++){
		if(binary_string[i] == '0'){ binary_string[i] = '1';}
		else{binary_string[i] = '0';}
	}


}

/*******************************************************************************
*
*******************************************************************************/
void incrementer(char *binary_string){
	fprintf(stderr, "%s\n", binary_string);

	int i;
	for(i = num_bits -1; i >=0; i--){
		if(binary_string[i] == '1'){ binary_string[i] = '0';}
		else{
			binary_string[i] = '1';
			break;
		}
	}
	fprintf(stderr, "%s\n\n", binary_string);

}

/*******************************************************************************
*
*******************************************************************************/
void adder(char *minuend, char *subtrahend){
	int i;
	for(i = 0;)

}
