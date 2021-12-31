#include <stdio.h>


void main() {
	//Variables and Arrays
	int deckOfCards[4][13];
/*	int player1Hand[13];
	int player2Hand[13];
	int player3Hand[13];
	int player4Hand[13];*/

	int playersCardChoice[4];

	int i, j, k, roundWinner;

	const int NUM_PLAYERS = 4;

	//populate deck of cards array
	//Ace = index0 value14, J,Q,K =11,12,13
	//Suits - 0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++) {
			if (j == 0) {
				deckOfCards[i][j] = 14;
			}
			else {
				deckOfCards[i][j] = j + 1;
			}	
		}
	}

	//Shuffle deck

	//Deal cards to p1, p2, p3, p4
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++) {
		    /*if (i == 0) {
				player1Hand[j] = deckOfCards[j][i];
			}
			else if (i == 1){
				player2Hand[j] = deckOfCards[j][i];
			}
			else if (i == 2) {
				player3Hand[j] = deckOfCards[j][i];
			}
			else if (i == 3) {
				player4Hand[j] = deckOfCards[j][i];
			}*/

		}
	}

	//play 13 rounds
	for (i = 0; i < 13; i++) {
		//print each players deck and ask them to choose a card to play
		for (j = 0; j < NUM_PLAYERS; j++) {

			printf("Round %d: \n", i+1);
			printf("Player %d deck: ", j+1);
			for (k = 0; k < 13; k++) {
				printf("%d:%d\t", k, deckOfCards[j][k]);
			}
			do {
				printf("Choose a card to play(0-12): ");
				scanf("%d", &playersCardChoice[j]);
				if (deckOfCards[j][playersCardChoice[j]] == -1) {
					printf("Card already played, choose another");
				}
			} while (deckOfCards[j][playersCardChoice[j]] == -1);
			
		}

		//calculate winner and add points to total
		if(deckOfCards[0][playersCardChoice[0]])

	}
	       


}