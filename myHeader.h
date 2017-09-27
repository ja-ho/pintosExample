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
	char list_name[MAX_TOKEN_NAME];
	struct list_elem elem;
} list_table;

typedef struct _hash_table {
	struct list_elem elem;
	char hash_name[MAX_TOKEN_NAME];
} hash_table;

typedef struct _bitmap_table {
	struct list_elem elem;
	char bitmap_name[MAX_TOKEN_NAME];
} bitmap_table;

//command process
int tokenizer(char* str, char token[][MAX_STR_SIZE]);
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount);


