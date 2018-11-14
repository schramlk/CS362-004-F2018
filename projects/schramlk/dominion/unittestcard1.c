/*********************************************************************
** Program Filename: unittestcard1.c
** Author: Kurt Schraml
** Date: 14 Nov 18
** Description: unit tester for dominion.c great_hall card
** Notes:  cardtest4.c used as a source
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
	int addedAction = 1;
	int i;
	//int j;
	//int randomNumActions;

	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	//for (j = 0; j < 10000; j++)
	//{
		//randomly determine numPlayers
		//srand(time(0));
		//numPlayers = rand() % (4 + 1 - 2) + 2;
		numPlayers = 2;

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

		//copy the initialized gameState to the test gameState
		memcpy(&testState, &originalState, sizeof(struct gameState));

		//printf("Gamestates copied\n");
		//getchar();

		//printf("originalState numPlayers: %d\n", originalState.numPlayers);
		//printf("testState numPlayers: %d\n", testState.numPlayers);

		//randomly determine current player
		//currentPlayer = rand() % numPlayers;
		//originalState.whoseTurn = currentPlayer;
		//testState.whoseTurn = currentPlayer;
		currentPlayer = 0;

		//printf("currentPlayer = %d\n", currentPlayer);
		//getchar();

		//randomly determine number of actions (usually assigned 1 at the beginning of each turn)
		//assigns random number between 1 and 5
		//randomNumActions = rand() % 5 + 1;
		//originalState.numActions = randomNumActions;
		//testState.numActions = randomNumActions;

		//call method under test
		//cardEffectGreatHall(currentPlayer, handPos, &testState);
		cardEffect(great_hall, choice1, choice2, choice3, &testState, handPos, &bonus);

		//printf("function called successfully\n");
		//getchar();

		//test numActions and deck/hand count values for current player
		if (testState.handCount[currentPlayer] != originalState.handCount[currentPlayer] + addedCard - discardedCard)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], originalState.handCount[currentPlayer] + addedCard - discardedCard);
		}

		if (testState.deckCount[currentPlayer] != originalState.deckCount[currentPlayer] - addedCard)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], originalState.deckCount[currentPlayer] - addedCard);
		}

		if (testState.numActions != originalState.numActions + addedAction)
		{
			printf("Bug Found:\n");
			printf("Current Player: %d\n", currentPlayer);
			printf("Number of Actions = %d, expected = %d\n", testState.numActions, originalState.numActions + addedAction);
		}

		//printf("Current Player: %d\n", currentPlayer);
		//printf("Hand count = %d, expected = %d\n", testState.handCount[currentPlayer], originalState.handCount[currentPlayer] + addedCard - discardedCard);
		//printf("Deck count = %d, expected = %d\n", testState.deckCount[currentPlayer], originalState.deckCount[currentPlayer] - addedCard);
		//printf("Number of Actions = %d, expected = %d\n", testState.numActions, originalState.numActions + addedAction);

		//test deck/hand count values for other players

		for (i = 0; i < numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if (testState.handCount[i] != originalState.handCount[i])
				{
					printf("Bug Found:\n");
					printf("Player %d:\n", i);
					printf("Hand count = %d, expected = %d\n", testState.handCount[i], originalState.handCount[i]);
				}

				if (testState.deckCount[i] != originalState.deckCount[i])
				{
					printf("Player %d:\n", i);
					printf("Bug Found:\n");
					printf("Deck count = %d, expected = %d\n", testState.deckCount[i], originalState.deckCount[i]);
				}

				//printf("Player %d:\n", i);
				//printf("Hand count = %d, expected = %d\n", testState.handCount[i], originalState.handCount[i]);
				//printf("Deck count = %d, expected = %d\n", testState.deckCount[i], originalState.deckCount[i]);
			}
		}

		//assert(testState.handCount[currentPlayer] == originalState.handCount[currentPlayer] + addedCard - discardedCard);
		//assert(testState.deckCount[currentPlayer] == originalState.deckCount[currentPlayer] - addedCard);
	//}

	
	
	return 0;
}



/*
Method under test:

int cardEffectGreatHall(int currentPlayer, int handPos, struct gameState *state)
{
//+1 Card
drawCard(currentPlayer, state);

//+1 Actions
state->numActions--;        //bug here:  should be < state->numActions++;  >

//discard card from hand
discardCard(handPos, currentPlayer, state, 0);
return 0;
}

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus){...}
cardEffectGreatHall(currentPlayer, handPos, state);

*/
