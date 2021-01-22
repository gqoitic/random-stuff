#include <stdio.h>
#include <stdlib.h>

int move();
void print_board();
int check_if_end();
int enemy_move();
int change_board(int *row, int *column, char player);

void move_with_checking();
void enemy_move_with_checking();

int is_board_full();

char board[4][4] = 
{
    { ' ', 'a', 'b', 'c' },
    { '1', '.', '.', '.' },
    { '2', '.', '.', '.' },
    { '3', '.', '.', '.' },
};

int main() 
{
    int turn = 1;
    printf("\nExamples of input: 1a; 2b; 3c etc\n");
	int result = 1;
    while (result != 0)
    {
		print_board();
        move_with_checking();
		result = check_if_end();
		if (result == 0) break;
		system("clear");
        enemy_move_with_checking();
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
int move()
{
    int row;
    char column;
    printf("\nyour turn: ");
    scanf("%d%c", &row, &column);
	int column_n;

	if (column == 'a') column_n = 1;
	else if (column == 'b') column_n = 2;
	else if (column == 'c') column_n = 3;

	if (board[row][column_n] != '.')
    {
        printf("\nYou can't move this way. Try again.\n");
        return 1;
    }
	else if (change_board(&row, &column_n, 'x') != 0)
	{
		printf("\nIncorrect input. Try again.\n");
		return 1;
	}
	change_board(&row, &column_n, 'x');
	return 0;
}

void move_with_checking()
{
	int correctMove = move();
	while (correctMove != 0)
	{
		correctMove = move();
	}
}

time_t t;
int enemy_move()
{
	/* Initializes random number generator */
	srand((unsigned) time(&t));

	int row;
	int column_n;

	row = rand()%3+1;
	column_n = rand()%3+1;

    if (board[row][column_n] != '.')
    {
        return 1;
    }
    else
    {
	    change_board(&row, &column_n, 'o');
		return 0;
    }
}

// TODO: fix 
void enemy_move_with_checking()
{
	int correctMove = enemy_move();
	while (correctMove != 0)
	{
		printf("randoming enemy's turn (obviously needs to be fixed)\n");
		correctMove = enemy_move();
	}
}

int is_board_full()
{
	int empty_cells = 9;
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (board[i][j] != '.') empty_cells--;
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


