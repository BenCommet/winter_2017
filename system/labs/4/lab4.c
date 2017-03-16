#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mark {
	int x;
	int y;
};

typedef struct Mark Mark;

/* load the structure that p points to with the date from f */
void getInfo (FILE * f, Mark * p);

/* write the data stored in structure item into output file f */
void printInfo (FILE * f, Mark item);

/* compare what pointers a and b point to; to be used by qsort() */
int compare (const void * a, const void * b);

int main()
{
	Mark list[100];
	Mark mark;
	int size = 0, i, col = 0;
	FILE * fin;

	fin = fopen ("lab4.dat", "r");
	if ( fin == NULL )
	{
		printf ("Cannot open file.\n");
		exit(1);
	}

	while ( !feof(fin) )
	{
		getInfo (fin, &mark);
		list[size++] = mark;
	}

	// use qsort() to sort data in list
	qsort(list, size, sizeof list[0], compare);



	for (i = 0; i < size; i++)
	{
		printInfo (stdout, list[i]);
		if ( ++col % 5 == 0 )
			fprintf(stdout, "\n");
	}

	fclose (fin);

	return 0;
}

/* complete the following helper functions */

void getInfo (FILE * f, Mark * p)
{
	char input[4];
	fgets(input, sizeof(20), f);
	strtok(input, "\n");
	p->x = atoi(input);
	fgets(input, sizeof(20), f);
	strtok(input, "\n");
	p->y = atoi(input);

}

void printInfo (FILE * f, Mark item)
{
	fprintf(stdout, "(%d, %d) ", item.x, item.y);

}

int compare (const void * a, const void * b)
{
	// compare two structures
	// return 0 if they are equal, a value less than 0 if the first
	// comes before the second, a value greater than 0 otherwise
	Mark *markA = (Mark *)a;
	Mark *markB = (Mark *)b;

	int comp1 = markA->x - markB->x;
	int comp2 = markA->y - markB->y;
	if(comp1){ return comp1;}
	else{return comp2;}
}
