#include <iostream>
#include <Windows.h> // just for animations 
#include <stack> // for depth first search 
#include <queue>	// for breadth first search 
#define ROWS 10 
#define COLS 10
#define frameDelay 300  // delay between each frame of animation 
using namespace std; 

enum State {EMPTY, VISITED, TARGET}; // the state that each node might be in  
void printGrid(int grid[ROWS][COLS])
{
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int i = 0; i < COLS; i++)
		{
			cout << "----";

		}cout << endl;
		for (int j = 0; j < COLS; j++)
		{
			if (grid[i][j] == EMPTY) // empty 
			{		
				cout << "|   ";
			}
			else if(grid[i][j] == VISITED ) // visited 
			{
				cout << "| O "; 
			}
			else// target
			{
				cout << "| X ";
			}

		}
		cout << endl; 
	}
	for (int i = 0; i < COLS; i++)
	{
		cout << "----";

	}cout << endl;
}

struct Coordinates
{
	int row, col; 
	Coordinates(int row, int col)
	{
		this->row = row; 
		this->col = col; 
	}
};
void breadthFirstSearch(int grid[ROWS][COLS])
{
	system("cls"); // clear console 
	queue<Coordinates> nodeQueue;
	nodeQueue.push(Coordinates(0, 0));  // we start at (0,0); the top left of the grid ; 
	grid[0][0] = VISITED; 
	bool targetFound = false; 
	while (!nodeQueue.empty() && !targetFound) // while there are still nodes to visited 
	{
		system("cls"); // clear console 
		// pop current node ; 
		Coordinates currentNode = nodeQueue.front();  // takes the node from the front 
		nodeQueue.pop(); // pops the node from queue 
		// check if this currentNode is the goal if so stop 

		

		// add adjacent nodes 
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == j) // don't add itself twice and dont add diagonals 
				{
					continue; 
				}
				// check if it is a valid grid point 
				int newRow = currentNode.row + i; 
				int newCol = currentNode.col + j; 
				if (newRow >= 0 && newRow < ROWS)
				{
					if (newCol >= 0 && newCol < COLS)
					{
						// meaning the coordinate exists 
						// now check if it is already visited 
						// check if it is the target first 
						if (grid[newRow][newCol] == TARGET)
						{
							cout << "Target Found!" << endl;
							targetFound = true; 
							break;
							
						}
						else if (grid[newRow][newCol] != VISITED) {
							grid[newRow][newCol] = VISITED; 
							nodeQueue.push(Coordinates(newRow, newCol));
						}
					}
				}
			}
		}
		
		
		//now redraw onto console 
		printGrid(grid);
		Sleep(frameDelay);
		
		
	}
}
int main()
{

	int grid[ROWS][COLS] = { 0 }; 
	int targetRow, targetCol; 
	cout << "Which row and column of the " << ROWS << "x" << COLS << " grid would you like the target to start on?" << endl; 
	cout << "Enter row (0-"<<ROWS-1<<"): "; 
	cin >> targetRow;
	cout << "Enter col (0-" << COLS - 1 << "): ";
	cin >> targetCol;

	grid[targetRow][targetCol] = TARGET; 

	// now commence breadth first search and depth first search
	cout << "Commencing Breadth First Search ... " << endl; 

	Sleep(1500); 

	 
	breadthFirstSearch(grid); 

	

	 
}