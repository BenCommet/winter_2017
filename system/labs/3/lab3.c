#include <stdio.h>
#include <string.h>

#define LEN 4

//char* strnsub (char *p, int n);

int main()
{
	char line[] = "His textbook was bought from that bookstore";  
	char *p1, *p2;

	p1 = line;
	//printf("%d", counter);
	while (*p1) 	
	{
		
                *p2 = p1[1];
		while (*p2){
			*p2 = p2[1];
		}
		*p1++;

//done:	//printf ("the first substring: %s\n", strnsub(p1, LEN));
	//printf ("the second substring: %s\n", strnsub(p2, LEN));

	}
	return 0;
}


// returns a string with the first n characters of string p

//char* strnsub (char *p, int n)
//{
	// write function definition here

//}
