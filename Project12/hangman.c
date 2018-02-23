/*
	PROGRAM: HANGMAN
	VERSION 1.0
	CURRENTLY: WORD INPUT BY USER, LETTERS INPUT BY USER

	FUTURE VERSION: WORD TAKEN BY RANDOM FROM DATABASE
*/

//disables fopen error
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
	srand(time(NULL));	//initiate random seed (time based) ONLY CALL ONCE
	int rand_word_select = rand() % 100;	//random number between 0 and 100, decided amount of spaces before word selected

	char word[20];	//word to be guessed, input by user 
	int correct_letters[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//array of 0/1s which tells us if a letter in word has been correctly guessed so far
	int correct_sum = 0;	//if size of word = number of correct_letters (AKA correct_sum), tells us if every letter has been guessed **SHORTCUT**
	int size = 0;	//stores length of input word (using strlen)
	int error_count = 0;	//number of incorrect guesses, has to be below a certain number or you've failed
	int word_complete = 0;	//flag for complete word, simlar to correct_sum
	char temp_letter;	//stores the single letter which user input (and has to be checked if it is in word string)
	int temp_letter_included = 1;	//checks if temp_letter was found in word. Prevents error_count from going up for every incorrect letter placement
	int place_in_word;	//for printing out the place of a correctly chosen letter in the original word. Essentially i+1

	//ADDING FOR RANDOM WORD SELECT FROM LOADED FILE:
	//srand(time(NULL));	//ONLY CALL ONCE
		//random number between 0 and 48, for searching txt file
	//printf("\n Random word select is: %d", rand_word_select);
	
	FILE *listofwords;
	listofwords = fopen("words.txt", "r");	//opens words.txt, a file filled with 100 words, separated by spaces
	char word_from_file[1000]; //size large enough for 100 random words
	int random_counter = 0;	//counts the amount of spaces we've gone through, for "random" selection
	int previous_i = 0;	//used for finding length and exact place in string of random word, remembers space before the one selected
	int current_i = 0;	//used for finding length and exact place in string of random word, remembers place of space after selected word
	int difference_i = 0; //used for finding length and exact place in string of random word, remembers length of selected word
	word[0] = '0'; //CHEAT for remembering previous_i and not also overwriting it when we find the random word

	if (listofwords == NULL) {
		printf("\n ERROR!!! File is empty or missing!");
		exit(-1);
	}
	while (fgets(word_from_file, 1000, listofwords) != 0) {
		for (int i = 0; i < 1000; i++) {
			if (word_from_file[i] == ' ') {
				random_counter++;
				current_i = i;

				if (random_counter + 1 == rand_word_select) {
					difference_i = current_i - previous_i - 1;	//amount of letters between the two consecutive spaces (aka length of word selected)

					for (int j = 0; j < difference_i; j++) {
						word[j] = word_from_file[previous_i + j + 1];
					}
					word[difference_i] = '\0';
					
				}
				if (word[0] == '0') {
					previous_i = i;
				}
			}
		}
		fclose(listofwords);
	}

	
	//size = strlen(word); //no longer needs - 1 because there is no enter
	size = difference_i;

	printf("\n Good luck! Here is your randomly selected word: \n");
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

					if (correct_letters[i] == 0) {
						correct_letters[i] = 1;
						correct_sum++;
					}
					else {
						printf("\n You've already guessed this letter, you fuck.");
					}

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

	//printf("\n Size: %d", size);
	printf("\n Word is: %s\n", word);

	return 0;
}