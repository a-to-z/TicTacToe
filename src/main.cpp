#include "TTTGame.h"

int main()
{
	Game game;
	char Rematch;

	do
	{
		game.PlayGame();
		Rematch = game.AskYesNo("Rematch? ");
	}while(Rematch!='N' && Rematch!='n');

	cout << "Thank you for playing Tic Tac Toe!\n";
	return 0;
}
