#include<stdio.h>
#include<pwd.h>
#include <stdlib.h>
#include <unistd.h>

main(){
	struct passwd *p = getpwuid(getuid());
	printf("User is: %s\n", p->pw_name);
	printf("UID is: %d\n", p->pw_uid);
	printf("GID is: %d\n", p->pw_gid);

	char hostname[255];
	gethostname(hostname, 255);
	printf("Host is %s\n", hostname);

	int i;
	for( i = 0; i < 5; i++){
		p = getpwuid(i);
		printf("entry %d: %s\n", i, p->pw_name);
	}

	char input[31];
	char envValue[31];
	printf("Enter disired environment variable: ");
	scanf("%s", input);
	printf("%s\n", getenv(input));


}