#include <stdio.h>
#include <stdlib.h>


void shuffle(int *shuffledDeck);
void deal(int *shuffledDeck, int *p1, int* p2, int* p3, int* p4);
void chooseCard(int *playerHand, int player, int *card);
void displayIntro();


void main() {
	//Variables and Arrays
	int deckOfCards[52];
	int player1Hand[13];
	int player2Hand[13];
	int player3Hand[13];
	int player4Hand[13];

	int chosenCard[4];
	int playerPoints[4] = {0,0,0,0};

	int i, rounds = 1, roundPoints = 0, draw, winner, largest, drawCount, finalWinner = 0, highestScore = 0;
	

	

	//populate deck of cards array
	for (i = 0; i < 52; i++) {
		//check for ace(worth 14) else assign value 2-13
		//also need to check for kings so value is not 0
		if (i == 0 || i == 13 || i == 26 || i == 39){
			deckOfCards[i] = 14;
		}
		else if (i == 12 || i == 25 || i == 38 || i == 51) {
			deckOfCards[i] = 13;
		}
		else {
			deckOfCards[i] = (i+1) % 13;
		}
	}

	displayIntro();


	//Shuffle deck
	shuffle(deckOfCards);

	//Deal cards
	deal(deckOfCards, player1Hand, player2Hand, player3Hand, player4Hand);

	//Playing 13 rounds
	do {
		printf("Round %d: \n", rounds);

		//Each player goes individually - print hand, ask for card to play
		//Storing card values in array - player 1 = index 0 player 2 = index 1 etc.
		
		chooseCard(player1Hand, 0, chosenCard);
		chooseCard(player2Hand, 1, chosenCard);
		chooseCard(player3Hand, 2, chosenCard);
		chooseCard(player4Hand, 3, chosenCard);

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
			printf("Player %d wins %d points!\n\n", winner + 1, roundPoints);
			roundPoints = 0;
		}
		else
		{
			printf("All Tie! Points will be carried into the next round\n\n");
		}

		rounds++;
	} while (rounds != -1 && rounds <= 13);

	//Calculate Overall winner
	for (i = 0; i < 4; i++) {
		if (highestScore < playerPoints[i]) {
			highestScore = playerPoints[i];
			finalWinner = i;
		}
	}
			
	//Final Output, winner, player scores
	printf("Game Complete, Player %d wins!\n", finalWinner + 1);
	printf("The Final Scores were:\n");
	printf("Player 1: %d\n", playerPoints[0]);
	printf("Player 2: %d\n", playerPoints[1]);
	printf("Player 3: %d\n", playerPoints[2]);
	printf("Player 4: %d\n", playerPoints[3]);
	

	
	       
}// end of main

//using pointer to pass and return array from/to main
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

void deal(int* shuffledDeck, int* p1, int* p2, int* p3, int* p4) {
	int i;

	//Give the first 13 cards to p1, next 13 to p2 etc.
	for (i = 0; i < 13; i++) {
		p1[i] = shuffledDeck[i];
		p2[i] = shuffledDeck[i + 13];
		p3[i] = shuffledDeck[i + 26];
		p4[i] = shuffledDeck[i + 39];
	}
}

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
		scanf("%d", input);
	}

	//store card being played, change value to -1 in deck
	card[player] = playerHand[input];
	playerHand[input] = -1;
	
}

void displayIntro() {
	printf("Welcome to War!\n");
	printf("Each player has 13 cards in their hand\n");
	printf("Choose the highest card to win. If two players choose the same card then the next highest card will win\n");
	printf("If all cards tie another then the points are rolled over to the next round\n");
	printf("Once a card has been played it can't be played again(represented by a -1)\n");
	printf("Whoever has the most points after 13 rounds wins.\n\n\n");


}
