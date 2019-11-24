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
	srand(time(0));
    	int choice1;
      	int seed = 1000;
    	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	printf("----------------- Testing Baron: ----------------\n");

	int test1 = 0;
	int test2 = 0;
	int test3 = 0;

	while (test1 < 100 || test2 < 100 || test3 < 100){

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		// Randomize player hand
		G.handCount[thisPlayer] = rand() % 6;
		G.hand[thisPlayer][0] = baron;
		G.hand[thisPlayer][1] = randCard();
		G.hand[thisPlayer][2] = randCard();
		G.hand[thisPlayer][3] = randCard();
		G.hand[thisPlayer][4] = randCard();
		// Randomize choice
		choice1 = rand() % 2;
		// Randomize supply count
		G.supplyCount[estate] = rand() % 3;
		G.supplyCount[duchy] = rand() % 3;
		G.supplyCount[copper] = rand() % 3;
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		effectBaron(choice1, &testG, thisPlayer);
	
		if (G.hand[thisPlayer][1] == estate && choice1 == 1) {
			test1++;
			G.coins += 4; //Add 4 coins to the amount of coins
	    		discardCard(0, thisPlayer, &G, 0);
			confirm(testG.coins == G.coins);
			printf("coins = %d, expected = %d\n", testG.coins, G.coins);
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		}
		else if (G.hand[thisPlayer][1] != estate && G.supplyCount[estate] == 0 && choice1 == 0) {
			test2++;
			discardCard(0, thisPlayer, &G, 0);
			confirm(testG.coins == G.coins);
			printf("coins = %d, expected = %d\n", testG.coins, G.coins);
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			confirm(isGameOver(&testG) == isGameOver(&G));
			printf("Is Game Over = %d, expected = %d\n", isGameOver(&testG), isGameOver(&G));
			
		}
		else if (G.hand[thisPlayer][1] != estate && choice1 == 1) {
			test3++;
			confirm(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
			printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		}
	}
		
	printf("\n >>>>> Testing complete <<<<<\n\n");
	return 0;
}

