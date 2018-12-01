/*********************************************************************
** Program Filename: randomtestadventurer.c
** Author: Kurt Schraml
** Date: 14 Nov 18
** Description: random tester for dominion.c adventurer card
** Notes:  cardtest4.c, testBuyCard.c, and Slack discussions used as sources
*********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	struct gameState originalState, testState;
	int numPlayers;
	int currentPlayer;
	int handPos = 0;
	//int addedCard = 1;
	//int discardedCard = 1;
	//int addedAction = 1;
	//int i;
	int j;
	int topcard;
	int secondtopcard;
	
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	srand(time(0));

	for (j = 0; j < 30; j++)
	{
		printf("GAME NUMBER: %d\n", j);
		//randomly determine numPlayers

		numPlayers = rand() % (4 + 1 - 2) + 2;
		//numPlayers = 2;

		//printf("numPlayers = %d\n", numPlayers);
		//getchar();

		int seed = 1000;
		int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall };

		//clear contents of both original and test gamestates
		memset(&originalState, 23, sizeof(struct gameState));
		memset(&testState, 23, sizeof(struct gameState));

		//intialize gamesState
		initializeGame(numPlayers, k, seed, &originalState);

		//printf("Game Initialized\n");
		//getchar();

		//randomly determine current player
		currentPlayer = rand() % numPlayers;
		originalState.whoseTurn = currentPlayer;

		//randomize deckCount, handCount, and discardCount (from testBuyCard.c and per Slack discussion)
		originalState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		originalState.discardCount[currentPlayer] = floor(Random() * (MAX_DECK - originalState.deckCount[currentPlayer]));
		originalState.handCount[currentPlayer] = floor(Random() * MAX_HAND);

		//copy the initialized gameState to the test gameState
		memcpy(&testState, &originalState, sizeof(struct gameState));

		//printf("Gamestates copied\n");
		//getchar();

		//printf("originalState numPlayers: %d\n", originalState.numPlayers);
		//printf("testState numPlayers: %d\n", testState.numPlayers);



		//printf("currentPlayer = %d\n", currentPlayer);
		//getchar();

		//call method under test using testState
		cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);

		//printf("function called successfully\n");
		//getchar();

		/*test for effects of adventurer
		  handcount should be +2
		  deckcount should be lower by 2 or more - NOT ALWAYS
		  top 2 cards in hand should be copper, silver, or gold
		*/
		if (testState.handCount[currentPlayer] - originalState.handCount[currentPlayer] != 2)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], originalState.handCount[currentPlayer] + 2);
		}

		/*
		// Removed because deck count may not be lower than when it started if the deck was reshuffled during the round
		if (originalState.deck[i][originalState.deckCount[i]] - testState.deck[i][testState.deckCount[i]] < 2)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Deck count = %d, expected = %d or lower\n", testState.deckCount[currentPlayer], originalState.deckCount[currentPlayer] - 2);
		}
		*/

		topcard = testState.hand[currentPlayer][testState.handCount[currentPlayer] - 1];
		secondtopcard = testState.hand[currentPlayer][testState.handCount[currentPlayer] - 2];

		if (topcard != copper && topcard != silver && topcard != gold)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Top card is not treasure, expected copper, silver, or gold\n");
		}

		if (secondtopcard != copper && secondtopcard != silver && secondtopcard != gold)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Second card from top is not treasure, expected copper, silver, or gold\n");
		}
	}
		return 0;
}
