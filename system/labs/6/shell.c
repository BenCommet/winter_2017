
#define MAXARG 20
#define MAXLINE 80
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>

int background(char **args);


int main(int argc, char **argv){
	//Make the array one larger than fgets allows to let us concatonate a space
	//at the end
	char input[MAXLINE];
	printf("shell> ");
	//Accept user input until they quit out
	while(1){
		//limit input to the size of the predeclared input array
		fgets(input, MAXLINE - 1, stdin);
		input[strlen(input) -1] = 0;
		char* checkForSpace = strchr(input, ' ');
		//if there are no spaces add one at the end so the tokenizer still works
		if(checkForSpace == NULL){
			strcat(input, " ");
		}
		//This pointer will receive tokens
		int iterator = 0;
		char **tokens = malloc(MAXLINE * sizeof(char*));
		char *token;
		//tokenize the input string
		token = strtok(input, " ");
		while(token != NULL){
            // Iterates through the created tokens from the user input, quits out when the tokenizer returns a NULL string
			tokens[iterator] = token;
			iterator ++;
			token = strtok(NULL, " ");
		}
		//Launch a process using the array of tokens
		background(tokens);
	}
	return 0;
}
/******************************************************************
 *Launch process does the majority of the work. This is where
 we check our exit call, or if the input is invalid. Additionally,
 we get the information about context switches and the usage
 time it takes for each process.
*******************************************************************/
int background(char **args){
	pid_t pid;
	int status;
    //Checking to see if input is quit, if it is, then program exits. Otherwise
    //the program continues.
	if(strcmp(args[0], "exit") == 0){
		printf("exiting!\n");
		exit(0);
	}
	//Fork and get the PID of forks
	pid = fork();
	//child process returns zero, if in child process, execute commands
	if (pid == 0){
		if(execvp(args[0], args) == -1){
			fprintf(stderr, "The command entered is invalid\n");
		}
		exit(0);
	}
	else{
		//wait and print the cpu usage statistics
		waitpid(-1, &status, 0);
	}
	//print shell> to make it move apparent that this is a prompt
	printf("shell>");
	return 0;
}
