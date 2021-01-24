#include <stdio.h>
#include <stdlib.h>

void move();
void print_board();
int check_if_end();
void random_enemy_move();
int change_board(int *row, int *column, char player);

int is_board_full();

void fillList();
void shuffleList();

void smart_enemy_move();

char board[4][4] = 
{
    { ' ', 'a', 'b', 'c' },
    { '1', '.', '.', '.' },
    { '2', '.', '.', '.' },
    { '3', '.', '.', '.' },
};

struct Cell { int row, column; };
struct Cell list[9];

void fillList()
{
	int index = 0;
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			struct Cell cell;
			cell.row = i;
			cell.column = j;
			list[index++] = cell;
		}
	}
}

time_t t;
void shuffleList()
{
	/* Initializes random number generator */
	srand((unsigned) time(&t));
	int random_index1;
	int random_index2;

	struct Cell randomC1;
	struct Cell randomC2;

	for (int i = 0; i < 50; i++)
	{
		random_index1 = rand()%9;
		random_index2 = rand()%9;
		randomC1 = list[random_index1];
		randomC2 = list[random_index2];
		list[random_index1] = randomC2;
		list[random_index2] = randomC1;
	}
}

int main() 
{
	fillList();
	shuffleList();

    int turn = 1;
    printf("\nExamples of input: 1a; 2b; 3c etc\n");
	int result = 1;
    while (result != 0)
    {
		print_board();
		move();
		result = check_if_end();
		if (result == 0) break;
		system("clear");
        smart_enemy_move();
        result = check_if_end();
        turn++;
    }
	print_board();
    printf("\nGame ended in %d turns.\n", turn);
    return 0;
}

void print_board()
{
    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int change_board(int *row, int *column, char player)
{
	if (*row == 1 || *row == 2 || *row == 3)
	{
		if (*column == 1) board[*row][*column] = player;
		else if (*column == 2) board[*row][*column] = player;
		else if (*column == 3) board[*row][*column] = player;
		return 0;
	}
	return 1;
}

// examples of input: 1a; 2b; 1c; 3a etc...
void move()
{
    int row;
    char column;
    printf("\nyour turn: ");
    scanf("%d%c", &row, &column);
	int column_n;

	if (column == 'a') column_n = 1;
	else if (column == 'b') column_n = 2;
	else if (column == 'c') column_n = 3;

	struct Cell checking;

	for (int i = 0; i < 9; i++)
	{
		checking = list[i];
		if (checking.row != row) continue;
		else
		{
			if (checking.column != column_n) continue;
			else
			{
				change_board(&row, &column_n, 'x');		
				list[i].row = 0;
				return;
			}
		}
	}
	printf("\nYou can't move this way. Try again.\n");
	move();
}

void random_enemy_move()
{
	/* Initializes random number generator */
	srand((unsigned) time(&t));

	int random_index = rand()%9;
	struct Cell randomCell;
	randomCell.row = 0;
	randomCell.column = 0;

	while (randomCell.row == 0)
	{
		random_index = rand()%9;
		randomCell = list[random_index];
	}
	change_board(&randomCell.row, &randomCell.column, 'o');
	list[random_index].row = 0;
}

void smart_enemy_move()
{
	struct Cell cellToMove;
	cellToMove.row = 0;
	cellToMove.column = 0;
	// checking horizontal lines
	if (board[1][1] == 'x' && board[1][3] == 'x')
	{
		cellToMove.row = 1;
		cellToMove.column = 2;
	}
	else if (board[2][1] == 'x' && board[2][3] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column = 2;
	}
	else if (board[3][1] == 'x' && board[3][3] == 'x')
	{
		cellToMove.row = 3;
		cellToMove.column = 3;

	}
	// checking vertical lines
	else if (board[1][1] == 'x' && board[3][1] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column = 1;
	}
	else if (board[1][2] == 'x' && board[3][2] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column =2;
	}
	else if (board[1][3] == 'x' && board[3][3] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column = 3;

	}
	// checking diagonal lines
	else if (board[1][1] == 'x' && board[3][3] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column = 2;
	}
	else if (board[1][3] == 'x' && board[3][1] == 'x')
	{
		cellToMove.row = 2;
		cellToMove.column = 2;
	}

	struct Cell checking;
	for (int i = 0; i < 9; i++)
	{
		checking = list[i];
		if (checking.row != cellToMove.row) continue;
		else
		{
			if (checking.column != cellToMove.column) continue;
			else
			{
				change_board(&cellToMove.row, &cellToMove.column, 'o');		
				list[i].row = 0;
				return;
			}
		}
	}
	random_enemy_move();
}

int is_board_full()
{
	int empty_cells = 0;
	for (int i = 0; i < 9; i++)
	{
		if (list[i].row != 0) 
		{
			empty_cells++;
			break;
		}
	}
	return (empty_cells > 0) ? 1 : 0;
}

int check_if_end()
{
	// checking rows 
	if (board[1][1] != '.' && board[1][1] == board[1][2] && board[1][2] == board[1][3])
	{
		printf("\n%c won the game!\n", board[1][1]);
		return 0;
	}
	else if (board[2][1] != '.' && board[2][1] == board[2][2] && board[2][2] == board[2][3])
	{
		printf("\n%c won the game!\n", board[2][1]);
		return 0;
	}
	else if (board[3][1] != '.' && board[3][1] == board[3][2] && board[3][2] == board[3][3])
	{
		printf("\n%c won the game!\n", board[3][1]);
		return 0;
	}

	// checking columns
	if (board[1][1] != '.' && board[1][1] == board[2][1] && board[2][1] == board[3][1])
	{
		printf("\n%c won the game!\n", board[1][1]);
		return 0;
	}
	else if (board[1][2] != '.' && board[1][2] == board[2][2] && board[2][2] == board[3][2])
	{
		printf("\n%c won the game!\n", board[1][2]);
		return 0;
	}
	else if (board[1][3] != '.' && board[1][3] == board[2][3] && board[2][3] == board[3][3])
	{
		printf("\n%c won the game!\n", board[1][3]);
		return 0;
	}

	// checking diagonals
	if (board[1][1] != '.' && board[1][1] == board[2][2] && board[2][2] == board[3][3])
    {
        printf("\n%c won the game!\n", board[1][1]);
        return 0;
    }
    else if (board[1][3] != '.' && board[1][3] == board[2][2] && board[2][2] == board[3][1])
    {
        printf("\n%c won the game!\n", board[1][3]);
        return 0;
    }

	//checking if draw
	int board_checking = is_board_full();
	if (board_checking == 1) return 1;
	else if (board_checking == 0)
	{
		printf("\nDraw!\n");
		return 0;
	}
    return 1;
}


