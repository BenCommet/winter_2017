#include<stdio.h>
#include<pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

main(){
	//Get the password struct of the current user id from the system
	struct passwd *p = getpwuid(getuid());
	//print out user name, user ID and group ID respectively
	printf("User is: %s\n", p->pw_name);
	printf("UID is: %d\n", p->pw_uid);
	printf("GID is: %d\n", p->pw_gid);

	//This char will hold the host name
	char hostname[255];
	//Store the hostname in the hostname char array
	gethostname(hostname, 255);
	// print the hostname
	printf("Host is %s\n", hostname);

	int i;
	//print the names of the first five entries in the password file 
	for( i = 0; i < 5; i++){
		p = getpwuid(i);
		printf("entry %d: %s\n", i, p->pw_name);
	}

	//The char and char[] variables are used to read scanf(), userdone is used to determine
	//When the user has finished looking up environment variables userDone will be set to false
	char input[31];
	char *envValue;
	char isExit;
	int userDone = 1;
	//This while loop will run until the user types Y or y when prompted to exit
	while(userDone){
		printf("Enter desired environment variable: ");
		//Get the environment variable is looking for
		scanf("%s", input);
		//Get the value of the environment variable from the system
		envValue = getenv(input);
		//Check to see if the environment variable is null
		if(envValue){
			//Show the user the value of the enverionment variable
			printf("Value is: %s\n", envValue);
			int exitDecided = 0;
			//Runs until the user responds Y/y or N/n to the query
			while(!exitDecided){
				printf("Exit? Y/N: ");
				scanf(" %c", &isExit);
				if(isExit == 'n' || isExit == 'N'){
					//exit this while loop and loop through the top while loop again
					exitDecided = 1;
				}
				else if(isExit == 'y' || isExit == 'Y'){
					//exit both while loops
					exitDecided = 1;
					userDone = 0;
				}
			}

		}
		//If the environment varible is null, inform the user and ask if they want to go again
		else{
			printf("That is not a valid environment variable.\n");
			int exitDecided = 0;
			//Runs until the user responds Y/y or N/n to the query
			while(!exitDecided){
				printf("Exit? Y/N: ");
				scanf(" %c", &isExit);
				if(isExit == 'n' || isExit == 'N'){
					//exit this while loop and loop through the top while loop again
					exitDecided = 1;
				}
				else if(isExit == 'y' || isExit == 'Y'){
					//exit both while loops
					exitDecided = 1;
					userDone = 0;
				}
			}
		}
	}
	return 0;
}