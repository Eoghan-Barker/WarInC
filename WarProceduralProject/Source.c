#include <stdio.h>
#include <stdlib.h>


void shuffle(int *shuffledDeck);
void deal(int *shuffledDeck, int *p1, int* p2, int* p3, int* p4);
void chooseCard(int *playerHand, int player, int *card);


void main() {
	//Variables and Arrays
	int deckOfCards[52];
	int player1Hand[13];
	int player2Hand[13];
	int player3Hand[13];
	int player4Hand[13];

	int chosenCard[4];
	int playerPoints[4];

	int i, rounds = 1, roundPoints;

	

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

		//Calculate points
		//reset roundPoints
		roundPoints = 0;
		for (i = 0; i < 4; i++){
			roundPoints += chosenCard[i];
		}

		//Find winning card


		//Add to winners total


		rounds++;
	} while (rounds != -1 || rounds <= 13);

			

	
	       
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

	printf("Player %d hand: \n", player + 1);
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

	playerHand[input] = -1;
	card[player] = input;
}
