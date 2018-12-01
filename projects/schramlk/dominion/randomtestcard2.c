/*********************************************************************
** Program Filename: randomtestcard2.c
** Author: Kurt Schraml
** Date: 14 Nov 18
** Description: random tester for dominion.c sea_hag card
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
	int addedCard = 1;
	int discardedCard = 1;
	//int addedAction = 1;
	int i;
	int j;

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
		cardEffect(sea_hag, choice1, choice2, choice3, &testState, handPos, &bonus);

		//printf("function called successfully\n");
		//getchar();

		//replicate function effect in originalState
		for (i = 0; i < numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				originalState.discard[i][originalState.discardCount[i]] = originalState.deck[i][originalState.deckCount[i]--];
				originalState.deckCount[i]--;
				originalState.discardCount[i]++;
				originalState.deck[i][originalState.deckCount[i]--] = curse;
			}
		}

		//test all players for curse card and deck/hand counts
		for (i = 0; i < numPlayers; i++)
		{
			if (i == currentPlayer)
			{
				if (testState.deck[i][testState.deckCount[i]] != originalState.deck[i][originalState.deckCount[i]])
				{
					printf("Bug Found:\n");
					printf("Current Player: %d\n", currentPlayer);
					printf("Top card = %d, expected = %d\n", testState.deck[i][testState.deckCount[i]], originalState.deck[i][originalState.deckCount[i]]);
				}

				if (testState.deckCount[currentPlayer] != originalState.deckCount[currentPlayer])
				{
					printf("Bug Found:\n");
					printf("Current Player: %d\n", currentPlayer);
					printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], originalState.deckCount[currentPlayer]);
				}

				if (testState.handCount[currentPlayer] != originalState.handCount[currentPlayer] + addedCard - discardedCard)
				{
					printf("Bug Found:\n");
					printf("Current Player: %d\n", currentPlayer);
					printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], originalState.handCount[currentPlayer] + addedCard - discardedCard);
				}
			}

			if (i != currentPlayer)
			{
				if (testState.deck[i][testState.deckCount[i]] != originalState.deck[i][originalState.deckCount[i]])
				{
					printf("Bug Found:\n");
					printf("Player: %d\n", i);
					printf("Top card = %d, expected = %d\n", testState.deck[i][testState.deckCount[i]], originalState.deck[i][originalState.deckCount[i]]);
				}

				if (testState.handCount[i] != originalState.handCount[i])
				{
					printf("Bug Found:\n");
					printf("Player: %d\n", i);
					printf("Hand count = %d, expected = %d\n", testState.handCount[i], originalState.handCount[i]);
				}

				if (testState.deckCount[i] != originalState.deckCount[i])
				{
					printf("Bug Found:\n");
					printf("Player %d:\n", i);
					printf("Deck count = %d, expected = %d\n", testState.deckCount[i], originalState.deckCount[i]);
				}
			}
		}
	}
		return 0;
}
