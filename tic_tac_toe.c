#include <stdio.h>
#include <stdlib.h>

void move();
void print_board();
int check_if_end();
void enemy_move();
int change_board(int *row, char *column, char player);

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
        move();
		system("clear");
        enemy_move();
        result = check_if_end();
        turn++;
    }
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

int change_board(int *row, char *column, char player)
{
	if (*row == 1 || *row == 2 || *row == 3)
	{
		if (*column == 'a') board[*row][1] = player;
		else if (*column == 'b') board[*row][2] = player;
		else if (*column == 'c') board[*row][3] = player;
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

    if (board[row][column] == 'x' || board[row][column] == 'o')
    {
        printf("\nYou can't move this way. Try again.\n");
        move();
    }
	else if (change_board(&row, &column, 'x') != 0)
	{
		printf("\nIncorrect input. Try again.\n");
		move();
	}
}

time_t t;
void enemy_move()
{
	/* Initializes random number generator */
	srand((unsigned) time(&t));
	char column;

	int row;
	int n_column;

	row = rand()%3+1;
	n_column = rand()%3+1;

	if (n_column == 1) column = 'a';
	else if (n_column == 2) column = 'b';
	else if (n_column == 3) column = 'c';

    if (board[row][column] == 'x' || board[row][column] == 'o')
    {
        enemy_move();
    }
    else
    {
	    change_board(&row, &column, 'o');
    }
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
        printf("\n%c won the game!\n", board[1][3]);
        return 0;
    }
    else if (board[1][3] != '.' && board[1][3] == board[2][2] && board[2][2] == board[3][1])
    {
        printf("\n%c won the game!\n", board[1][3]);
        return 0;
    }
    return 1;
}
