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

	
	printf("----------------- Testing Ambassador: ----------------\n");

	// ----------- TEST 1: Trying to choose 3 of the available copies --------------
	printf("\n-- TEST 1: Choosing 3 Available Copies --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = ambassador;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	//printf("Supply Count for Smithy = %d\n", G.supplyCount[smithy]);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 3;
	handPos = 0;
	int result = effectAmbassador(choice1, choice2, &testG, handPos, thisPlayer);
	//discardCard(0, thisPlayer, &G, 0);
	//G.supplyCount[smithy] += choice2;
	//gainCard(smithy, &G, 0, thisPlayer + 1);	
	
	//G.handCount[thisPlayer] -= 3;

	confirm(result == -1);
	printf("Function Return = %d, Expected = %d\n", result, -1);
	//confirm(testG.supplyCount[smithy] == G.supplyCount[smithy]);
	//printf("Supply Count for Smithy = %d, Expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);		

	// ----------- TEST 2: Choice 2 (discard hand, +4 cards, other players do the same if they have >4 cards --------------
	printf("\n-- TEST 2: Trying to Choose 4 Copies from 2 Available--\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = ambassador;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = baron;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[thisPlayer + 1] = 5;
	G.hand[thisPlayer + 1][0] = minion;
	G.hand[thisPlayer + 1][1] = copper;
	G.hand[thisPlayer + 1][2] = duchy;
	G.hand[thisPlayer + 1][3] = feast;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 4;
	handPos = 0;
	result = effectAmbassador(choice1, choice2, &testG, handPos, thisPlayer);	
	discardCard(0, thisPlayer, &G, 0);
		
	confirm(result == -1);
	printf("Function Return = %d, Expected = %d\n", result, -1);
	
	//confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	//printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	//confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	//printf("Opponent Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
	
	// ----------- TEST 3: Trying to choose 3 of the available copies --------------
	printf("\n-- TEST 3: Choosing 2 Available Copies --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = ambassador;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = baron;
	G.hand[thisPlayer][4] = feast;

//	printf("Supply Count for Smithy = %d\n", G.supplyCount[smithy]);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 2;
	handPos = 0;
	result = effectAmbassador(choice1, choice2, &testG, handPos, thisPlayer);
	//discardCard(0, thisPlayer, &G, 0);
	G.supplyCount[smithy] += choice2;
	gainCard(smithy, &G, 0, thisPlayer + 1);	
	
	//G.handCount[thisPlayer] -= 3;

	//confirm(result == -1);
	//printf("Function Return = %d, Expected = %d\n", result, -1);
	confirm(testG.supplyCount[smithy] == G.supplyCount[smithy]);
	printf("Supply Count for Smithy = %d, Expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);	
	printf("\n >>>>> Testing complete <<<<<\n\n");

	return 0;
}

