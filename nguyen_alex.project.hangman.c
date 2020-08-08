#include <stdio.h>
#include <string.h>
#include <time.h>

#define BOARD_WIDTH 33
#define MAX_GUESSES 6

void printTitle();
void printLettersTitle();
void printGuessLettersTitle();
void drawHangman(int);
void printAvailableLetters(char*, char*);
char* getWord(char*);
char* createBlanks(char*, char*, int);
int guessWord(char*, int, char*, char);
int refreshAvailableLetters(char*, char*, char);
void printGame(char* title, int printTop, int printBottom, int printingCharacters);
void delay(int);

int main() {
	
	char lettersRow1[BOARD_WIDTH] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', '\0'};
	char lettersRow2[BOARD_WIDTH] = {'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W','X', 'Y', 'Z', '\0'};
	
	char answerWord[BOARD_WIDTH];
	getWord(answerWord);	// User enters word to be guessed
	
	int answerLength = strlen(answerWord);
	
	char guessedWord[BOARD_WIDTH] = { '\0' };
	
	createBlanks(guessedWord, answerWord, answerLength);
	char guessedLetter = '\0';
	int won = 0;
	int numGuesses = 0;
	int letterIsUsed = 0;

	do
	{
		system("@cls||clear");

		printTitle();
		drawHangman(numGuesses);
		printLettersTitle();
		printAvailableLetters(lettersRow1, lettersRow2);
		printGuessLettersTitle();
		printGame(guessedWord, 0, 1, 1);
		
		printf("Enter a letter: ");
		scanf_s(" %c", &guessedLetter, 1);
		won = guessWord(answerWord, answerLength, guessedWord, guessedLetter);
		letterIsUsed = refreshAvailableLetters(lettersRow1, lettersRow2, guessedLetter);
		if (won == 0 && letterIsUsed == 1)	// If incorrect guess and letter was not already used -> increase number of guesses used
			numGuesses++;
		
	} while ((won != 2 && numGuesses < 6));

	system("cls");
	printTitle();
	drawHangman(numGuesses);
	printLettersTitle();
	printAvailableLetters(lettersRow1, lettersRow2);
	printGuessLettersTitle();
	printGame(guessedWord, 0, 1, 1);
	if (won == 2)
		printf("Correct! Game Over!");
	else
		printf("Incorrect! Game Over!\nThe word was: %s", answerWord);
	return 0;
}

void printTitle() {
	char title[BOARD_WIDTH] = "Hangman";

	printGame(title, 1, 1, 0);
}

void printLettersTitle() {
	char lettersTitle[BOARD_WIDTH] = "Available Letters";

	printGame(lettersTitle, 1, 1, 0);
}

void printGuessLettersTitle() {
	char guessLettersTitle[BOARD_WIDTH] = "Guess the Word";

	printGame(guessLettersTitle, 0, 1, 0);
}

void drawHangman(int numGuesses) {

	char drawingPipe[BOARD_WIDTH] = "|";	// Noose and body
	char drawingEmpty[BOARD_WIDTH] = "";	// Empty
	char drawingHead[BOARD_WIDTH] = "O";	// Head
	char drawingLeftArm[BOARD_WIDTH] = "/|";	// Left arm and body
	char drawingRightArm[BOARD_WIDTH] = "/|\\";	// Full upper body (left arm, body, right arm)
	char drawingLeftLeg[BOARD_WIDTH] = "/ ";	// Left Leg
	char drawingRightLeg[BOARD_WIDTH] = "/ \\";	// Full lower body (left leg, right leg)

	printGame(drawingPipe, 0, 0, 0);	// Drawing noose
	printGame(drawingPipe, 0, 0, 0);

	switch (numGuesses)
	{
		case 1:	// Draw head
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			break;
		case 2:	// Draw torso
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingPipe, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			break;
		case 3:	// Draw left arm
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingLeftArm, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			break;
		case 4:	// Draw right arm (full upper body)
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingRightArm, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			break;
		case 5: // Draw left leg
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingRightArm, 0, 0, 0);
			printGame(drawingLeftLeg, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			break;
		case 6: // Draw right leg (full lower body)
			printGame(drawingHead, 0, 0, 0);
			printGame(drawingRightArm, 0, 0, 0);
			printGame(drawingRightLeg, 0, 0, 0);

			printGame(drawingEmpty, 0, 0, 0);
			break;
		default:
			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			printGame(drawingEmpty, 0, 0, 0);
			break;
	}
}

void printAvailableLetters(char* letters1, char* letters2) {
	printGame(letters1, 0, 0, 1);
	printGame(letters2, 0, 1, 1);
}

char* getWord(char* wordToGuess) {

	int length = 0;
	do
	{
		printf("Enter a word between 0 - 16 characters: ");
		scanf_s("%[^\n]%*c", wordToGuess, BOARD_WIDTH);
		length = strlen(wordToGuess);
		if (length > 16) {
			printf("Word is too long.\n");
			delay(1);

			system("@cls||clear");
		}
	} while (length > 16);

	return wordToGuess;
}

char* createBlanks(char* guessWord, char* answerWord, int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (answerWord[i] != ' ')
			guessWord[i] = '_';
		else
			guessWord[i] = ' ';
	}
	guessWord[i] = '\0';
	return guessWord;
}

int guessWord(char* word, int wordLength, char* guessWord, char guessLetter) {
	int letterFound = 0;

	if (guessLetter == '\0')
		return 0;

	for (int i = 0; i < wordLength; i++)
	{
		if (tolower(guessLetter) == tolower(word[i])) {
			letterFound = 1;
			guessWord[i] = tolower(guessLetter);
		}
	}
	char tempAnswer[17] = { '\0' };
	char tempGuess[17] = { '\0' };

	for (int i = 0, j = 0; i < wordLength; i++) {
		if (word[i] != ' ') {
			tempAnswer[j] = tolower(word[i]);
			j++;
		}
	}

	for (int i = 0, j = 0; i < wordLength; i++) {
		if (guessWord[i] != ' ') {
			tempGuess[j] = tolower(guessWord[i]);
			j++;
		}
	}

	if (strcmp(tempAnswer, tempGuess) == 0)
		return 2;	// Word was guessed correctly -> Game won
	else
		return letterFound; // Return 0 if incorrect letter guess, 1 if correct letter guess
}

/**
	Refreshes list of available letters after guess
	@param letters1 first list of available letters
	@param letters2 second list of available letters
	@param guessedLetter character guessed by user
*/
int refreshAvailableLetters(char* letters1, char* letters2, char guessedLetter) {

	int letterNotUsed = 0;
	if (isdigit(guessedLetter)) {
		printf("Not a valid input. Enter a letter.");
		return letterNotUsed;
	}
	if (toupper(guessedLetter) <= 'M') {
		for (int i = 0; i < strlen(letters1); i++) {
			if (toupper(guessedLetter) == letters1[i])
			{
				letterNotUsed = 1;
				letters1[i] = ' ';
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < strlen(letters2); i++) {
			if (toupper(guessedLetter) == letters2[i])
			{
				letterNotUsed = 1;
				letters2[i] = ' ';
				break;
			}
		}
	}
	if (!letterNotUsed)
	{
		printf("Letter %c has already been used", guessedLetter);
		delay(1);
	}
	return letterNotUsed; // Return 0 if letter already used, return 1 if letter not already used
}

/**
	Draws borders of game
	@param title title of game
	@param printTop boolean to check if printing top border
	@param printBottom boolean to check if printing bottom border
*/
void printGame(char* title, int printTop, int printBottom, int printingCharacters) {
	char temp[BOARD_WIDTH];
	
	for (int i = 0; i < BOARD_WIDTH; i++) {
		temp[i] = title[i];
	}

	if (printingCharacters) {
		for (unsigned int i = 0; i < strlen(temp); i++) {
			title[i * 2] = temp[i];
		}
		for (int i = 1; i < BOARD_WIDTH; i += 2) {
			title[i] = ' ';
		}
	}

	
	if (printTop)
		printf("%s\n", "---------------------------------"); // 33 characters long
	
	printf("%c", '|');
	for (int i = strlen(title), start = 1; i < BOARD_WIDTH - 1; i++)
	{
		if (start)
		{
			int k = strlen(title);
			title[k] = ' ';
			title[k + 1] = '\0';
			for (int j = k - 1; j >= 0; j--)
			{
				title[k--] = title[j];
			}
			title[k] = ' ';
			start = 0;
		}
		else
		{
			start = 1;
		}
	}

	
	int l = strlen(title);
	while (l < BOARD_WIDTH - 2)
	{
		title[l] = ' ';
		l++;
	}
	title[l] = '\0';

	
	printf("%s", title);

	printf("%c\n", '|');

	if (printBottom)
		printf("%s\n", "---------------------------------"); // 33 characters long

	if (!printingCharacters) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			title[i] = temp[i];
		}
	}
	else
	{
		int length = strlen(title);
		for (int i = 0; i < BOARD_WIDTH; i++)
			title[i] = '\0';
		for(int i = 0; i < length; i++)
			title[i] = temp[i];
	}
	
}

/**
	Delays the system by a set number of seconds
	@param numSeconds number of seconds to delay system
*/
void delay(int numSeconds) {
	int millisec = 1000 * numSeconds;
	clock_t timeStart = clock();

	while (clock() < timeStart + millisec)
		;
}

/**
	Prints out notes and instructions for hangman game and the program specifically
*/
void printInstructions() {
	printf("Welcome to Hangman!\n");
	printf("How to play:\n First, enter a word to be guessed that is between 0 -16 characters long. The word can include spaces but must still be"
		"less than 16 characters long (spaces are counted as a character). Next, enter a character or multiple characters that you think are in the word" 
		"and try to guess what the word is! You are given 6 attempts to guess the word, after which the game will be over, and you will be notified if you were correct or not."
	"If you are incorrect and lose the game, the word will be displayed for you.");
	printf("NOTES:\n");
	printf("For aesthetic purposes only, there is a command in the program that clears the screen but only runs on Windows. For Linux and Mac users, the line needs to be replaced with the commented line directly below it.");
}