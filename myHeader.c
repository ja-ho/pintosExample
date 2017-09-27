#include "myHeader.h"

/*command process*/

//divide the parameter into tokens, and count them. return the count number.
int tokenizer(char* str, char token[][MAX_TOKEN_SIZE])
{
	char* tempStr;
	int count = 0;
	tempStr= strtok(str, " ");
	token[count][0] = '\0';
	token[count] = tempStr;
	count++;
	while(tempStr=strtok(NULL, " ")) {
		token[count][0] = '\0';
		token[count] = tempStr;
		count++;
	}

	return count;
}

//handle the command taken by token[][], and process it.
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount)
{
	

	if(strcmp(token[0], "quit" == 0)) {
		return -1;
	}
	
	if(strcmp(token[0], "create" ==0)) {
		if(strcmp(token[1], "list" == 0)) {
			
		} else if(strcmp(token[1], "hashtable" == 0)) {
		
		} else if(strcmp(token[1], "bitmap" == 0)) {
		
		} 
	} else if (strcmp(token[0], "delete" == 0)) {
	
	} else if (strcmp(token[0], "dumpdata" == 0)) {

	// list function
	} else if (strcmp(token[0], "list_insert" == 0)) {
	
	} else if (strcmp(token[0], "list_splice" == 0)) {
	
	} else if (strcmp(token[0], "list_push_front" == 0)) {
	
	} else if (strcmp(token[0], "list_push_back" == 0)) {
	
	} else if (strcmp(token[0], "list_remove" == 0)) {
	
	} else if (strcmp(token[0], "list_pop_front" == 0)) {
	
	} else if (strcmp(token[0], "list_pop_back" == 0)) {
	
	} else if (strcmp(token[0], "list_front" == 0)) {
	
	} else if (strcmp(token[0], "list_back" == 0)) {
	
	} else if (strcmp(token[0], "list_size" == 0)) {

	} else if (strcmp(token[0], "list_empty" == 0)) {
	
	} else if (strcmp(token[0], "list_reverse" == 0)) {

	} else if (strcmp(token[0], "list_sort" == 0)) {
	
	} else if (strcmp(token[0], "list_insert_ordered" == 0)) {

	} else if (strcmp(token[0], "list_unique" == 0)) {
	
	} else if (strcmp(token[0], "list_max" == 0)) {
	
	} else if (strcmp(token[0], "list_min" == 0)) {
	
	//hashtable function
	} else if (strcmp(token[0], "hash_insert" == 0)) {
	
	} else if (strcmp(token[0], "hash_replace" == 0)) {
	
	} else if (strcmp(token[0], "hash_find" == 0)) {
	
	} else if (strcmp(token[0], "hash_delete" == 0)) {
	
	} else if (strcmp(token[0], "hash_clear" == 0)) {
	
	} else if (strcmp(token[0], "hash_size" == 0)) {
	
	} else if (strcmp(token[0], "hash_empty" == 0)) {
	
	} else if (strcmp(token[0], "hash_apply" == 0)) {
	
	//bitmap function
	} else if (strcmp(token[0], "bitmap_size" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_set" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_mark" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_reset" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_flip" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_test" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_set_all" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_set_multiple" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_count" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_contains" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_any" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_none" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_all" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_scan" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_scan_and_flip" == 0)) {
	
	} else if (strcmp(token[0], "bitmap_dump" == 0)) {
	
	}
	
	
	
	
	
	
	



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

/*Hashtable*/

//return hash value of integer i
unsigned hash_int_2(int i)
{
	
}


/*Bitmap*/

//expand Bitmap's size
struct Bitmap *bitmap_expand(struct bitmap *bitmap, int size)
{
	
}
