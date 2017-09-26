#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

#define MAX_STR_SIZE 128
#define MAX_TOKEN_NAME 20
#define MAX_TOKEN_SIZE 5

//command process
int tokenizer(char* str, char token[][MAX_STR_SIZE]);
int commandHandler(char token[][MAX_STR_SIZE], int tokenCount);


//List
void list_swap(struct list_elem *a, struct list_elem *b);
void list_shuffle(struct list *list);


//Hashtable
unsigned hash_int_2(int i);


//Bitmap
struct bitmap *bitmap_expand(struct bitmap *bitmap, int size);
