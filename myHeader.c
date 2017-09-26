#include "myHeader.h"

/*command process*/

//divide the parameter into tokens, and count them. return the count number.
int tokenizer(char* str, char token[][MAX_TOKEN_SIZE])
{
	char* tempStr;
	int count = 0;
	tempStr= strtok(str, " \t\n");
	token[count] = tempStr;
	count++;
	while(tempStr=strtok(NULL, "\t\n")) {
		token[count] = tempStr;
		count++;
	}

	return count;
}


/*List*/
//swap two elements of list which is taken by parameter.
void list_swap(struct list_elem *a, struct list_elem *b)
{
	struct list_elem* temp = NULL;
	
	if(a->next != NULL) {
		a->next->prev = b;
	}

	if(a->prev != NULL) {
		a->prev->next = b;
	}
	
	if(b->next != NULL) {
		b->next->prev = a;
	}

	if(b->prev != NULL) {
		b->prev->next = a;
	}

	temp->next = a->next;
	temp->prev = a->prev;

	a->next = b->next;
	a->prev = b->prev;

	b->next = temp->next;
	b->prev = temp->prev;
	
}


