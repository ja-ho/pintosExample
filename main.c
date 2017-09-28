#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

#define MAX_STR_SIZE 128
#define MAX_TOKEN_NAME 20
#define MAX_TOKEN_SIZE 5

typedef enum _data_type {
	LIST, HASH, BITMAP
} data_type;

typedef struct _data_table {
	struct list_elem elem;
	char data_name[MAX_TOKEN_NAME];
	void *dataPointer;
	data_type type;
} data_table;

typedef struct _list_node {
	struct list_elem elem;
	int data;
} list_node;

typedef struct _hash_node {
	struct hash_elem elem;
	int data;
} hash_node;

//command process
int tokenizer(char* str, char token[][MAX_STR_SIZE]);
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount, struct list* table_data);

//list_func
bool _list_less_func(const struct list_elem *a, const struct list_elem *b, void *aux);

//hash_func
unsigned _hash_hash_func(const struct hash_elem *e, void *aux);

bool _hash_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux);

void _destructor(struct hash_elem *e, void *aux);

int main() {
	char str[MAX_STR_SIZE]= {'\0',};
	char token[MAX_TOKEN_SIZE][MAX_STR_SIZE];
	int tokenCount=0;
	
	struct list table_data;
	list_init(&table_data);

	while(true) {
		fgets(str, MAX_STR_SIZE, stdin);
		tokenCount= tokenizer(str, token);
		if(tokenCount != 0) {
			if(commandHandler(token, tokenCount, &table_data)) {
				break;
			}
		}
	}

	return 0;
}

/*command process*/

//divide the parameter into tokens, and count them. return the count number.
int tokenizer(char* str, char token[][MAX_STR_SIZE])
{
	char* tempStr;
	int count = 0;
	tempStr= strtok(str, " ");
	token[count][0] = '\0';
	strcpy(token[count], tempStr);
	count++;
	while(tempStr=strtok(NULL, " ")) {
		token[count][0] = '\0';
		strcpy(token[count], tempStr);
		count++;
	}

	return count;
}

//handle the command taken by token[][], and process it.
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount, struct list *table_data)
{		
	data_table *tempTable;
	struct list_elem *temp;
	bool isExist = false;

	if(strcmp(token[0], "quit") == 0) {
		return -1;
	}
	
	if(strcmp(token[0], "create") ==0) {
		if(strcmp(token[1], "list") == 0) {
			isExist = false;
			struct list *listPointer;
			for(temp = list_begin(table_data); temp != list_end(table_data); temp = list_next(temp)) {
				tempTable = list_entry(temp, data_table, elem);
				if(strcmp(tempTable->data_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}
			if(!isExist) {
				tempTable = (data_table*)malloc(sizeof(data_table));
				strcpy(tempTable->data_name, token[2]);
				listPointer = (struct list*)malloc(sizeof(struct list));
				list_init(listPointer);
				tempTable->type = LIST;
				tempTable->dataPointer = (void*)listPointer;
				list_push_back(table_data, &(tempTable->elem));
			}
		
		} else if(strcmp(token[1], "hashtable" == 0)) {
			isExist = false;
			struct hash *hashPointer;
			for(temp = list_begin(table_data); temp != list_end(table_data); temp = list_next(temp)) {
				tempTable = list_entry(temp, data_table, elem);
				if(strcmp(tempTable->data_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}	
			if(!isExist) {
				tempTable = (data_table*)malloc(sizeof(data_table));
				strcpy(tempTable->data_name, token[2]);
				hashPointer = (struct hash*)malloc(sizeof(struct hash));
				hash_init(hashPointer, _hash_hash_func, _hash_less_func, NULL);
				tempTable->type = HASH;
				tempTable->dataPointer = (void*)hashPointer;
				list_push_back(table_data, &(tempTable->elem));
			}
		} else if(strcmp(token[1], "bitmap" == 0)) {
			isExist = false;
			size_t bit_cnt;
			struct bitmap *bitmapPointer;
			for(temp = list_begin(table_data); temp != list_end(table_data); temp = list_next(temp)) {
				tempTable = list_entry(temp, data_table, elem);
				if(strcmp(tempTable->data_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}
			if(!isExist) {
				tempTable = (data_table*)malloc(sizeof(data_table));
				strcpy(tempTable->data_name, token[2]);
				bit_cnt = (size_t)atoi(token[3]);
				bitmapPointer = bitmap_create(bit_cnt);
				tempTable->type = BITMAP;
				tempTable->dataPointer = (void*)bitmapPointer;
				list_push_back(table_data, &(tempTable->elem));
			}

		} 
	} else if (strcmp(token[0], "delete" == 0)) {
		isExist = false;
		struct list *listPointer;
		struct hash *hashPointer;
		struct bitmap *bitmapPointer;
		for(temp = list_begin(table_data); temp != list_end(table_data); temp = list_next(temp)) {
			tempTable = list_entry(temp, data_table, elem);
			if(strcmp(tempTable->data_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			if(tempTable->type == LIST) {
				listPointer = (struct list*)tempTable->dataPointer;
				for(temp = list_begin(listPointer); temp != list_end(listPointer);) {
					list_node* node = list_entry(temp, list_node, elem);
					temp = list_remove(&(node->elem));
					free(node);
				}
				list_remove(&(tempTable->elem));
				free(tempTable);
				
			} else if (tempTable->type == HASH) {
				hashPointer = (struct hash*)tempTable->dataPointer;
				hash_destroy(hashPointer, _destructor);
				list_remove(&(tempTable->elem));
				free(tempTable);		
			} else if (tempTable->type == BITMAP) {
				bitmapPointer = (struct bitmap*)tempTable->dataPointer;
				bitmap_destroy(bitmapPointer);
				list_remove(&(tempTable->elem));
				free(tempTable);
			}
		}
	} else if (strcmp(token[0], "dumpdata" == 0)) {
		isExist = false;
		struct list *listPointer;
		struct hash *hashPointer;
		struct bitmap *bitmapPointer;
		for(temp = list_begin(table_data); temp != list_end(table_data); temp = list_next(temp)) {
			tempTable = list_entry(temp, data_table, elem);
			if(strcmp(tempTable->data_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
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


//list_func
bool _list_less_func(const struct list_elem *a, const struct list_elem *b, void *aux)
{
	list_node* tempA;
	list_node* tempB;
	tempA = list_entry(a, list_node, elem);
	tempB = list_entry(b, list_node, elem);
	if(tempA->data < tempB->data) return true;
	else return false;
}

//hash_func
unsigned _hash_hash_func(const struct hash_elem *e, void *aux)
{
	hash_node* temp = hash_entry(e, hash_node, elem);
	return hash_int(temp->data);
}

bool _hash_less_func(const struct hash_elem *a, const struct hash_elem *b, void *aux)
{
	hash_node* tempA = hash_entry(a, hash_node, elem);
	hash_node* tempB = hash_entry(b, hash_node, elem);
	if(tempA->data < tempB->data) return true;
	else return false;
}

void _destructor(struct hash_elem *e, void *aux)
{
	hash_node* temp = hash_entry(e, hash_node, elem);
	free(temp);
	return;
}
