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
    	int choice1, choice2, handPos;
      	int seed = 1000;
    	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Minion: ----------------\n");

	// ----------- TEST 1: Choice 1 (+2 Coin) --------------
	printf("\n-- TEST 1: Choice 1 --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = minion;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 0;
	handPos = 0;
	handleMinion(&testG, choice1, choice2, thisPlayer, handPos);	

	G.coins += 2;//Add 4 coins to the amount of coins
    	G.handCount[thisPlayer]--;

	confirm(testG.coins == G.coins);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		

	// ----------- TEST 2: Choice 2 (discard hand, +4 cards, other players do the same if they have >4 cards --------------
	printf("\n-- TEST 2: Choice 2 --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = minion;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[thisPlayer + 1] = 5;
	G.hand[thisPlayer + 1][0] = minion;
	G.hand[thisPlayer + 1][1] = copper;
	G.hand[thisPlayer + 1][2] = duchy;
	G.hand[thisPlayer + 1][3] = smithy;
	G.hand[thisPlayer + 1][4] = feast;

	// Copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	handPos = 0;
	handleMinion(&testG, choice1, choice2, thisPlayer, handPos);	
	discardCard(0, thisPlayer, &G, 0);
	G.handCount[thisPlayer + 1] = 4;

	confirm(testG.coins == G.coins);
	printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	printf("Opponent Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
	
	
	printf("\n >>>>> Testing complete <<<<<\n\n");

	return 0;
}

