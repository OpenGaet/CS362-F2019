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
    	int seed = 1000;
    	int numPlayers = 2;
	int thisPlayer = 0;
	int nextP = thisPlayer + 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	printf("----------------- Testing Tribute: ----------------\n");

	int test1 = 0;
	int test2 = 0;
	int test3 = 0;
	int i;

	while (test1 < 100 || test2 < 100 || test3 < 100){ 
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		// Set player hand
		G.handCount[thisPlayer] = rand () % 5;
		G.hand[thisPlayer][0] = tribute;
		G.hand[thisPlayer][1] = randCard();
		G.hand[thisPlayer][2] = randCard();
		G.hand[thisPlayer][3] = randCard();
		G.hand[thisPlayer][4] = randCard();
		// Set opponent hand
		G.handCount[nextP] = rand () % 5;
		G.hand[nextP][0] = randCard();
		G.hand[nextP][1] = randCard();
		G.hand[nextP][2] = randCard();
		G.hand[nextP][3] = randCard();
		G.hand[nextP][4] = randCard();
		// Set discard count and deck count
		G.deckCount[thisPlayer] = rand() % 5;
		G.discardCount[nextP] = rand() % 5;
		G.deckCount[nextP] = rand() % 5;
		G.numActions = 0;
		// Set deck
		G.deck[nextP][0] = randCard();
		G.deck[nextP][1] = randCard();
		G.deck[nextP][2] = randCard();
		G.deck[nextP][3] = randCard();
		G.deck[nextP][4] = randCard();
		// Set discard
		G.discard[nextP][0] = randCard();
		G.discard[nextP][1] = randCard();
		G.discard[nextP][2] = randCard();
		G.discard[nextP][3] = randCard();
		G.discard[nextP][4] = randCard();
	
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		effectTribute(&testG, thisPlayer, nextP);
		G.deckCount[nextP]--;

		for (i = 0; i < 2; i ++) {
            		if (G.playedCards[i] == copper || G.playedCards[i] == silver || G.playedCards[i] == gold) { //Treasure cards
	                	G.coins += 2;
			}
			else if (G.playedCards[i] == estate || G.playedCards[i] == duchy || G.playedCards[i] == province || 
			  G.playedCards[i] == gardens || G.playedCards[i] == great_hall) { //Victory Card Found
				G.handCount[thisPlayer] += 2;		
			}
			else { //Action Card
				G.numActions += 2;                 
			}
		}
		
		if (G.discardCount[nextP] == 0 && G.deckCount[nextP] == 1) {
			test1++;
			confirm(testG.deckCount[nextP] == G.deckCount[nextP]);
			printf("Next Player Deck Count = %d, Expected = %d\n", testG.deckCount[nextP], G.deckCount[nextP]);
			confirm(testG.coins == G.coins);
			printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
			confirm(testG.numActions == G.numActions);
			printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
			confirm(testG.handCount[nextP] == G.handCount[nextP]);
			printf("Hand Count = %d, Expected = %d\n", testG.handCount[nextP], G.handCount[nextP]);
		}
		else if (G.discardCount[nextP] == 1 && G.deckCount[nextP] == 0) {
			test2++;
			confirm(testG.discardCount[nextP] == G.discardCount[nextP]);
			printf("Next Player Discard Count = %d, Expected = %d\n", testG.discardCount[nextP], G.discardCount[nextP]);
			confirm(testG.coins == G.coins);
			printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
			confirm(testG.numActions == G.numActions);
			printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
			confirm(testG.handCount[nextP] == G.handCount[nextP]);
			printf("Hand Count = %d, Expected = %d\n", testG.handCount[nextP], G.handCount[nextP]);
		}
		else if (G.deckCount[nextP] > 1) {
			test3++;
			confirm(testG.discardCount[nextP] == G.discardCount[nextP]);
			printf("Next Player Deck Count = %d, Expected = %d\n", testG.deckCount[nextP], G.deckCount[nextP]);
			confirm(testG.coins == G.coins);
			printf("Coins = %d, Expected = %d\n", testG.coins, G.coins);
			confirm(testG.numActions == G.numActions);
			printf("Number of Actions = %d, Expected = %d\n", testG.numActions, G.numActions);
			confirm(testG.handCount[nextP] == G.handCount[nextP]);
			printf("Hand Count = %d, Expected = %d\n", testG.handCount[nextP], G.handCount[nextP]);
		}
	}

	
	printf("\n >>>>> Testing complete <<<<<\n\n");
	return 0;
}

