#include "myHeader.h"



int main() {
	char str[MAX_STR_SIZE]= {'\0',};
	char token[MAX_TOKEN_SIZE][MAX_STR_SIZE];
	int tokenCount=0;
	
	while(true) {
		fget(str, MAX_STR_SIZE, stdin);
		tokenCount= tokenizer(str, token);
		if(tokenCount != 0) {
			
		}
	}

	return 0;
}
