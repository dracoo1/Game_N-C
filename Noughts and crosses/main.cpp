#include<iostream>
#include<string>
#include<stdio.h>
#include<conio.h> //this is only used for _getch
using namespace std;

//defined to shorten function
#define cls system("cls")

//if true, game is active, if false, game has ended
bool gamestate = true;
//if false then game is pvp 
bool aiEnabled = false;
//false = player1, true = player2/ai
bool turn = false;
//player input for selecting space on grid
int input;

string grid[3][3];

//player Names
string P1Name = "Player 1";
string P2Name = "Player 2";

char key = ' ';

string Winner = "";
//only used to select menu or game 
int selection = 0;


class Game {
public:
	//stores default grid
	string grid[3][3] = { {"1","4","7"}, {"2","5","8"}, { "3","6","9"} };

	//defines marker and _player
	string marker;
	string _player;

	int AIPlace;
	Game(){

		//player 1
		if (!turn)
		{
			marker = "x";
			_player = P1Name;
		}
		//player2/AI
		else
		{
			marker = "o";
			_player = P2Name;

			if (aiEnabled)
			{
				key = (rand() % 9 + 1) + '0';
			}

		}
		
	}
};


//class 

void GameReset()
{
	Game Game;

	//loops through grid replacing each section in the grid to its original value (numbers 1-9)
	for (int x = 0; x <= 2; x++)
	{
		for (int y = 0; y <= 2; y++)
		{
				
			grid[x][y] = Game.grid[x][y];

		}
	}
	turn = false;
	gamestate = true;
	Winner == "";
}
//this only holds the grid
void Pgrid()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (grid[x][y] == "x")
			{
				printf("\033[32m%s\033[0m", grid[x][y].c_str());
			}
			else if (grid[x][y] == "o")
			{
				printf("\033[31m%s\033[0m", grid[x][y].c_str());
			}
			else
			{
				printf("%s", grid[x][y].c_str());
			}
			if (y < 2) { printf(" | "); }
		}
		if (x < 2) { printf("\n---+---+---\n"); }
	}
	printf("\n\n\n");

};
void game()
{
	//clears screen
	cls;
	//defines the class "Game"
	Game Game;


	
	//grid 
	Pgrid();
	printf("%s's", Game._player.c_str());
	
	//conditions to check if it is the ai's turn(if enabled)
	if (aiEnabled == true && turn)
	{
		Game.AIPlace;
	}
	else
	{
		key = _getch();
	}
	
	//converts value from key from char to string to be used for finding number in grid
	string str(1,key);
	cout << "\n" << str.c_str() << "\n";

	bool invalidplacement = true;
	//loops through grid to find correct number and replaces number with players marker
	for (int x = 0; x <= 2; x++)
	{
		for (int y = 0; y <= 2; y++)
		{
			if (str == grid[x][y] && str != "x" && str != "o") {
				//calls player.marker to get the correct marker ("x" or "o")
				grid[x][y] = Game.marker;
				turn = !turn;
				invalidplacement = false;
				break;
			}
		}
	}
	if(invalidplacement == true && !turn || invalidplacement == true && !aiEnabled)
	{
		cout << "Select an available grid.\n";
		_getch();
	}

	//

	
	//win condition
	for (int i = 0; i <= 2; i++)
	{
		if (grid[i][0] == "x" && grid[i][1] == "x" && grid[i][2] == "x") {
			gamestate = false;
			Winner = "Winner: " + P1Name;
		}
		else if (grid[i][0] == "o" && grid[i][1] == "o" && grid[i][2] == "o") {
			gamestate = false;
			Winner = "Winner: " + P2Name;
		}
		else if (grid[0][i] == "x" && grid[1][i] == "x" && grid[2][i] == "x") {
			gamestate = false;
			Winner = "Winner: " + P1Name;
		}
		else if (grid[0][i] == "o" && grid[1][i] == "o" && grid[2][i] == "o") {
			gamestate = false;
			Winner = "Winner: " + P2Name;
		}	
	}
	if (grid[0][0] == "x" && grid[1][1] == "x" && grid[2][2] == "x") {
		gamestate = false;
		Winner = "Winner: " + P1Name;
	}
	if (grid[0][2] == "x" && grid[1][1] == "x" && grid[2][0] == "x") {
		gamestate = false;
		Winner = "Winner: " + P1Name;
	}
	if (grid[0][0] == "o" && grid[1][1] == "o" && grid[2][2] == "o") {
		gamestate = false;
		Winner = "Winner: " + P2Name;
	}
	if (grid[0][2] == "o" && grid[1][1] == "o" && grid[2][0] == "o") {
		gamestate = false;
		Winner = "Winner: " + P2Name;
	}

	//draw condition
	int filledCells = 0;
	for (int x = 0; x <= 2; x++)
	{
		for (int y = 0; y <= 2; y++)
		{
			// Loop through each character in the string and check if it's a digit
			if (grid[x][y] == "x" || grid[x][y] == "o") { filledCells++; };
		}
	}
	if (filledCells == 9) {
		gamestate = false;
		Winner = "Draw";
	}

	while (gamestate == false)
	{
		cls;
		Pgrid();
		printf("%s\n\nR: rematch\nW: Menu\nQ: Quit",Winner.c_str());
		input = _getch();
		string str(1, input);
		if (str == "r" || str == "R")
		{
			GameReset();
		}
		else if (str == "w" || str == "W")
		{
			GameReset();
			selection = 0;
		}
		else if (str == "q" || str == "Q")
		{
			exit(0);
		}
	}
};

void help()
{
	printf("players will take turns selecting boxes,\nthe first player to 3 in a row wins\nplayers can only choose blank spaces/spaces with numbers in them\n\nAI will choose spaces at random\n\n\n\n\n\n\nPress any key to continue");
	
	_getch();
}

void menu()
{	
	

	cls;
	printf("Welcome to Noughts and Crosses\n\nAI Enabled: %s\n\nP1: %s     P2: %s\n\n1:Play\n2:help\n3:quit\n\nE:Switch between 2 player or Player vs AI\nZ:Change Player 1's name       X:Change Player 2's Name\n",aiEnabled ? "true" : "false",P1Name.c_str(), P2Name.c_str());
	
	//infroms the user that their input was invalid
	if (input == 0 || NULL)
	{
		cout << "\npress key" << endl;
	}
	else
	{
		cout << "\ninvalid selection\npress key" << endl;
	};
	
	//_getch gets key input on key press
	char key = _getch();
	cout << key;
	//menu inputs
	if (key == '1')
	{
		GameReset();
		selection = 1;
		input = 0;
	}
	else if (key == '2')
	{
		cls;
		help();
		input = 0;
	}
	else if (key == '3')
	{
		cls;
		exit(0);
	}
	else if (key == 'E' || key == 'e')
	{
		aiEnabled = !aiEnabled;
	}
	else if (key == 'Z' || key == 'z')
	{
		cls;
		printf("Enter new name for %s\n", P1Name.c_str());
		cin >> P1Name;
	}
	else if (key == 'X' || key == 'x')
	{
		cls;
		printf("Enter new name for %s\n",P2Name.c_str());
		cin >> P2Name;
	}
	else
	{
		input = 1;
	};


};

int main() 
{

	while (true)
	{
		switch (selection)
		{
		case 0: menu();
			break;
		case 1:
			game();
			break;

		default: selection = 0;
		}
	}
	return 0;
}