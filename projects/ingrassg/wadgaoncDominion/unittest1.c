#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"


void confirm (int passed) {
	if (passed == 1)
		printf("PASSED: ");
	else
		printf("FAILED: ");
}


int main() {
    	int choice1 = 0;
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
	printf("\n-- TEST 1: Player Has Estate Card --\n");

	// Set player hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	handleBaron(&testG, choice1, thisPlayer);

	G.coins += 4;//Add 4 coins to the amount of coins
    	G.handCount[thisPlayer]--;

	confirm(testG.coins == G.coins);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		

	// ----------- TEST 2: Player Does Not Have Estate Card but There are None to Get --------------
	printf("\n-- TEST 2: Player Does Not Have Estate Card but there are none in supply --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// Copy the game state to a test case
	G.supplyCount[estate] = 0;
	G.supplyCount[duchy] = 0;
	G.supplyCount[copper] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	handleBaron(&testG, choice1, thisPlayer);
	discardCard(0, thisPlayer, &G, 0);

	confirm(testG.coins == G.coins);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	confirm(isGameOver(&testG) == isGameOver(&G));
	printf("Is Game Over = %d, expected = %d\n", isGameOver(&testG), isGameOver(&G));
	
	// ----------- TEST 3: No Estate Card but Tries to Discard One --------------

	printf("\n-- TEST 3: Player Does Not Have an Estate Card but Tries to Discard One --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	G.hand[thisPlayer][0] = baron;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	handleBaron(&testG, choice1, thisPlayer);
	
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);

	printf("\n >>>>> Testing complete <<<<<\n\n");

	return 0;
}

