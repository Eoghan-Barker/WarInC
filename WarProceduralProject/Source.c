#include <stdio.h>
#include <stdlib.h>


void shuffle(int *shuffledDeck);


void main() {
	//Variables and Arrays
	int deckOfCards[52];

	int playersCardChoice[4];

	int i;

	

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

	/*printf("\n");
	for (int i = 0; i < 52; i++) {
		printf("%d  ", deckOfCards[i]);
	}*/

	
	       
}// end of main

void shuffle(int *shuffledDeck) {
	int i, j, k;
	srand ( time(NULL) );

	//move through each array index and swap the value of that index with the value of a random index
	for (i = 0; i < 52 - 1; i++)
	{
		//create random number between 0-51
		j = rand() % 52;
		printf("%d ", j);
		//store value from random index
		k = shuffledDeck[j];
		//swap random index value with current index value
		shuffledDeck[j] = shuffledDeck[i];
		shuffledDeck[i] = k;
	}
}
