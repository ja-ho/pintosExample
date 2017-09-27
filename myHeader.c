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
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount, struct list *table_list, struct list *table_hash, 
																						struct list *table_bitmap)
{		
	struct list_table *lists;
	struct hash_table *hashs;
	struct bitmap_table *bitmaps;
	struct list_elem *temp;

	if(strcmp(token[0], "quit" == 0)) {
		return -1;
	}
	
	if(strcmp(token[0], "create" ==0)) {
		if(strcmp(token[1], "list" == 0)) {
			bool isExist = false;
				
		
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
	
	//my function
	} else if (strcmp(token[0], "list_swap" == 0)) {
	
	} else if (strcmp(token[0], "list_shuffle" == 0)) {
	
	//hashtable function
	} else if (strcmp(token[0], "hash_insert" == 0)) {
	
	} else if (strcmp(token[0], "hash_replace" == 0)) {
	
	} else if (strcmp(token[0], "hash_find" == 0)) {
	
	} else if (strcmp(token[0], "hash_delete" == 0)) {
	
	} else if (strcmp(token[0], "hash_clear" == 0)) {
	
	} else if (strcmp(token[0], "hash_size" == 0)) {
	
	} else if (strcmp(token[0], "hash_empty" == 0)) {
	
	} else if (strcmp(token[0], "hash_apply" == 0)) {
	
	//my function
	} else if (strcmp(token[0], "hash_int_2" == 0)) {
	
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

	//my function
	} else if (strcmp(token[0], "bitmap_expand" == 0)) {
	
	}
	
	
	
	
	return 0;
}



