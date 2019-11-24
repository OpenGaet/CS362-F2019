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
    	int seed = 1000;
    	int numPlayers = 2;
	int thisPlayer = 0;
	int nextP = thisPlayer + 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Tribute: ----------------\n");


	// ----------- TEST 1: 0 discarded cards, 1 card in the deck --------------
	printf("\n-- TEST 1: 0 discarded cards, 1 card in the deck --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = tribute;
	G.hand[thisPlayer][1] = baron;
	G.hand[thisPlayer][2] = silver;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[nextP] = 5;
	G.hand[nextP][0] = minion;
	G.hand[nextP][1] = copper;
	G.hand[nextP][2] = duchy;
	G.hand[nextP][3] = feast;
	G.hand[nextP][4] = estate;

	// Set discard count and deck count
	G.discardCount[nextP] = 0;
	G.deckCount[nextP] = 1;
	G.numActions = 0;

	// Set deck
	G.deck[nextP][0] = copper;

        // Set trib revealed cards
        int trib[2] = {1, 2};

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	handleTribute(&testG, thisPlayer, nextP, trib);
	G.deckCount[nextP]--;
	G.coins += 2;
	G.numActions += 2;

	confirm(testG.deckCount[nextP] == G.deckCount[nextP]);
	printf("Next Player Deck Count = %d, Expected = %d\n", testG.deckCount[nextP], G.deckCount[nextP]);
	confirm(testG.coins == G.coins);
	printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
	confirm(testG.numActions == G.numActions);
	printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
	confirm(testG.handCount[nextP] == G.handCount[nextP]);
	printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);


	// ----------- TEST 2: 1 discarded card, 0 cards in the deck --------------
	printf("\n-- TEST 2: 1 discarded card, 0 cards in the deck --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = tribute;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = baron;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[nextP] = 5;
	G.hand[nextP][0] = minion;
	G.hand[nextP][1] = copper;
	G.hand[nextP][2] = duchy;
	G.hand[nextP][3] = feast;
	G.hand[nextP][4] = estate;

	// Set discard count and deck count
	G.discardCount[nextP] = 1;
	G.deckCount[nextP] = 0;
	G.numActions = 0;

	// Set discard
	G.discard[nextP][0] = estate;

	// Set trib revealed cards
        trib[0] = 1;
        trib[1] = 2;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	handleTribute(&testG, thisPlayer, nextP, trib);
	G.discardCount[nextP]--;
	G.numActions += 2;
	G.handCount[thisPlayer] += 2;
		
		
	confirm(testG.discardCount[nextP] == G.discardCount[nextP]);
	printf("Next Player Discard Count = %d, Expected = %d\n", testG.discardCount[nextP], G.discardCount[nextP]);
	confirm(testG.coins == G.coins);
	printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
	confirm(testG.numActions == G.numActions);
	printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
	confirm(testG.handCount[nextP] == G.handCount[nextP]);
	printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);


	// ----------- TEST 3: More than one card in deck --------------
	printf("\n-- TEST 3: More than 1 card in deck --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = tribute;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = baron;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[nextP] = 5;
	G.hand[nextP][0] = minion;
	G.hand[nextP][1] = copper;
	G.hand[nextP][2] = duchy;
	G.hand[nextP][3] = feast;
	G.hand[nextP][4] = estate;

	// Set discard count and deck count
	G.discardCount[nextP] = 10;
	G.deckCount[nextP] = 10;
	G.numActions = 0;

	// Set deck
	G.deck[nextP][0] = copper;
	G.deck[nextP][1] = smithy;

	// Set current player deck count to 0
	G.deckCount[thisPlayer] = 0;

	// Set trib revealed cards
        trib[0] = 1;
        trib[1] = 2;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	handleTribute(&testG, thisPlayer, nextP, trib);
	G.deckCount[nextP] -= 2;
	G.coins += 2;
	G.numActions += 2;	
	
	confirm(testG.discardCount[nextP] == G.discardCount[nextP]);
	printf("Next Player Deck Count = %d, Expected = %d\n", testG.deckCount[nextP], G.deckCount[nextP]);
	confirm(testG.coins == G.coins);
	printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
	confirm(testG.numActions == G.numActions);
	printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
	confirm(testG.handCount[nextP] == G.handCount[nextP]);
	printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);


	// ----------- TEST 4: Discards action card --------------
	printf("\n-- TEST 4: Discards an action card --\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Set player hand
	G.hand[thisPlayer][0] = tribute;
	G.hand[thisPlayer][1] = smithy;
	G.hand[thisPlayer][2] = smithy;
	G.hand[thisPlayer][3] = baron;
	G.hand[thisPlayer][4] = feast;

	// Set opponent hand
	G.handCount[nextP] = 5;
	G.hand[nextP][0] = minion;
	G.hand[nextP][1] = copper;
	G.hand[nextP][2] = duchy;
	G.hand[nextP][3] = feast;
	G.hand[nextP][4] = estate;

	// Set discard count and deck count
	G.discardCount[nextP] = 2;
	G.deckCount[nextP] = 2;
	G.deckCount[thisPlayer] = 2;
	G.numActions = 0;

	// Set deck
	G.deck[nextP][0] = copper;
	G.deck[nextP][1] = smithy;

	// Set trib revealed cards
        trib[0] = 1;
        trib[1] = 2;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	handleTribute(&testG, thisPlayer, nextP, trib);
	G.deckCount[nextP] -= 2;
	G.coins += 2;
	G.numActions += 2;	
	
	confirm(testG.discardCount[nextP] == G.discardCount[nextP]);
	printf("Next Player Deck Count = %d, Expected = %d\n", testG.deckCount[nextP], G.deckCount[nextP]);
	confirm(testG.coins == G.coins);
	printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
	confirm(testG.numActions == G.numActions);
	printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
	confirm(testG.handCount[nextP] == G.handCount[nextP]);
	printf("Hand Count = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);

	printf("\n >>>>> Testing complete <<<<<\n\n");

	return 0;
}

