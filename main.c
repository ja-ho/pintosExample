#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

#define MAX_STR_SIZE 128
#define MAX_TOKEN_NAME 20
#define MAX_TOKEN_SIZE 5

typedef struct _list_table {
	struct list_elem elem;
	char list_name[MAX_TOKEN_NAME];
	struct list *listPointer;
} list_table;

typedef struct _hash_table {
	struct list_elem elem;
	char hash_name[MAX_TOKEN_NAME];
	struct hash *hashPointer;
} hash_table;

typedef struct _bitmap_table {
	struct list_elem elem;
	char bitmap_name[MAX_TOKEN_NAME];
	struct bitmap *bitmapPointer;
} bitmap_table;

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
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount, struct list* lists,
						struct list* hashs, struct list* bitmaps);

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

	struct list lists;
	struct list hashs;
	struct list bitmaps;
	list_init(&lists);
	list_init(&hashs);
	list_init(&bitmaps);

	while(true) {
		fgets(str, MAX_STR_SIZE, stdin);
		tokenCount= tokenizer(str, token);
		if(tokenCount != 0) {
			if(commandHandler(token, tokenCount, &lists, &hashs, &bitmaps)) {
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
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount, struct list *lists,
					struct list *hashs, struct list *bitmaps)
{
	list_table *listTable;
	hash_table *hashTable;
	bitmap_table *bitmapTable;
	struct list_elem *temp;
	int i, j;
	bool isExist = false;

	if(strcmp(token[0], "quit") == 0) {
		return -1;
	}

	if(strcmp(token[0], "create") ==0) {
		if(strcmp(token[1], "list") == 0) {
			isExist = false;
			struct list *listPointer;
			for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
				listTable = list_entry(temp, list_table, elem);
				if(strcmp(listTable->list_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}
			if(!isExist) {
				listTable = (list_table*)malloc(sizeof(list_table));
				strcpy(listTable->list_name, token[2]);
				listTable->listPointer = (struct list*)malloc(sizeof(struct list));
				list_init(listTable->listPointer);
				list_push_back(lists, &(listTable->elem));
			}

		} else if(strcmp(token[1], "hashtable" == 0)) {
			isExist = false;
			for(temp = list_begin(hashs); temp != list_end(hashs); temp = list_next(temp)) {
				hashTable = list_entry(temp, hash_table, elem);
				if(strcmp(hashTable->hash_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}
			if(!isExist) {
				hashTable = (hash_table*)malloc(sizeof(hash_table));
				strcpy(hashTable->hash_name, token[2]);
				hashTable->hashPointer = (struct hash*)malloc(sizeof(struct hash));
				hash_init(hashTable->hashPointer, _hash_hash_func, _hash_less_func, NULL);
				list_push_back(hashs, &(hashTable->elem));
			}
		} else if(strcmp(token[1], "bitmap" == 0)) {
			isExist = false;
			size_t bit_cnt;
			for(temp = list_begin(bitmaps); temp != list_end(bitmaps); temp = list_next(temp)) {
				bitmapTable = list_entry(temp, bitmap_table, elem);
				if(strcmp(bitmapTable->bitmap_name, token[2]) == 0) {
					isExist = true;
					break;
				}
			}
			if(!isExist) {
				bitmapTable = (bitmap_table*)malloc(sizeof(bitmap_table));
				strcpy(bitmapTable->bitmap_name, token[2]);
				bit_cnt = (size_t)atoi(token[3]);
				bitmapTable->bitmapPointer = bitmap_create(bit_cnt);
				list_push_back(bitmaps, &(bitmapTable->elem));
			}

		}
	} else if (strcmp(token[0], "delete" == 0)) {
		bool isList = false;
		bool isHash = false;
		bool isBitmap = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isList= true;
				break;
			}
		}

		if(!isList) {
			for(temp = list_begin(hashs); temp != list_end(hashs); temp = list_next(temp)) {
				hashTable = list_entry(temp, hash_table, elem);
				if(strcmp(hashTable->hash_name, token[1]) == 0) {
					isHash= true;
					break;
				}
			}
		} else if(!isList && !isHash) {
			for(temp = list_begin(bitmaps); temp != list_end(bitmaps); temp = list_next(temp)) {
				bitmapTable = list_entry(temp, bitmap_table, elem);
				if(strcmp(bitmapTable->bitmap_name, token[1]) == 0) {
					isBitmap= true;
					break;
				}
			}
		}

		if(isList) {
			for(temp = list_begin(listTable->listPointer); temp != list_end(listTable->listPointer);) {
				list_node* node = list_entry(temp, list_node, elem);
				temp = list_remove(&(node->elem));
				free(node);
			}
			list_remove(&(listTable->elem));
			free(listTable);
		} else if(isHash) {
			hash_destroy(hashTable->hashPointer, _destructor);
			list_remove(&(hashTable->elem));
			free(hashTable);
		} else if(isBitmap) {
			bitmap_destroy(bitmapTable->bitmapPointer);
			list_remove(&(bitmapTable->elem));
			free(bitmapTable);
		}

	} else if (strcmp(token[0], "dumpdata" == 0)) {
		bool isList = false;
		bool isHash = false;
		bool isBitmap = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isList= true;
				break;
			}
		}

		if(!isList) {
			for(temp = list_begin(hashs); temp != list_end(hashs); temp = list_next(temp)) {
				hashTable = list_entry(temp, hash_table, elem);
				if(strcmp(hashTable->hash_name, token[1]) == 0) {
					isHash= true;
					break;
				}
			}
		} else if(!isList && !isHash) {
			for(temp = list_begin(bitmaps); temp != list_end(bitmaps); temp = list_next(temp)) {
				bitmapTable = list_entry(temp, bitmap_table, elem);
				if(strcmp(bitmapTable->bitmap_name, token[1]) == 0) {
					isBitmap= true;
					break;
				}
			}
		}
		if(isList) {
			for(temp=list_begin(listTable->listPointer); temp != list_end(listTable->listPointer); temp = list_next(temp)) {
				list_node* node = list_entry(temp, list_node, elem);
				printf("%d ", node->data);
			}
			if(list_size(listTable->listPointer) != 0) printf("\n");
		} else if (isHash) {
			struct hash_iterator iter;
			hash_first(&iter, hashTable->hashPointer);
			while(hash_next(&iter)) {
				hash_node *hashTemp = hash_entry(hash_cur(&iter), hash_node, elem);
				printf("%d ", hashTemp->data);
			}
			if(!hash_empty(hashTable->hashPointer)) printf("\n");
		} else if (isBitmap) {
			size_t index;
			for(index = 0; index < bitmap_size(bitmapTable->bitmapPointer); index++) {
				printf("%d ", bitmap_test(bitmapTable->bitmapPointer, index));
			}
			printf("\n");			
		}

	// list function
	} else if (strcmp(token[0], "list_insert" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			int i;
			list_node *node = (list_node*)malloc(sizeof(list_node));
			node->data = atoi(token[3]);
			temp = list_begin(listTable->listPointer);
			for(i=0; i<atoi(token[2]); i++) {
				temp = list_next(temp);
			}
			list_insert(temp, &(node->elem));
		}				


	} else if (strcmp(token[0], "list_splice" == 0)) {
		isExist= false;
		struct list_elem *before;
		struct list_elem *first;
		struct list_elem *last;
		int n;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			n=atoi(token[2]);
			before = list_begin(listTable->listPointer);
			for(i=0; i<n; i++) {
				before = list_next(before); 
			}
		}

		isExist = false;

		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[3]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			n=atoi(token[4]);
			first = list_begin(listTable->listPointer);
			for(i=0; i<n; i++) {
				fisrt = list_next(first);
			}
			n=atoi(token[5]);
			last = list_begin(listTable->listPointer);
			for(i=0; i<n; i++) {
				last = list_next(last);
			}
		}

		list_splice(before, start, last);

	} else if (strcmp(token[0], "list_push_front" == 0)) {
		isExist = false;
		int n;
		list_node *node;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			n= atoi(token[2];
			node = (list_node*)malloc(sizeof(list_node));
			node->data = n;
			temp = list_begin(listTable->listPointer);
			list_insert(temp, &(node->elem));
		}

	} else if (strcmp(token[0], "list_push_back" == 0)) {
		isExist = false;
		int n;
		list_node *node;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			n= atoi(token[2];
			node = (list_node*)malloc(sizeof(list_node));
			node->data = n;
			temp = list_end(listTable->listPointer);
			list_insert(temp, &(node->elem));
		}
	} else if (strcmp(token[0], "list_remove" == 0)) {
		isExist = false;
		int i, n;
		struct list_elem *temp_node;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist && !list_empty(listTable->listPointer)) {
			n = atoi(token[2]);
			temp_node = list_begin(listTable->listPointer);
			for(i=0; i<n; i++) {
				temp_node = list_next(temp_node);
			}
			list_remove(temp_node);
		}		
	} else if (strcmp(token[0], "list_pop_front" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			list_pop_front(listTable->listPointer);	
		}		
	} else if (strcmp(token[0], "list_pop_back" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			list_pop_back(listTable->listPointer);	
		}
	} else if (strcmp(token[0], "list_front" == 0)) {
		
	} else if (strcmp(token[0], "list_back" == 0)) {

	} else if (strcmp(token[0], "list_size" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
		if(isExist) {
			printf("%d\n", list_size(listTable->listPointer));
		}

			
	} else if (strcmp(token[0], "list_empty" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			if(list_empty(listTable->listPointer)) {
				printf("true\n");
			} else {
				printf("false\n");
			}
		}

		
	} else if (strcmp(token[0], "list_reverse" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			list_reverse(listTable->listPointer);	
		}
	} else if (strcmp(token[0], "list_sort" == 0)) {

	} else if (strcmp(token[0], "list_insert_ordered" == 0)) {
		isExist = false;
		int n;
		list_node *node;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
		if(isExist) {
			n = atoi(token[2]);
			node = (list_node*)malloc(sizeof(list_node));
			node->data = n;
			list_insert_ordered(listTable->listPointer, &(node->elem), _list_less_func, NULL);
		}
		
	} else if (strcmp(token[0], "list_unique" == 0)) {
		isExist = false;
		int n;
		struct list *temp_list;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			if(token[2] != 0) {
				for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
					temp_list = list_entry(temp, list_table, elem);
					if(strcmp(temp_list->list_name, token[2]) == 0) {
						list_unique(listTable->listPointer, temp_list->listPointer, _list_less_func, NULL);
					}
				}
			} else {
				list_unique(listTable->listPointer, NULL, _list_less_func, NULL);
			}
		}
		
	} else if (strcmp(token[0], "list_max" == 0)) {
		isExist = false;
		list_node *node;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
		if(isExist) {
			temp = list_max(listTable->listPointer, _list_less_func, NULL);
			node = list_entry(temp, list_node, elem);
			printf("%d\n", node->data);

		}	
	} else if (strcmp(token[0], "list_min" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
		if(isExist) {
			temp = list_min(listTable->listPointer, _list_less_func, NULL);
			node = list_entry(temp, list_node, elem);
			printf("%d\n", node->data);
		}	


	//my function
	} else if (strcmp(token[0], "list_swap" == 0)) {
		isExist = false;
		int from, to;
		struct list_elem *a;
		struct list_elem *b;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}

		if(isExist) {
			from = atoi(token[2]);
			to = atoi(token[3]);
			a = list_begin(listTable->listPointer);
			b = list_begin(listTable->listPointer);
			for(i=0; i<from; i++) {
				a = list_next(a);
			}
			for(i=0; i<to; i++) {
				b = list_next(b);
			}
			list_swap(a, b);
		}

		
	} else if (strcmp(token[0], "list_shuffle" == 0)) {
		isExist = false;
		for(temp = list_begin(lists); temp != list_end(lists); temp = list_next(temp)) {
			listTable = list_entry(temp, list_table, elem);
			if(strcmp(listTable->list_name, token[1]) == 0) {
				isExist= true;
				break;
			}
		}
		if(isExist) {
			list_shuffle(listTable->listPointer);
		}


	//hashtable function
	} else if (strcmp(token[0], "hash_insert" == 0)) {
		isExist= false;
		int n;
		hash_node *node;
		for(temp = list_begin(hashs); temp != list_end(hashs); temp = list_next(temp)) {
			hashTable = list_entry(temp, hash_table, elem);
			if(strcmp(token[1], hashTable->hash_name) ==0) {
				isExist = true;
				break;
			}
		}

		if(isExist) {
			n = atoi(token[2]);
			node = (hash_node*)malloc(sizeof(hash_node));
			node->data = n;
			hash_insert(hashTable->hashPointer, &(node->elem));
		}
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

unsigned hash_int_2(int i)
{
	const unsigned char *buf = (const unsigned char*) &i;
	size_t size = sizeof(i);
	unsigned hash;

	ASSERT (buf != NULL);

	hash= FNV_32_BASIS;
	while(size-- > 0) {
		hash = (hash * FNV_32_PRIME) ^ *(buf+2);
		buf += size;
	}

	return hash;
}
