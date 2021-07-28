// Title: Brummettland Game
// Author:
// Date: Oct 22, 2019
// Purpose: This program simulates a dice rolling game

#include<iostream>
#include<string>
#include<fstream>
#include<ctime>

// Maximum players
#define MAX_PLAYERS 20
// Maximum board space
#define BOARD_SPACES 25

using namespace std;

// functions declarations
void GetPlayersNames(string[], int);
int rollDice(string);
void ActivateActionOnSpace(string[], int[], double[], int, int);
void PlayerFinishedBoard(string[], int[], double[], int);

// Main Function
int main()
{
	// to input play again or not
	string choice;
	do
	{
		system("cls");
		int numOfPlayers;
		cout << "Welcome to BRUMMETTLAND!\n";

		// inputs Number of Players
		cout << "How many Players? ";
		cin >> numOfPlayers;

		// Validates Number of Players
		while (numOfPlayers <= 0 || numOfPlayers > 20)
		{
			cout << "Number of Players should be non negative and in range (1-20)\n";
			cout << "How many Players? ";
			cin >> numOfPlayers;
		}

		// board Space array to store board spaces of players
		int boardSpace[MAX_PLAYERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		// player names
		string names[MAX_PLAYERS] = { "", "", "", "", "", "", "", "", "", "",
			                          "", "", "", "", "", "", "", "", "", "" };

		// Player Scores Array
		double score[MAX_PLAYERS] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

		// gets names of players
		GetPlayersNames(names, numOfPlayers);

		// flag to determine if any player has reached the end of board
		bool boardSpaceFlag = false;
		while (!boardSpaceFlag)
		{
			int player;
			// iterates through players
			for (player = 0; player < numOfPlayers; player++)
			{
				cout << "----------\n";
				cin.get();
				// rolls a dice an adds to board Space of corresponding player
				boardSpace[player] = boardSpace[player] + rollDice(names[player]);
				// if player has finished board
				if (boardSpace[player] >= 25)
				{
					// displays player's info and high score of game
					PlayerFinishedBoard(names, boardSpace, score, numOfPlayers);
					boardSpaceFlag = true;
					break;
				}
				else
				{
					// displays dice and good or bad message
					ActivateActionOnSpace(names, boardSpace, score, numOfPlayers, player);
				}
				cout << "----------\n\n";
			}
		}

		// inputs for play again
		cout << "DO YOU WANT TO PLAY AGAIN?\nY or N: ";
		cin >> choice;
	} while (choice == "Y" || choice == "y");
	return 0;
}

// Get each player’s name 
// places their name in each element of the names array
void GetPlayersNames(string names[], int numOfPlayers)
{
	cout << "\n\n";
	for (int i = 0; i < numOfPlayers; i++)
	{
		cout << "PLAYER " << i + 1 << ", WHAT IS YOUR NAME?\nNAME: ";
		cin >> names[i];
		cout << "\n";
	}
}

// Randomly generate a number between 1 & 6 (for the dice roll) 
// Prints out the player’s name and tell them to press enter to roll die.
int rollDice(string playerName)
{
	srand(time(0));
	cout << playerName << ", PRESS ENTER TO ROLL A DIE.";
	cin.get();  //get is a function that will retrieve ONE character from the keyboard
	// generates a number for die
	int dieRoll = rand() % 6 + 1;
	// displays rolled number of die
	cout << "YOU ROLLED A " << dieRoll << "\n\n";

	// displays die
	switch (dieRoll)
	{
	case 1:
		cout << " _________\n";
		cout << "|         |\n";
		cout << "|    o    |\n";
		cout << "|         |\n";
		cout << "|_________|\n\n";
		break;
	case 2:
		cout << " _________\n";
		cout << "|         |\n";
		cout << "|  o      |\n";
		cout << "|      o  |\n";
		cout << "|_________|\n\n";
		break;
	case 3:
		cout << " _________\n";
		cout << "| o       |\n";
		cout << "|    o    |\n";
		cout << "|       o |\n";
		cout << "|_________|\n\n";
		break;
	case 4:
		cout << " _________\n";
		cout << "| o     o |\n";
		cout << "|         |\n";
		cout << "| o     o |\n";
		cout << "|_________|\n\n";
		break;
	case 5:
		cout << " _________\n";
		cout << "| o     o |\n";
		cout << "|    o    |\n";
		cout << "| o     o |\n";
		cout << "|_________|\n\n";
		break;
	case 6:
		cout << " _________\n";
		cout << "| o     o |\n";
		cout << "| o     o |\n";
		cout << "| o     o |\n";
		cout << "|_________|\n\n";
		break;
	}
	// returns die roll number
	return dieRoll;
}

// Prints out current board space 
// displays what happens on the space – good or bad.  
void ActivateActionOnSpace(string names[], int boardSpace[], double score[], int numOfPlayers, int index)
{
	// for random number
	srand(time(0));
	// displays current board space of player
	cout << names[index] << " IS NOW ON SPACE " << boardSpace[index];
	// generates good or bad (1 or 0)
	int goodOrBad = rand() % 2 + 1;
	// generates number to read from file
	int messageNumber = rand() % 20 + 1;
	// message from file
	string message;

	// if it is good 
	if (goodOrBad == 1)
	{
		// prints Happy face
		cout << "\n    --------\n";
		cout << "   (        )\n";
		cout << "  (  *     * )\n";
		cout << " (      *     )\n";
		cout << "  (  \\    /  )\n";
		cout << "   (  ----  )\n";
		cout << "    --------\n";

		// opens file in read mode
		fstream f;
		f.open("good.txt", ios::in);
		// iterates till number
		for (int i = 1; i <= messageNumber; i++)
		{
			getline(f, message);
		}
		// reads message
		getline(f, message);
		// close file
		f.close();
		// displays message
		cout << "\nGreat!" << message << "\n";
		// generates Score
		double playerScore = rand() % 100000 + 1;
		// adds to player's current score
		score[index] = score[index] + playerScore;
	}

	// for bad
	else
	{
		// prints sad face
		cout << "\n    --------\n";
		cout << "   (        )\n";
		cout << "  (  *     * )\n";
		cout << " (      *     )\n";
		cout << "  (   ----   )\n";
		cout << "   ( /    \\ )\n";
		cout << "    --------\n";

		// opens file in read mode
		fstream f;
		f.open("bad.txt", ios::in);
		//iterates lines
		for (int i = 1; i <= messageNumber; i++)
		{
			getline(f, message);
		}
		// reads message
		getline(f, message);
		// close file
		f.close();
		// prints message
		cout << "\nOh NO!" << message << "\n";
		// generates a score
		double playerScore = rand() % 100000 + 1;
		// subtracts form player's current score
		score[index] = score[index] - playerScore;
	}
	// displays score of player
	cout << "YOU NOW HAVE A SCORE OF " << score[index] << ".\n";
}

// Displays the results of the game 
// who reached the end of the board 
// who ended up with the most score.
void PlayerFinishedBoard(string names[], int boardSpace[], double score[], int numOfPlayers)
{
	// to save player name
	string playerName;
	// finds the name of player who has reached the end of the board
	for (int i = 0; i < numOfPlayers; i++)
	{
		if (boardSpace[i] >= BOARD_SPACES)
		{
			// sets player's name
			playerName = names[i];
			break;
		}
	}

	// to save max score
	double maxScore = score[0];
	// to save max index
	int maxIndex = 0;
	// finds out maximum score 
	for (int i = 1; i < numOfPlayers; i++)
	{
		// if score is greater than maxScore
		if (score[i]>maxScore)
		{
			maxScore = score[i];
			maxIndex = i;
		}
	}

	// displays info
	cout << "PLAYER WHO HAVE SURVIVED ENTIRE BRUMMETTLAND BOARD: " << playerName << "\n";
	cout << "PLAYER WHO HAVE THE HIGHEST SCORE IS: " << names[maxIndex]
		<< " WITH A SCORE OF " << maxScore << "\n\n";
}