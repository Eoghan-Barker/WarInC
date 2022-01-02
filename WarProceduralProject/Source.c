#include <stdio.h>
#include <stdlib.h>

FILE *fptr;

void createDeck(int *newDeck);
void shuffle(int *shuffledDeck);
void deal(int *shuffledDeck, int *p1, int* p2, int* p3, int* p4);
void chooseCard(int *playerHand, int player, int *card);
int playRound(int rounds, int* p1, int* p2, int* p3, int* p4, int *playerPoints, int roundPoints);
int displayIntro();
void gameComplete(int *playerPoints);
void gameStatus(int* playerPoints, int rounds);
void saveGame(int* p1Hand, int* p2Hand, int* p3Hand, int* p4Hand, int round, int* playerPoints);
int loadGame(int* p1Hand, int* p2Hand, int* p3Hand, int* p4Hand, int round, int* playerPoints);
int openFile(int mode);
void closeFile();


void main() {
	//Variables and Arrays
	int deckOfCards[52];
	int player1Hand[13];
	int player2Hand[13];
	int player3Hand[13];
	int player4Hand[13];
	int playerPoints[4] = {0,0,0,0};

	int rounds = 1, roundPoints = 0, continueCheck;
	

	
	//Game setup
	//if displayIntro returns true the the game is loaded from a file
	//if it returns false then a new game is created
	if (displayIntro()) {
		rounds = loadGame(player1Hand, player2Hand, player3Hand, player4Hand, rounds, playerPoints, roundPoints);
		gameStatus(playerPoints, rounds);
	}
	else {
		createDeck(deckOfCards);
		shuffle(deckOfCards);
		deal(deckOfCards, player1Hand, player2Hand, player3Hand, player4Hand);
	}

	

	//Playing 13 rounds
	do {
		
		//playRound returns the roundpoints, will be a 0 unless All cards tied so it can be carried into next round
		roundPoints = playRound(rounds, player1Hand, player2Hand, player3Hand, player4Hand, playerPoints, roundPoints);

		//Ask user to continue, ouput game status, exit, exit and save
		//while loop to bring user back to this menu when they choose output game status
		continueCheck = 2;
		while (continueCheck == 2)
		{
			printf("1. Continue\n");
			printf("2. Output game status\n");
			printf("3. Exit\n");
			printf("4. Exit and save\n");
			printf("Enter option 1-4: ");
			scanf("%d", &continueCheck);

			switch (continueCheck)
			{
			case 1: 
				break;
			case 2:
				gameStatus(playerPoints, rounds);
				break;
			case 3:
				exit(0);
				break;
			case 4:
				rounds++;
				saveGame(player1Hand, player2Hand, player3Hand, player4Hand, rounds, playerPoints, roundPoints);
				exit(0);
				break;
			default:
				break;
			}

		}

		rounds++;
	} while (rounds != -1 && rounds <= 13);

	
	gameComplete(playerPoints);
	
	       
}// end of main

//using pointera to pass and return arrays from/to main
//populate deck of cards array
void createDeck(int *newDeck) {
	int i;
	for (i = 0; i < 52; i++) {
		//check for ace(worth 14) else assign value 2-13
		//also need to check for kings so value is not 0
		if (i == 0 || i == 13 || i == 26 || i == 39) {
			newDeck[i] = 14;
		}
		else if (i == 12 || i == 25 || i == 38 || i == 51) {
			newDeck[i] = 13;
		}
		else {
			newDeck[i] = (i + 1) % 13;
		}
	}
}// end of createDeck function


//shuffle deck of cards array by swapping cards 0-51 with a card at a random index
void shuffle(int *shuffledDeck) {
	int i, j, k;
	srand ( time(NULL) );

	//move through each array index and swap the value of that index with the value of a random index
	for (i = 0; i < 52 - 1; i++)
	{
		//create random number between 0-51
		j = rand() % 52;
		//store value from random index
		k = shuffledDeck[j];
		//swap random index value with current index value
		shuffledDeck[j] = shuffledDeck[i];
		shuffledDeck[i] = k;
	}
}// end of shuffle function

//deal 13 cards to each players hand
void deal(int* shuffledDeck, int* p1, int* p2, int* p3, int* p4) {
	int i;

	//Give the first 13 cards to p1, next 13 to p2 etc.
	for (i = 0; i < 13; i++) {
		p1[i] = shuffledDeck[i];
		p2[i] = shuffledDeck[i + 13];
		p3[i] = shuffledDeck[i + 26];
		p4[i] = shuffledDeck[i + 39];
	}
}// end of deal function

//ask each player to choose which card they want to play
//make sure it hasn't been played already
//store the value for finding winner later
void chooseCard(int* playerHand, int player, int* card) {
	int i, input;

	printf("\nPlayer %d hand: \n", player + 1);
	for (i = 0; i < 13; i++) {
		printf("%d:%d\n", i, playerHand[i]);
	}
	printf("\nChoose a card to play(0-12): ");
	scanf("%d", &input);
	
	//check for valid input and that card hasn't been played
	while (input > 12 || input < 0 ||  playerHand[input] == -1) {
		printf("\nInvalid input or card already played, choose another");
		printf("\nChoose a card to play(0-12): ");
		scanf("%d", &input);
	}

	//store card being played, change value to -1 in deck
	card[player] = playerHand[input];
	playerHand[input] = -1;
	
}// end of chooseCard function

//play a round, ask players to choose a card, calculate the points for that round
int playRound(int rounds, int* p1, int* p2, int* p3, int* p4, int *playerPoints, int roundPoints) {
	int chosenCard[4];
	int i, draw, winner, largest, drawCount, allTie;


	printf("Round %d: \n", rounds);

	//Each player goes individually - print hand, ask for card to play
	//Storing card values in array - player 1 = index 0 player 2 = index 1 etc.

	chooseCard(p1, 0, chosenCard);
	chooseCard(p2, 1, chosenCard);
	chooseCard(p3, 2, chosenCard);
	chooseCard(p4, 3, chosenCard);

	//Calculate points for current round
	for (i = 0; i < 4; i++) {
		roundPoints += chosenCard[i];
	}

	//Find winning card
	//if any 2 cards = the largest they get put to 0 and loop runs again
	//if draw count = 4 then it is a full tie and the points get rolled over to the next round
	drawCount = 0;
	do {
		//find the largest card
		largest = 0;
		for (i = 0; i < 4; i++) {
			if (largest < chosenCard[i]) {
				largest = chosenCard[i];
				//need to do this for checking draws
				chosenCard[i] = 0;
				winner = i;
				draw = 0;
			}
		}

		//check for draws
		for (i = 0; i < 4; i++) {
			if (largest == chosenCard[i]) {
				chosenCard[i] = 0;
				draw = 1;
				drawCount++;
			}
		}
	} while (draw == 1 && drawCount < 4);

	//Add to winners total and reset roundPoints
	//Unless drawCount = 4, then roundPoints carry into next round
	if (drawCount < 4)
	{
		playerPoints[winner] += roundPoints;
		printf("\nPlayer %d wins %d points!\n\n", winner + 1, roundPoints);
		roundPoints = 0;
		
	}
	else
	{
		printf("\nAll Tie! Points will be carried into the next round\n\n");
	}

	return roundPoints;
}

//Prints game rules and ask user if they want to start a new game or load a saved one
//returns 0 if game is new or 1 if game is to be loaded
int displayIntro() {
	int NewOrLoad;
	printf("Welcome to War!\n");
	printf("Each player has 13 cards in their hand\n");
	printf("Choose the highest card to win. If two players choose the same card then the next highest card will win\n");
	printf("If all cards tie another then the points are rolled over to the next round\n");
	printf("Once a card has been played it can't be played again(represented by a -1)\n");
	printf("Whoever has the most points after 13 rounds wins.\n\n\n");

	printf("Enter 0 to start a new game or 1 to load a saved game: ");
	scanf("%d", &NewOrLoad);

	return NewOrLoad;


}// end of displayIntro function

//when all rounds are over
//calculates winning player
void gameComplete(int *playerPoints) {
	int i, highestScore = 0, finalWinner = 0;

	//Calculate Overall winner
	for (i = 0; i < 4; i++) {
		if (highestScore < playerPoints[i]) {
			highestScore = playerPoints[i];
			finalWinner = i;
		}
	}

	//Output winner + player scores
	printf("Game Complete, Player %d wins!\n", finalWinner + 1);
	printf("The Final Scores were:\n");
	gameStatus(playerPoints, 13);
}

//prints current round and points of each player
void gameStatus(int* playerPoints, int rounds) {
	printf("\nRounds played: %d\n", rounds);
	printf("Player 1: %d\n", playerPoints[0]);
	printf("Player 2: %d\n", playerPoints[1]);
	printf("Player 3: %d\n", playerPoints[2]);
	printf("Player 4: %d\n\n\n", playerPoints[3]);
}

//opens file in write mode
//prints each players hand and points to file
//prints rounds played to file
void saveGame(int *p1Hand, int *p2Hand, int* p3Hand, int* p4Hand, int round, int *playerPoints) {
	int openOk, i;

	openOk = openFile(0);
	if (openOk) {
		
		//print player 1-4 hand array to file
		for (i = 0; i < 13; i++)
		{
			fprintf(fptr, "%d\n", p1Hand[i]);
		}
		for (i = 0; i < 13; i++)
		{
			fprintf(fptr, "%d\n", p2Hand[i]);
		}
		for (i = 0; i < 13; i++)
		{
			fprintf(fptr, "%d\n", p3Hand[i]);
		}
		for (i = 0; i < 13; i++)
		{
			fprintf(fptr, "%d\n", p4Hand[i]);
		}

		//print playerPoints array to file
		for (i = 0; i < 4; i++)
		{
			fprintf(fptr, "%d\n", playerPoints[i]);
		}

		//print current round and roundPoints to file
		fprintf(fptr, "%d\n", round);
		
	}

	closeFile();
	
}

//opens file in read mode
//reads players hands and points into arrays
//reads in and returns the current round
int loadGame(int* p1Hand, int* p2Hand, int* p3Hand, int* p4Hand, int round, int* playerPoints) {
	int openOk, i;

	openOk = openFile(1);
	if (openOk == 1) {
		//while (!feof(fptr)) {			//read player 1-4 hand to arrays
			for (i = 0; i < 13; i++)
			{
				fscanf(fptr, "%d\n", &p1Hand[i]);
			}
			for (i = 0; i < 13; i++)
			{
				fscanf(fptr, "%d\n", &p2Hand[i]);
			}
			for (i = 0; i < 13; i++)
			{
				fscanf(fptr, "%d\n", &p3Hand[i]);
			}
			for (i = 0; i < 13; i++)
			{
				fscanf(fptr, "%d\n", &p4Hand[i]);
			}

			//read playerPoints to array 
			for (i = 0; i < 4; i++)
			{
				fscanf(fptr, "%d\n", &playerPoints[i]);
			}

			
			//read current round and roundPoints from file
			fscanf(fptr, "%d\n", &round);						return round;		
	}
	else {
		printf("Error loading Game");
		exit(0);
	}

	closeFile();
}

//if mode is 0 = w mode
//mode 1 = r mode
int openFile(int mode) {
	int result;

	if (mode == 0) {
		fptr = fopen("gameSave.txt", "w");
	}
	else {
		fptr = fopen("gameSave.txt", "r");
	}
	
	if (fptr == NULL)
	{
		printf("Error opening file"); 
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

void closeFile() {
	fclose(fptr);
}