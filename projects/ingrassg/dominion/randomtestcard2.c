#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"


char randCard()
{
    	// Generate random card
	int cardStart = 0;
        int cardEnd = 26;
        char c = (rand() % (cardEnd - cardStart + 1)) + cardStart;
    
	return c;
}

void confirm (int passed) {
	if (passed == 1)
		printf("PASSED: ");
	else
		printf("FAILED: ");
}


int main() {
    	int choice1, choice2, handPos;
      	int seed = 1000;
    	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Minion: ----------------\n");

	int test1 = 0;
	int test2 = 0;
	while (test1 < 100 || test2 < 100) {

		// Initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		// Randomize player hand
		G.handCount[thisPlayer] = 5;
		G.hand[thisPlayer][0] = minion;
		G.hand[thisPlayer][1] = randCard();
		G.hand[thisPlayer][2] = randCard();
		G.hand[thisPlayer][3] = randCard();
		G.hand[thisPlayer][4] = randCard();
		// Randomize opponent hand
		G.handCount[thisPlayer + 1] = 5;
		G.hand[thisPlayer + 1][0] = minion;
		G.hand[thisPlayer + 1][1] = randCard();
		G.hand[thisPlayer + 1][2] = randCard();
		G.hand[thisPlayer + 1][3] = randCard();
		G.hand[thisPlayer + 1][4] = randCard();
		// Randomize choices
		choice1 = rand() % 2;
		choice2 = rand() % 2;
		handPos = 0;
		// Copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		effectMinion(choice1, choice2, &testG, handPos, thisPlayer);	
		discardCard(0, thisPlayer, &G, 0);
	
		if (choice1 == 1) {
			test1++;
			G.coins += 2;//Add 4 coins to the amount of coins
			confirm(testG.coins == G.coins);
			printf("coins = %d, expected = %d\n", testG.coins, G.coins);
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		}
		else if (choice2 == 1) {
			test2++;
			G.handCount[thisPlayer + 1] = 4;
			confirm(testG.coins == G.coins);
			printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Opponent Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
		}
	}
	
	printf("\n >>>>> Testing complete <<<<<\n\n");
	return 0;
}

