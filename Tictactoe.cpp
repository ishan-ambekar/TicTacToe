#include<iostream>
#include<algorithm>

using namespace std;

class Move
{
public:
	int row, col,mov;
	char mat[3][3];
	bool isMovesLeft();
	int evaluate();
	Move minimax();
	void initialize();
	int get_move(int n);
	int comp_move();
	void display();
	int maxSearch();
	int minSearch();
};

char player = 'X', opponent = 'O';
void Move::display()
{
	cout << "\t\t\t" << mat[0][0] << "  | " << mat[0][1] << "  | " << mat[0][2] << endl;
	cout << "\t\t\t" << "------------" << endl;
	cout << "\t\t\t" << mat[1][0] << "  | " << mat[1][1] << "  | " << mat[1][2] << endl;
	cout << "\t\t\t" << "------------" << endl;
	cout << "\t\t\t" << mat[2][0] << "  | " << mat[2][1] << "  | " << mat[2][2] << endl;
	cout << endl;
}
void Move::initialize()
{
	int i, j;
	mov = 0;
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
			mat[i][j] = ' '; //reset every position
	}
	cout << endl;
}
int Move::get_move(int n)
{
	int tempr, tempc;
	tempr = (n - 1) / 3; //calculating row index
	tempc = (n - 1) % 3; //calculating column index
	if (mat[tempr][tempc] == ' ')
	{
		mat[tempr][tempc] = 'X'; //store player move
		mov++;
		cout << endl;
		return 1;
	}
	else
	{
		cout << "The position is already chosen, please choose a different position" << endl;
		return 0;
	}
}
int Move::comp_move()
{
	Move bestMove = minimax();
	int r = bestMove.row;
	int c = bestMove.col;
	if (mat[r][c] == ' ')
	{
		mat[r][c] = 'O'; //store comp move
		mov++;
		cout << endl;
		return 1;
	}
	
}
// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool Move::isMovesLeft()
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (mat[i][j] == ' ')
				return true;
	return false;
}


int Move::evaluate()
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		if (mat[row][0] == mat[row][1] &&
			mat[row][1] == mat[row][2])
		{
			if (mat[row][0] == player)
				return +10;
			else if (mat[row][0] == opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (mat[0][col] == mat[1][col] &&
			mat[1][col] == mat[2][col])
		{
			if (mat[0][col] == player)
				return +10;

			else if (mat[0][col] == opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (mat[0][0] == mat[1][1] && mat[1][1] == mat[2][2])
	{
		if (mat[0][0] == player)
			return +10;
		else if (mat[0][0] == opponent)
			return -10;
	}

	if (mat[0][2] == mat[1][1] && mat[1][1] == mat[2][0])
	{
		if (mat[0][2] == player)
			return +10;
		else if (mat[0][2] == opponent)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
// This will return the best possible move for the player
Move Move::minimax()
{
	int bestMoveScore = 100; // -100 is arbitrary
	Move bestMove;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j] == ' ') {
				mat[i][j] = opponent;
				int tempMoveScore = maxSearch();
				if (tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.row = i;
					bestMove.col = j;
				}
				mat[i][j] = ' ';
			}
		}
	}

	return bestMove;
}

int Move::maxSearch() {
	int score = evaluate();
	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (isMovesLeft() == false)
		return 0;
	Move bestMove;

	int bestMoveScore = -1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j] == ' ') {
				mat[i][j] = player;
				int tempMoveScore = minSearch();
				if (tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.row = i;
					bestMove.col = j;
				}
				mat[i][j] = ' ';
			}
		}
	}

	return bestMoveScore;
}
int Move::minSearch() {
	int score = evaluate();
	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (isMovesLeft() == false)
		return 0;
	Move bestMove;

	int bestMoveScore = 1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j] == ' ') {
				mat[i][j] = opponent;
				int tempMove = maxSearch();
				if (tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.row = i;
					bestMove.col = j;
				}
				mat[i][j] = ' ';
			}
		}
	}

	return bestMoveScore;
}



// Driver code
int main()
{
	int i, j, temp = 10,pos;
	Move obj, obj1;
	obj.initialize();
	obj.display();
	while (temp > 0)
	{
		cout << endl;
		if (temp % 2 == 0)
		{
			cout <<"Enter the position at which the move is to be played:" << endl;
			cin >> pos;
			j = obj.get_move(pos);
			while (j == 0)
			{
				cout << "Enter the position at which the move is to be played:" << endl;
				cin >> pos;
				j = obj.get_move(pos);
			}
			i = obj.evaluate();
			if (i == 10)
			{
				cout << "Player wins" << endl;
				obj.display();
				break;
			}
			else if (i == -10)
			{
				cout << "Computer wins" << endl;
				obj.display();
				break;
			}
			else if (i == 0 && temp==1)
			{
				cout << "Game Over" << endl;
				obj.display();
				break;
			}
			obj.display();
			cout << endl;
			temp--;
		}
		if (temp % 2 != 0)
		{
			i = obj.evaluate();
			if (i == 10)
			{
				cout << "Player wins" << endl;
				obj.display();
				break;
			}
			else if (i == -10)
			{
				cout << "Computer wins" << endl;
				obj.display();
				break;
			}
			else if (i == 0 && temp == 1)
			{
				cout << "Game Over, it's a draw. :(" << endl;
				obj.display();
				break;
			}
			cout << "Computer plays" << endl;
			obj.comp_move();
			obj.display();
			cout << endl;
			temp--;
		}
	}
	
	return 0;
}
