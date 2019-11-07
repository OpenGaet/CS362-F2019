#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"


void confirm (int passed) {
	if (passed == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n",);
}


int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Baron: ----------------\n");

	// ----------- TEST 1: Player Has Estate Card --------------
	printf("TEST 1: Player Has Estate Card\n");

	// Set player hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	effectBaron(choice1, &testG, thisPlayer);

	G.coins += 4;//Add 4 coins to the amount of coins
    G.handCount[thisPlayer]--;

	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	confirm(testG.coins == G.coins);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	

	// ----------- TEST 2: Player Does Not Have Estate Card --------------
	printf("TEST 2: Player Does Not Have Estate Card and Only One Estate Card Left\n");

	// Set player hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	G->supplyCount[estate] = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	effectBaron(choice1, &testG, thisPlayer);

	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	confirm(testG.coins == G.coins);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Is Game Over = %d, expected = %d\n", isGameOver(testG), isGameOver(G));
	confirm(isGameOver(testG) == isGameOver(G))
	

	// ----------- TEST 3: No Estate Card but Tries to Discard One --------------

	printf("TEST 3: choice1 = 3 = trash two cards\n");

	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	effectBaron(choice1, &testG, thisPlayer);

	// tests that the removed cards are no longer in the player's hand
	for (m=0; m < testG.handCount[thisPlayer]; m++) {
		printf("(%d)", testG.hand[thisPlayer][m]);
		assert(testG.hand[thisPlayer][m] != remove1);
		assert(testG.hand[thisPlayer][m] != remove2);
	}
	printf(", expected: ");
	for (m=1; m<G.handCount[thisPlayer]; m++) {
		if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
			printf("(%d)", G.hand[thisPlayer][m]);
		}
	}
	printf("\n");

	// tests for the appropriate number of remaining cards
	newCards = 0;
	xtraCoins = 0;
	discarded = 3;
	if (i==1 && j==2) {
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	}
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);


	printf("\n >>>>> SUCCESS: Testing complete <<<<<\n\n");


	return 0;
}

