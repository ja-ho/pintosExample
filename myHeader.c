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

//shuffle the list randomly.
void list_shuffle(struct list* list)
{
	int i, j;
	int random_1, random_2;
	struct list_elem *first, *second;
	int listSize= list_size(list);
	for(i=0; i< listSize; i++) {
		random_1 = rand % listSize;
		random_2 = rand % listSize;
		if(random_1 == random_2) continue;

		first = list_begin(list);
		second = list_begin(list);
		for(j=0; j<random_1; j++) {
			first = list_next(first);
		}
		
		for(j=0; j<random_2; j++) {
			second = list_next(second);
		}
		list_swap(first, second);
	}
}
