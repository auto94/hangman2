/*
	PROGRAM: HANGMAN
	VERSION 1.0

	CURRENT VERSION: WORD TAKEN BY RANDOM FROM DATABASE

	FUTURE DEVELOPMENT: Making it so that you can't get multiple errors by repeatingly guessing the same wrong letter
	(basicly keeping a log of previous mistakes, and comparing them to the current letter in a for loop)
*/

#pragma warning(disable:4996)	//disables fopen error

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	//used for srand(time(NULL))
#include <ctype.h>	//used for tolower()

#define MAX_ERROR 6


int main(void) {
	srand(time(NULL));	//initiate random seed (time based) ONLY CALL ONCE
	int rand_word_select = 3 + (rand() % 10);	//random number between 0 and 100, decided amount of spaces before word selected

	char word[20];	//word to be guessed, input by user 
	int correct_letters[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//array of 0/1s which tells us if a letter in word has been correctly guessed so far
	int correct_sum = 0;	//if size of word = number of correct_letters (AKA correct_sum), tells us if every letter has been guessed **SHORTCUT**
	int size = 0;	//stores length of input word (by calculating difference in position of two consecutive spaces
	int error_count = 0;	//number of incorrect guesses, has to be below a certain number or you've failed
	char temp_letter;	//stores the single letter which user input (and has to be checked if it is in word string)
	int temp_letter_included = 1;	//checks if temp_letter was found in word. Prevents error_count from going up for every incorrect letter placement
	int place_in_word;	//for printing out the place of a correctly chosen letter in the original word. Essentially i+1
	
	FILE *listofwords;
	listofwords = fopen("words.txt", "r");	//opens words.txt, a file filled with 100 words, separated by spaces
	char string_from_file[1000]; //size large enough for 100 random words
	int random_counter = 0;	//counts the amount of spaces we've gone through, for "random" selection
	int previous_space = 0;	//used for finding length and exact place in string of random word, remembers space before the one selected
	int current_space = 0;	//used for finding length and exact place in string of random word, remembers place of space after selected word
	word[0] = '0'; //CHEAT for remembering previous_space and not also overwriting it when we find the random word

	if (listofwords == NULL) {
		printf("\n ERROR!!! File is empty or missing!");
		exit(-1);
	}
	while (fgets(string_from_file, 1000, listofwords) != 0) {
		for (int i = 0; i < 1000; i++) {
			if (string_from_file[i] == ' ') {
				random_counter++;
				current_space = i;

				if (random_counter + 1 == rand_word_select) {
					size = current_space - previous_space - 1;	//amount of letters between the two consecutive spaces (aka length of word selected)

					for (int j = 0; j < size; j++) {
						word[j] = string_from_file[previous_space + j + 1];
					}
					word[size] = '\0'; //doda znak za konec za zadnim mestom ki ga zaseda beseda
					
				}
				if (word[0] == '0') {
					previous_space = i;
				}
			}
		}
		fclose(listofwords);
	}

	printf("\n Good luck! Here is your randomly selected word: \n");
	//zacetni izpis podcrtajev namesto crk
	for (int i = 0; i < size; i++) {
		printf(" _ ");
		correct_letters[i] = 0;
	}


	printf("\n Enter the letters, one by one: ");
	//sprejemanje crk dokler ni prevec errorjev ali ni dovolj pravilnih crk
	while (error_count < MAX_ERROR && (correct_sum < size)) {
		
		temp_letter = getchar();
		temp_letter_included = 0;
		temp_letter = tolower(temp_letter);

		//enter ignoriramo
		if (temp_letter != '\n') {

			//preveri da je input crka in ne kak drug znak
			if ((temp_letter >= 'a' && temp_letter <= 'z') || (temp_letter >= 'A' && temp_letter <= 'Z')) {
				//gre skozi vse crke v izbrani besedi
				for (int i = 0; i < size; i++) {
					//gleda ce se ujemajo s trenutno dano crko
					if (temp_letter == word[i]) {

						//ce se ujemajo (prvic) to zapise v correct_letters (mesto), drugace vrne da je ta crka ze bila izbrana
						if (correct_letters[i] == 0) {
							correct_letters[i] = 1;
							correct_sum++;
						}
						else {
							printf("\n You've already guessed this letter, you fuck.");
						}

						//izpise mesto crke v besedi
						temp_letter_included = 1;
						place_in_word = i + 1;

						printf("\n The letter is in the word, specifically in place: %d", place_in_word);
					}
				}

				//ce crke ni v besedi poveca stevilo napak
				if (temp_letter_included == 0) {
					error_count++;
					printf("\n The letter %c is not in the word.", temp_letter);
				}

				printf("\n Current errors: %d", error_count);
				printf("\n");
				//izpise podcrtaje oziroma ze pravilno izbrane crke
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
				printf("\n You idiot, you entered something that isn't a letter. Learn to read!");
			}
		}
		else {
			printf("\n Enter your next guess: ");
		}

	}

	//pogoj za uspesen zakljucek
	if (correct_sum == size) {
		printf("\n You've successfully guessed the word with only %d errors! Congratulations!\n", error_count);
	}
	//pogoj za preveliko stevilo napak/narobe izbranih crk
	else if (error_count >= MAX_ERROR) {
		printf("\n You've made too many mistakes! Try again from the start.\n");
	}

	//na koncu vedno izpise celo besedo
	printf("\n Word is: %s\n", word);

	return 0;
}