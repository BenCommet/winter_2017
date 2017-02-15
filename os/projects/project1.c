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
void exit_handler(int);
void start_handler(int);
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

	//Create the pipes used by the processes to communicate
	pipe(com_to_inc);
	pipe(inc_to_adder);

	//Set the handler that will start up all our processes
	signal (SIGINT, start_handler);

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
	fin2 = fopen (file1, "r");
	fin1 = fopen(file2, "r");
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

	fprintf(stderr, "Press ^C to begin" );
	incrementerPid = fork();
	//Complementer process
	if(incrementerPid){
			pause();
			fprintf(stderr, "Starting...\n" );
			char binary_string[num_bits + 1];
			while(fgets(binary_string, num_bits + 3, fin1) != NULL){
				binary_string[strcspn(binary_string, "\r\n")] = 0;
				fprintf(stderr, "Complementer read: %s,		", binary_string);
				complementer(binary_string);
				fprintf(stderr, "Complementer sending: %s\n", binary_string);
				close(com_to_inc[0]);
				write(com_to_inc[1], binary_string, sizeof(binary_string) + 1);
			}
	}
	else{
		//Set the exit handler for the incrementer and adder processes
		adderPid = fork();
		//Incrementer process;
		if(adderPid){
			int i;
			for(i = 0; i < num_elements; i++){
				close(com_to_inc[1]);
				char binary_string[num_bits + 1];
				read(com_to_inc[0], binary_string, sizeof(binary_string) + 1);
				fprintf(stderr, "Incrementer recieved: %s,	", binary_string);
				incrementer(binary_string);
				fprintf(stderr, "Incrementer Sending: %s\n", binary_string);
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
				fprintf(stderr, "Adder Recieved: %s		", binary_string_0);
				if(fgets(binary_string_1, num_bits + 3, fin2) == NULL){
					fprintf(stderr, "Error: file 2 length is not equal to the user supplied parameter");
					exit(1);
				}
				binary_string_1[strcspn(binary_string_1, "\r\n")] = 0;
				fprintf(stderr, "Adder Read: %s,	", binary_string_1);
				adder(binary_string_0, binary_string_1);
				fprintf(stderr, "Adder writing %s\n", binary_string_0);
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
	int i;
	for(i = num_bits -1; i >=0; i--){
		if(binary_string[i] == '1'){ binary_string[i] = '0';}
		else{
			binary_string[i] = '1';
			break;
		}
	}

}

/*******************************************************************************
*
*******************************************************************************/
void adder(char *minuend, char *subtrahend){
	int i = strlen(minuend) - 1;
	// fprintf(stderr, "  %s\n+ %s", minuend, subtrahend);

	int carry = 0;
	while(*(minuend + i)){
		int num_0 = minuend[i] - '0';
		int num_1 = subtrahend[i] - '0';
		int total = carry + num_0 + num_1;
		//minuend needs to be zero, is already set to zero
		if(!total){ carry = 0;}
		else if(total == 1){ minuend[i] = '1'; carry = 0;}
		else if(total == 2){ minuend[i] = '0'; carry = 1;}
		else if(total == 3){ minuend[i] = '1'; carry = 1;}
		i--;
	}
	// fprintf(stderr, "__________\n  %s\n\n", minuend);

}

/*******************************************************************************
*
*******************************************************************************/
void exit_handler (int sigNum)
{
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}

/*******************************************************************************
*
*******************************************************************************/
void start_handler(int sigNum){
	signal (SIGINT, exit_handler);
}
