#include <iostream>

using namespace std;

class chessBoard
{
private:
	char **graph;
	char **previousState;
public:
	chessBoard()
	{
		graph = new char *[8];
		for (int i = 0; i < 8; i++)
			graph[i] = new char[8];

		previousState = new char *[8];
		for (int i = 0; i < 8; i++)
			previousState[i] = new char[8];


		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0) graph[i][j] = 'w';

				else graph[i][j] = 'b';
			}
	}


	void saveState()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				previousState[i][j] = graph[i][j];
	}

	void revertToPreviousState()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				graph[i][j] = previousState[i][j];
	}

	void resetBoard()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0) graph[i][j] = 'w';

				else graph[i][j] = 'b';
			}
	}

	void printBoard()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}

	bool placeQueen(int y, int x)
	{
		if (graph[x][y] == 'Q') return false;

		for (int i = x; i > -1; i--) {
			if (graph[i][y] == 'Q') return false;
		}
		for (int i = x + 1; i < 8; i++) {
			if (graph[i][y] == 'Q')return false;
		}



		for (int i = y-1; i > -1; i--) {
			if (graph[x][i] == 'Q') return false;
		}
		for (int i = y + 1; i < 8; i++) {
			if (graph[x][i] == 'Q') return false;
		}

		int x1 = x, y1 = y;

		while (true)
		{
			x1++; y1++;
			if (x1 >= 8 | y1 >= 8) {
				x1 = x;
				y1 = y;
				break;
			}
			if (graph[x1][y1] == 'Q') return false;
		}

		while (true)
		{
			x1--; y1--;
			if (x1 < 0 | y1 < 0) {
				x1 = x;
				y1 = y;
				break;
			}
			if (graph[x1][y1] == 'Q') return false;
		}
		graph[x][y] = 'Q';
		return true;
	}


	bool tryToPlaceAtAnyPossiblePlace()
	{
		for(int i=0;i<8;i++)
			for (int j = 0; j < 8; j++)
			{
				if (placeQueen(i, j)) return true;
			}
		return false;
	}


	bool getACombination(int totalQueens,int x=0,int y=0)
	{
		int counter=0;
		while (counter < totalQueens)
		{
			if (counter == 0)placeQueen(x, y);

			if (!tryToPlaceAtAnyPossiblePlace()) {
				return 0;
			}
			counter++;
		}
		return 1;
	}

	int getTotalPossibleCombinations(int totalQueens)
	{
		int counter = 0;
		for(int i=0;i<8;i++)
			for (int j = 0; j < 8; j++)
			{
				if (getACombination(totalQueens, i, j))
				{
					counter++;
					cout << endl;
					printBoard();
					cout << endl;   
				}
				resetBoard();
			}
		return counter;
	}
};



