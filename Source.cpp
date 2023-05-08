#include <iostream>
#include <iomanip>
#include <Windows.h> // just for animations 
#include <stack> // for depth first search 
#include <queue>	// for breadth first search 
#define ROWS 10 
#define COLS 10
#define frameDelay 125  // delay between each frame of animation 
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
int  breadthFirstSearch(int grid[ROWS][COLS])
{
	system("cls"); // clear console 
	queue<Coordinates> nodeQueue;
	nodeQueue.push(Coordinates(0, 0));  // we start at (0,0); the top left of the grid ; 
	grid[0][0] = VISITED; 
	bool targetFound = false; 
	int iterations = 0; // this is the iterations; we can use this to see how efficient the algorithm was at finding the target
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
		
		iterations++; 
		//now redraw onto console 
		printGrid(grid);
		Sleep(frameDelay);
		
		
	}
	return iterations; 
}
int  depthFirstSearch(int grid[ROWS][COLS])
{
	system("cls"); // clear console 
	bool targetFound = false;
	stack<Coordinates> nodeStack;
	nodeStack.push(Coordinates(0, 0));  // we start at (0,0); the top left of the grid ; 
	grid[0][0] = VISITED;

	int iterations = 0; // this is the iterations; we can use this to see how efficient the algorithm was at finding the target
	while (!nodeStack.empty() && !targetFound) // while there are still nodes to visited 
	{
		system("cls"); // clear console 
		// pop current node ; 
		Coordinates currentNode = nodeStack.top();  // takes the node from the front 
		nodeStack.pop(); // pops the node from queue 
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
							nodeStack.push(Coordinates(newRow, newCol));
						}
					}
				}
			}
		}

		iterations++; 
		//now redraw onto console 
		printGrid(grid);
		Sleep(frameDelay);


	}
	return iterations;

}

void reset(int grid[ROWS][COLS] ,int trow , int tcol)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == trow && j == tcol) {
				grid[i][j] = TARGET;
			}
			else
			{
				grid[i][j] = EMPTY;

			}
		}
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

	 
	int bfsIterations = breadthFirstSearch(grid); 
	cout << "BFS Took " << bfsIterations << " iterations to find the target" << endl; 
	
	Sleep(1500); 


	// reset grid; 
	reset(grid, targetRow , targetCol); 
	system("cls"); 
	cout << "Commencing Depth First Search ... " << endl;

	Sleep(1500);
	int dfsIterations = depthFirstSearch(grid);
	cout << "DFS Took " << dfsIterations << " iterations to find the target" << endl;

	Sleep(1500);

	system("cls"); 

	cout << setw(6) << "BFS" << setw(6) << "DFS" << endl;
	cout << setw(6) << "------" << setw(6) << "---------" << endl;

	cout << setw(6) << bfsIterations <<" |" << setw(6) << dfsIterations << endl;








	

	 
}