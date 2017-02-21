#define TRUE 1
#define FALSE 0
#define MAX 25

typedef int EType;		// type of elements in stack
typedef int BOOLEAN;

typedef struct {
	EType data[MAX];
	int top;
} STACK;

void initialize(STACK *pS) 	// initialze the stack	
{

}

BOOLEAN isEmpty(STACK *pS) 	// returns true if the stack is empty
{

}

BOOLEAN isFull(STACK *pS)  	// returns true if the stack is full
{

}

BOOLEAN pop(STACK *pS, EType *px)	// removes the top element from the stack 
{					// has px point to the removed element   
       					// returns true if done successfully       


}

BOOLEAN push(EType x, STACK *pS)	// puts an element on the top of the stack  
{					// returns true if done successfully       


}

int main ()
{
	STACK s;
	int i;
	
	initialize (&s);

	// write code below to test functions defined above
 

	return 0;
}
