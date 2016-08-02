#include <iostream>

using namespace std;

class chessBoard
{
private:
	char **graph; //Chess Board Container
	
public:
	chessBoard() //Making graph variable a chess matrix (8 x 8)
	{
		graph = new char *[8];
		for (int i = 0; i < 8; i++)
			graph[i] = new char[8];

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0) graph[i][j] = 'w';

				else graph[i][j] = 'b';
			}
	}

	~chessBoard() //Delete Chess Board
	{
		delete graph;
	}


	void resetBoard() //Removing all queens from the board
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0) graph[i][j] = 'w';

				else graph[i][j] = 'b';
			}
	}

	void printBoard() // Prints Current Condition of the queen
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

	bool placeQueen(int y, int x) //Tries to place queen to given position. If the Queen Gets Attacked By other queen then the function will return false and wont place the queen
	{
		if (graph[x][y] == 'Q') return false;

		for (int i = x; i > -1; i--) {
			if (graph[i][y] == 'Q') return false;
		}
		for (int i = x + 1; i < 8; i++) {
			if (graph[i][y] == 'Q')return false;
		}



		for (int i = y - 1; i > -1; i--) {
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


		while (true)
		{
			x1--; y1++;
			if (x1 < 0 | y1 >= 8) {
				x1 = x;
				y1 = y;
				break;
			}
			if (graph[x1][y1] == 'Q') return false;
		}

		while (true)
		{
			x1++; y1--;
			if (x1 >7  | y1 < 0) {
				x1 = x;
				y1 = y;
				break;
			}
			if (graph[x1][y1] == 'Q') return false;
		}

		graph[x][y] = 'Q';
		return true;
	}

	bool tryToPlaceAtAnyPossiblePlace() //Tries to place to queen at any safe position if possible. If not possible, it will return false
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (placeQueen(i, j)) return true;
			}
		return false;
	}

	bool getACombination(int totalQueens, int x = 0, int y = 0) //I takes the position of the first queen and Tries to get a combination N number of unattacked Queens. 
	{
		int counter = 0;
		while (counter < totalQueens)
		{
			if (counter == 0)placeQueen(x, y);

			if (!tryToPlaceAtAnyPossiblePlace()) {
				return false;
			}
			counter++;
		}
		return true;
	}

	int getTotalPossibleCombinations(int totalQueens) //Tries to get all possible combinations of N number of queens
	{
		int counter = 0;
		for (int i = 0; i<8; i++)
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



int main()
{
	chessBoard cb;
	int totalQueen;
	cout << "Total Queens to place :";
	cin >> totalQueen;
	totalQueen--;
	cout << "Total Possible combinations: " << cb.getTotalPossibleCombinations(totalQueen) << endl;
	
}