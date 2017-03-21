/***************************************************************/
/* Author:			Chris Hooker
/* Date:			5/20/2012
/* File Name:		Proj1.c
/* Project No:		1
/* Description: Load, print, sort a list of books, and do lookups
/* in the list by price and code.
/***************************************************************/

#include <stdio.h>

#define MAX 100

struct Book {
	int code;
	float price;
};


void loadArray (struct Book list[], int* numOfBooksPtr);

void printArray (struct Book list[], int numOfBooks);

int Count (struct Book list[], int numOfBooks, float targetPrice);

void Sort (struct Book list[], int numOfBooks);

float FindPrice (struct Book list[], int numOfBooks, int targetCode);

void PriceSearch (struct Book list[], int numOfBooks);

void CodeSearch (struct Book list[], int numOfBooks);


main()
{
	int numOfBooks;
	struct Book list[MAX];

	// Get the list of books from the user
	loadArray (list, &numOfBooks);
	printf ("\n\n");

	// Print out the list
	printf ("Book list:\n");
	printArray (list, numOfBooks);
	printf ("\n\n");

	// Sort the list
	Sort(list, numOfBooks);

	// Print out the sorted list
	printf ("Book list, sorted by Code:\n");
	printArray (list, numOfBooks);
	printf ("\n\n");

	// Let the user search for all books under a given price
	PriceSearch (list, numOfBooks);

	// Let the user get the price of a book by entering its code
	CodeSearch (list, numOfBooks);

	return 0;
}

/***************************************************************/
/* void loadArray
/* Parameters:
/*		struct Book list[] - the list to store the books in
/*		int* numOfBooksPtr - pointer to the variable to store
/*				     the number of books in the list
/* Description:
/*		Load a list of book codes and prices, based on user input.
/****************************************************************/

void loadArray (struct Book list[], int* numOfBooksPtr)
{
	int aCode;
	float aPrice;

	*numOfBooksPtr = 0;

	printf ("Code of Book (9999 to end) ? ");

	scanf("%d", &aCode);

	while ( aCode != 9999 )
	{
		// Get the price of the book
		// A price of zero is disallowed
		do
		{
			printf ("Price of Book ? ");

			scanf("%f", &aPrice);

			if (aPrice == 0.00)
				printf ("A price of $0 is not allowed!\n");

		} while (aPrice == 0.00);

		list[*numOfBooksPtr].code = aCode;

		list[*numOfBooksPtr].price = aPrice;

		(*numOfBooksPtr)++;

		printf ("Code of Book (9999 to end) ? ");

		scanf("%d", &aCode);
	}

}

/***************************************************************/
/* void printArray
/* Parameters:
/*		struct Book list[] - the list of books
/*		int numOfBooks - the number of books in the list
/* Description:
/*		Display a list of book codes and prices on screen.
/****************************************************************/

void printArray (struct Book list[], int numOfBooks)
{
	int index;

	printf("\n\n%10s%10s", "CODE", "PRICE");
	printf("\n");

	for (index = 0; index < numOfBooks; index++)
	{
		printf("%10d%10.2f\n", list[index].code, list[index].price);
	}
}

/***************************************************************/
/* int Count
/* Parameters:
/*		struct Book list[] - the list of books
/*		int numOfBooks - the number of books in the list
/*		float targetPrice - the price to compare against
/* Description:
/*		Return the number of books whose price is less than
/*		a target price.
/****************************************************************/

int Count (struct Book list[], int numOfBooks, float targetPrice)
{
	int i;
	int count = 0;

	for (i=0; i<numOfBooks; i++)
	{
		if (list[i].price < targetPrice)
			count++;
	}

	return count;
}

/***************************************************************/
/* void Sort
/* Parameters:
/*		struct Book list[] - the list of books to sort
/*		int numOfBooks - the number of books in the list
/* Description:
/*		Sort a list of books in ascending order by code.
/****************************************************************/

void Sort (struct Book list[], int numOfBooks)
{
	int pos, i, smallest;
	struct Book temp;

	// Loop through each position in the list (except the last)
	for (pos=0; pos<numOfBooks-1; pos++)
	{
		smallest = pos;

		// Find the smallest element from the rest of the list
		for (i=pos+1; i<numOfBooks; i++)
		{
			if (list[i].code < list[smallest].code)
				smallest = i;
		}

		// Move the smallest element into the current position
		// But, don't bother moving the elements if their codes are the same
		if (list[pos].code != list[smallest].code)
		{
			temp = list[pos];
			list[pos] = list[smallest];
			list[smallest] = temp;
		}
	}
}

/***************************************************************/
/* float FindPrice
/* Parameters:
/*		struct Book list[] - the list of books
/*		int numOfBooks - the number of books in the list
/*		int targetCode - the code of the book whose price we want
/* Description:
/*		Return the price of a book, given its code.
/*		A price of 0.00 indicates the book is not found.
/* Notes:
/*		Because price = 0.00 indicates the book was not found,
/*		when the user first enters the books, we disallow a
/*		price of zero.
/****************************************************************/

float FindPrice (struct Book list[], int numOfBooks, int targetCode)

{
	int i;

	for (i=0; i<numOfBooks; i++)
		if (list[i].code == targetCode)
			return list[i].price;

	return 0.00;
}

/***************************************************************/
/* void PriceSearch
/* Parameters:
/*		struct Book list[] - the list of books to search
/*		int numOfBooks - the number of books in the list
/* Description:
/*		Lets the user search for books under a certain price.
/*		Loops until the user enters a target price of 9999.
/****************************************************************/

void PriceSearch (struct Book list[], int numOfBooks)
{
	float targetPrice = 0.00;

	do
	{
		printf ("Enter a target price (9999 to end): ");
		scanf ("%f", &targetPrice);
		if (targetPrice != 9999)
			printf ("Books under $%3.2f: %d\n\n", targetPrice, Count (list, numOfBooks, targetPrice));
	} while (targetPrice != 9999);

	printf ("\n\n");
}

/***************************************************************/
/* void CodeSearch
/* Parameters:
/*		struct Book list[] - the list of books to search
/*		int numOfBooks - the number of books in the list
/* Description:
/*		Lets the user get the price of a book by entering its code.
/*		Loops until the user enters a code of 9999.
/****************************************************************/

void CodeSearch (struct Book list[], int numOfBooks)
{
	int targetCode = 0;
	float price = 0.00;

	do
	{
		printf ("Enter a target code (9999 to end): ");
		scanf ("%d", &targetCode);
		if (targetCode != 9999)
		{
			price = FindPrice (list, numOfBooks, targetCode);
			if (price == 0.00)
				printf ("Book %d not found!\n\n", targetCode);
			else
				printf ("Price for book %d: $%3.2f\n\n", targetCode, price);
		}
	} while (targetCode != 9999);

	printf ("\n\n");
}
