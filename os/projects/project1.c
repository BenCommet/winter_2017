/*******************************************************************************************
* Programming Assignment 2: Standard Vector Processing
* Author: Ben Commet
* This program creates three processes, one which flips the bits of a binary string, one
* which adds one to said string and a third which performs addition using a string and
* the modified string which is now a two's complement of the originally supplied binary
* value. The three processes communicate via pipes and output using stderr. Due to the
* concurrent nature of this program, it is likely that the order and formatting of the
* output will vary slightly from what is expected.
*******************************************************************************************/

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
	//Pipeholders
	int com_to_inc[2];
	int inc_to_adder[2];
	//filenames
	char *file1;
	char *file2;
	//length of the files
	int num_elements;
	//file pointers
	FILE *fin1;
	FILE *fin2;
	//pipes for communicating between processes
	pid_t isIncrementerPid;
	pid_t adderPid;

	//Create the pipes used by the processes to communicate
	pipe(com_to_inc);
	pipe(inc_to_adder);

	//Set the handler that will start up all our processes
	signal (SIGINT, start_handler);

	//Ensure the number of command line arguments is correct
	if(argc != 5){
		printf("Input 2 command line arguments in the following format, <file1>, <file2> <number of elements>, <size of bits>.\n" );
		exit(1);
	}
	//Make sure the last two arguments are numbers
	if(!isNumber(argv[3]) || !isNumber(argv[4])){
		printf("Please input valid numbers as arguments.");
		exit(1);
	}
	//Convert numerical arguments into
	num_elements = atoi(argv[3]);
	num_bits = atoi(argv[4]);
	//get file names
	file1 = argv[1];
	file2 = argv[2];

	//Open the files in read mode
	fin2 = fopen (file1, "r");
	fin1 = fopen(file2, "r");
	//Check to see if files exist
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
	//Fork off into complementer and incrementer processes
	isIncrementerPid = fork();
	//This process will flip all the bits with string manipulation
	//All the processes will wait until the user hits C^
	if(isIncrementerPid){
			pause();
			fprintf(stderr, "Starting...\n" );
			char binary_string[num_bits + 1];
			//Read in lines from the file until we reach the end
			while(fgets(binary_string, num_bits + 3, fin1) != NULL){
				//Remove carriage return and endline characters from the file
				binary_string[strcspn(binary_string, "\r\n")] = 0;
				fprintf(stderr, "Complementer read: %s,		", binary_string);
				complementer(binary_string);
				fprintf(stderr, "Complementer sending: %s\n", binary_string);

				//close input stream
				close(com_to_inc[0]);
				//write to output stream
				write(com_to_inc[1], binary_string, sizeof(binary_string) + 1);
			}
	}
	else{
		//Set the exit handler for the incrementer and adder processes
		adderPid = fork();
		//This process adds one to each binary string passed to it
		if(adderPid){
			int i;
			for(i = 0; i < num_elements; i++){
				//close output stream
				close(com_to_inc[1]);
				char binary_string[num_bits + 1];
				//read in input stream from complementer
				read(com_to_inc[0], binary_string, sizeof(binary_string) + 1);

				fprintf(stderr, "Incrementer recieved :%s,		", binary_string);
				incrementer(binary_string);
				fprintf(stderr, "Incrementer Sending : %s\n", binary_string);

				//close input stream
				close(inc_to_adder[0]);
				//write to output stream
				write(inc_to_adder[1], binary_string, sizeof(binary_string) +1);
			}
		}
		//Adder process
		else{
			int i;
			for(i = 0; i < num_elements; i++){
				//close output stream
				close(inc_to_adder[1]);
				char binary_string_0[num_bits + 1];
				char binary_string_1[num_bits + 1];
				// read input from incrementer process
				read(inc_to_adder[0], binary_string_0, sizeof(binary_string_0) + 1);

				fprintf(stderr, "Adder Recieved: %s,		", binary_string_0);
				//Make sure that each fgets works correctly
				if(fgets(binary_string_1, num_bits + 3, fin2) == NULL){
					fprintf(stderr, "Error: file 2 length is not equal to the user supplied parameter");
					exit(1);
				}

				//Remove carriage returns and end lines
				binary_string_1[strcspn(binary_string_1, "\r\n")] = 0;
				fprintf(stderr, "Adder Read: %s,	", binary_string_1);
				adder(binary_string_0, binary_string_1);
				fprintf(stderr, "Adder writing %s\n", binary_string_0);
			}
		}
	}
	// close off the pipes
	close(com_to_inc[0]);
	close(com_to_inc[1]);
	close(inc_to_adder[0]);
	close(inc_to_adder[1]);
	return 0;
}

/*******************************************************************************************
* This function determines if the string passed in as a parameter consists of valid numbers
* @param{char *} number - This string is iterated over char by char to see if it is a number
* @return{int} - 1 if the number is valid, 0 if invalid
*******************************************************************************************/
int isNumber(char *number)
{
  for (i = 0; number[i] != 0; i++)
  {
    if (!isdigit(number[i]))
    	return 0;
  }
    return 1;
}

/*******************************************************************************************
* This function flips the bits of a binary number represented as a string
* @param{char *} binary_string - This parameter is originally read in from file A and is
* modified here to have its bits flipped
*******************************************************************************************/
void complementer(char *binary_string){
	int i;
	//Iterate through the string flipping its bits
	for(i = 0; i < num_bits; i++){
		if(binary_string[i] == '0'){ binary_string[i] = '1';}
		else{binary_string[i] = '0';}
	}
}

/*******************************************************************************************
* This funciton adds one to a string representation of a binary number
* @param{char *} binary_string - This parameter is originally piped in from the complementer
*	process and is modified here to have one added to it.
*******************************************************************************************/
void incrementer(char *binary_string){
	int i;
	//loop until we get to the end of the string
	for(i = num_bits -1; i >=0; i--){
		//flip the ones simulating a carry
		if(binary_string[i] == '1'){ binary_string[i] = '0';}
		else{
			//drop the carry and prevent the loop from modifying more positions
			binary_string[i] = '1';
			break;
		}
	}
}

/*******************************************************************************************
* This function adds two binary numbers represented as strings to one another.
* @param {char *} minuend - number being subtracted from, we will modify this string for use
* by the adder process. This was piped in by the incrementer process
* @param {char *} subtrahend - number being used to subtract, piped in by the incrementer process
*******************************************************************************************/
void adder(char *minuend, char *subtrahend){
	int i = strlen(minuend) - 1;
	// fprintf(stderr, "  %s\n+ %s", minuend, subtrahend);

	int carry = 0;
	//Loop from the end to the beginning of the string
	while(*(minuend + i)){
		//get the number at the current posiition
		int num_0 = minuend[i] - '0';
		int num_1 = subtrahend[i] - '0';
		int total = carry + num_0 + num_1;
		//minuend needs to be zero, is already set to zero, 1 = 1, 2 = 10, 3 = 11
		if(!total){ carry = 0;}
		else if(total == 1){ minuend[i] = '1'; carry = 0;}
		else if(total == 2){ minuend[i] = '0'; carry = 1;}
		else if(total == 3){ minuend[i] = '1'; carry = 1;}
		i--;
	}
	// fprintf(stderr, "__________\n  %s\n\n", minuend);

}

/*******************************************************************************************
* Used to kill all the processes
* @param{int} sigNum - required parameter, unused
*******************************************************************************************/
void exit_handler (int sigNum)
{
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}

/*******************************************************************************************
* Used to start all the processes
* @param{int} sigNum - required parameter, unused
*******************************************************************************************/
void start_handler(int sigNum){
	//have the processes listen for the exit handler
	signal (SIGINT, exit_handler);
}
