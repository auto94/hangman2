/*
	PROGRAM: HANGMAN
	VERSION 1.0
	CURRENTLY: WORD INPUT BY USER, LETTERS INPUT BY USER

	FUTURE VERSION: WORD TAKEN BY RANDOM FROM DATABASE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char word[20];	//word to be guessed, input by user
	int correct_letters[20];	//array of 0/1s which tells us if a letter in word has been correctly guessed so far
	int correct_sum = 0;	//if size of word = number of correct_letters (AKA correct_sum), tells us if every letter has been guessed **SHORTCUT**
	int size = 0;	//stores length of input word (using strlen)
	int error_count = 0;	//number of incorrect guesses, has to be below a certain number or you've failed
	int word_complete = 0;	//flag for complete word, simlar to correct_sum
	char temp_letter;	//stores the single letter which user input (and has to be checked if it is in word string)
	int temp_letter_included = 1;	//checks if temp_letter was found in word. Prevents error_count from going up for every incorrect letter placement
	int place_in_word;	//for printing out the place of a correctly chosen letter in the original word. Essentially i+1


	printf("\n Please input the word: ");
	fgets(word, 20, stdin);

	size = strlen(word) - 1;


	//zacetni izpis podcrtajev namesto crk
	for (int i = 0; i < size; i++) {
		printf(" _ ");
		correct_letters[i] = 0;
	}


	printf("\n Enter the letters, one by one: ");
	//sprejemanje crk dokler ni prevec errorjev ali ni dovolj pravilnih crk
	while (error_count < 5 && (correct_sum < size)) {
		
		temp_letter = getchar();
		temp_letter_included = 0;

		if (temp_letter != '\n') {

			

			for (int i = 0; i < size; i++) {
				if (temp_letter == word[i]) {
					correct_letters[i] = 1;
					correct_sum++;
					temp_letter_included = 1;
					place_in_word = i + 1;

					printf("\n The letter is in the word, specifically in place: %d", place_in_word);
				}
			}

			if (temp_letter_included == 0) {
				error_count++;
				printf("\n The letter %c is not in the word.", temp_letter);
			}

			printf("\n Current errors: %d", error_count);
			printf("\n");
			for (int i = 0; i < size; i++) {
				if (correct_letters[i] == 1) {
					printf(" %c ", word[i]);
				}
				else {
					printf(" _ ");
				}
			}
		}
		else {
			printf("\n Enter your next guess: ");
		}

	}

	if (correct_sum == size) {
		word_complete = 1;
		printf("\n You've successfully guessed the word! Congratulations!\n");
	}
	else if (error_count >= 5) {
		printf("\n You've made too many mistakes! Try again from the start.\n");
	}

	printf("\n Size: %d", size);
	printf("\n Word is: %s", word);

	return 0;
}