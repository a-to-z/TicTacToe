#ifndef TTTGAME_H_
#define TTTGAME_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Game
{
	private:
		const char X='X';
		const char O='O';
		const char Empty = ' ';
		const char Tie = 'T';
		const char No_One = 'N';
		int HumanScore = 0;
		int CompScore = 0;

	public:
		void Instructions(void);
		char AskYesNo(string question);
		int AskNumber(string question, int high, int low=0);
		char HumanPiece(void);
		char Opponent(char piece);
		void DisplayBoard(const vector<char>& board);
		char Winner(const vector<char>& board);
		inline bool IsLegal(const vector<char>& board, int move);
		int HumanMove(const vector<char>& board, char human);
		int ComputerMove(vector<char>& board, char computer);
		void AnnounceWinner(char winner, char computer, char human);
		void PlayGame(void);
		Game();
};

#endif
