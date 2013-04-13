#include "TTTGame.h"

Game::Game(){};
//function definitions
void Game::Instructions(void)
{
    /* Welcome's player and gives instructions */
	cout << "*************************\n"
		 << "Welcome to Tic Tac Toe!\n"
		 << "To make a move press a number from 0-8 "
		 << "corresponding to the board.\n"
		 << "*************************\n";

	cout << "Dummy Board\n"
		 << "\n\t0 | 1 | 2 "
	     << "\n\t——————————"
	     << "\n\t3 | 4 | 5 "
	     << "\n\t——————————"
	     << "\n\t6 | 7 | 8 "
	     << "\n\n"
		 << "*************************\n";

	cout << "Current Score:\nHuman: " << HumanScore
		 << "\nMachine: " << CompScore << "\n";
}

char Game::AskYesNo(string question)
{
    /* Simple function to ask a Yes or No question and return's the answer in Y or N */
	char answer;
	do
	{
		cout << endl << question << " (Y/N): ";
		cin >> answer;
	}while(answer!='y' && answer!='n' && answer!='Y' && answer!='N');
	return answer;
}


int Game::AskNumber(string question, int high, int low)
{
    /* Asks player to enter number between 0-8 */
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	}while(number > high || number < low);

	return number;
}

char Game::HumanPiece(void)
{
    /* Calls AskYesNo to get the user to choose first turn or not */
	char Go_First = AskYesNo("You do want to go first? ");
	if(Go_First == 'Y' || Go_First == 'y')
	{
		cout << "First move: Human!\n";
		return X;
	}
	else
	{
		cout << "First move: Machine!\n";
		return O;
	}
}

char Game::Opponent(char piece)
{
    /* Picks the opposite of given piece, like if given is X, opponent gets 0 */
	if(piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}

void Game::DisplayBoard(const vector<char>& board)
{
    /* Displays Board */
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2]
	     << "\n\t" << "——————————"
	     << "\n\t" << board[3] << " | " << board[4] << " | " << board[5]
	     << "\n\t" << "——————————"
	     << "\n\t" << board[6] << " | " << board[7] << " | " << board[8]
	     << "\n\n";
}


char Game::Winner(const vector<char>& board)
{
    /* Loops through winning conditions to check if game won or tied */
	const int Winning_Rows[8][3] = { {0,1,2},
									 {0,4,8},
									 {0,3,6},
									 {1,4,7},
									 {2,5,8},
									 {2,4,6},
									 {3,4,5},
									 {6,7,8} };
	const int Total_Rows = 8;

	//Loops through winning conditions
	for(int row = 0; row < Total_Rows; ++row)
	{
		if ((board[Winning_Rows[row][0]] != Empty) &&
			(board[Winning_Rows[row][0]] == board[Winning_Rows[row][1]] &&
			 board[Winning_Rows[row][1]] == board[Winning_Rows[row][2]]))
		{
			return board[Winning_Rows[row][0]];
		}
	}

	//Checks for ties
	if(count(board.begin(), board.end(), Empty) == 0)
	{
		return Tie;
	}
	return No_One;
}


inline bool Game::IsLegal(const vector<char>& board, int move)
{
    /* Simply checks if a square is empty or not */
	return (board[move] == Empty);
}

int Game::HumanMove(const vector<char>& board, char human)
{
    /* Asks for a number, check's if it is legal, return's the move number */
	int move = AskNumber("Enter your move: ", (board.size()-1));
	while(!IsLegal(board, move))
	{
		cout << "\nThat Square is already occupied!\n";
		move = AskNumber("Enter your move: ", (board.size()-1));
	}
	cout << "Fine...\n";
	return move;
}

int Game::ComputerMove(vector<char>& board, char computer)
{
    /* Hardest of all, AI */
	unsigned int move = 0;
	bool found = false;

	//Check to see if computer can win in next move.
	while(!found && move < board.size())
	{
		if(IsLegal(board, move))
		{
			board[move] = computer;
			found = Winner(board) == computer;
			board[move] = Empty;
		}

		if(!found)
		{
			++move;
		}
	}

	//Check to see if player is winning.
	if (!found)
	{
		move = 0;
		char human = Opponent(computer);
		while (!found && move < board.size())
		{
			if(IsLegal(board, move))
			{
				board[move] = human;
				found = Winner(board) == human;
				board[move] = Empty;
			}
			if (!found)
			{
				++move;
			}
		}
	}

	//Move to best square
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int Best_Moves[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
		//pick best open square
		while (!found && i < board.size())
		{
			move = Best_Moves[i];
			if (IsLegal(board, move))
			{
				found = true;
			}
			++i;
		}
	}
	cout << "Computer moves to: " << move << endl;
	return move;
}

void Game::AnnounceWinner(char winner, char computer, char human)
{
    /*Checks if someone won or if it is a tie */
	if(winner == computer)
	{
		cout << "The machine won!\n";
		CompScore++;
	}

	else if(winner == human)
	{
		cout << "You won!\n";
		HumanScore++;
	}
	else
	{
		cout << "It's a tie!\n";
	}
}

void Game::PlayGame(void)
{
	int move;
	const int Num_Squares = 9; //Number of boxes
	vector<char> board(Num_Squares, Empty);

	//Welcome Player
	Instructions();

	//Allocated turns
	char human = HumanPiece();
	char computer = Opponent(human);

	char turn = X;

	//Display board and keep playing while no-one wins
	DisplayBoard(board);
	while(Winner(board)==No_One)
	{
		if(turn==human)
		{
			move = HumanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = ComputerMove(board, computer);
			board[move] = computer;
		}
		DisplayBoard(board);
		turn = Opponent(turn);
	}
	AnnounceWinner(Winner(board), computer, human);
}

