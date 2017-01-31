#include <stdio.h>
#include <ctype.h>
int main () {
	char ch;
	int symbolSequences = 0;
	int wordCount = 0;
	//These will be used as booleans to keep track of whether the text is currently a word
	int isCurrentlyWord = 0;
	int isCurrentlySymbol = 0;
	printf ("Enter text (Ctrl-D to quit).\n");
	while ( ch = getchar(), ch != EOF ) {
		if(isspace(ch)){
			isCurrentlyWord = 0;
			isCurrentlySymbol = 0;
		}
		else if(isalnum(ch)){
			if(!isCurrentlyWord){
				isCurrentlyWord = 1;
				wordCount++;
			}
			if(isCurrentlySymbol){
				isCurrentlySymbol = 0;
			}
		}
		else{
			if(!isCurrentlySymbol){
				isCurrentlySymbol = 1;
				symbolSequences++;
			}
			if(isCurrentlyWord){
				isCurrentlyWord = 0;
			}
		}
	}

	printf("\nNumber of words: %d\n", wordCount);
	printf("Number of symbol Sequences: %d\n", symbolSequences);
	return 0;
}
