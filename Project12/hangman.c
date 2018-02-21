/*
	PROGRAM: HANGAM
	VERSION 1.0
	CURRENTLY: WORD INPUT BY USER, LETTERS INPUT BY USER
	
	FUTURE VERSION: WORD TAKEN BY RANDOM FROM DATABASE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char word[20];
	int size = 0;
	int error_count = 0;


	printf("\nPlease input the word: ");
	fgets(word, 20, stdin);

	size = strlen(word) - 1;


	for (int i = 0; i < size; i++) {
		printf("_\t");
	}

	printf("\nSize: %d", size);
	printf("\nWord is: %s", word);


	return 0;
}