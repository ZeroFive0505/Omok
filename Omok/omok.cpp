#include "pch.h"
#include "omok.h"

STAT Buffer[SIZE][SIZE];
STAT Screen[SIZE][SIZE];
bool black_turn;
int cur_x;
int cur_y;
bool game_end;

void GotoXY(int x, int y)
{
	COORD new_coord = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), new_coord);
}


void Initialize()
{
	black_turn = true;
	game_end = false;
	cur_x = SIZE / 2;
	cur_y = SIZE / 2;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			Buffer[i][j] = Screen[i][j] = EMPTY;
			GotoXY(j, i);
			printf("¡à");
		}
	}

}

void DrawBoard()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Buffer[i][j] != Screen[i][j])
			{
				Screen[i][j] = Buffer[i][j];
				switch (Screen[i][j])
				{
				case EMPTY :
					GotoXY(j, i);
					printf("¡à");
					break;
				case SELECTED :
					GotoXY(j, i);
					printf("¢È");
					break;
				case BLACK :
					GotoXY(j, i);
					printf("¡Û");
					break;
				case WHITE :
					GotoXY(j, i);
					printf("¡Ü");
					break;
				}
			}
		}
	}

	Checking();

	GotoXY(20, 10);
	if (black_turn)
		printf("BLACK's turn");
	else
		printf("WHITE's turn");
}

void Control()
{
	int key;

	if (_kbhit())
	{
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case UP :
				Move(0, -1);
				break;
			case DOWN :
				Move(0, 1);
				break;
			case LEFT :
				Move(-1, 0);
				break;
			case RIGHT :
				Move(1, 0);
				break;
			}
		}
		else if (key == SPACE)
		{
			if (black_turn)
				Buffer[cur_y][cur_x] = BLACK;
			else
				Buffer[cur_y][cur_x] = WHITE;
			black_turn = !black_turn;


			cur_x = SIZE / 2; //Reset pos
			cur_y = SIZE / 2; //Reset pos
		}
	}
}

void Move(int x, int y)
{
	if (Boundary(cur_x + x, cur_y + y))
		return;
	if (Buffer[cur_y + y][cur_x + x] == EMPTY)
	{
		Buffer[cur_y + y][cur_x + x] = SELECTED;
		if(Buffer[cur_y][cur_x] == SELECTED)
			Buffer[cur_y][cur_x] = EMPTY;
	}
	else if (Buffer[cur_y + y][cur_x + x] == BLACK
		|| Buffer[cur_y + y][cur_x + x] == WHITE)
	{
		if (Buffer[cur_y][cur_x] == SELECTED)
			Buffer[cur_y][cur_x] = EMPTY;
	}

	cur_x += x;
	cur_y += y;
}

bool Boundary(int x, int y)
{
	if (x >=SIZE || y >= SIZE)
		return true;
	else if (x < 0 || y < 0)
		return true;
	else
		return false;
}

void Checking()
{
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Screen[i][j] == WHITE || Screen[i][j] == BLACK)
				Chain_check(i, j);
		}
	}
}

void Chain_check(int row, int col) // Total 8 Directions to check
{

	int count = 0;
	int i, j;
	for (i = row; i < SIZE; i++) // Horizontal + direcion
	{
		if (count == 4)
			game_end = true;

		if (Boundary(i, col))
			break;

		if (Screen[i][col] != EMPTY && Screen[i][col] == Screen[i + 1][col])
			count++;
		else 
			break;
	}

	count = 0;

	for (i = row; i>0; i--) // Horizontal - direction
	{
		if (count == 4)
			game_end = true;

		if (Boundary(i, col))
			break;

		if (Screen[i][col] != EMPTY && Screen[i][col] == Screen[i - 1][col])
			count++;
		else
			break;
	}

	count = 0;

	for (j = col; j<SIZE; j++) // Vertical + direction
	{
		if (count == 4)
			game_end = true;

		if (Boundary(row, j))
			break;

		if (Screen[row][j] != EMPTY && Screen[row][j] == Screen[row][j+1])
			count++;
		else
			break;
	}

	count = 0;

	for (j = col; j>0; j--) // Vertical - direcion
	{
		if (count == 4)
			game_end = true;

		if (Boundary(row, j))
			break;

		if (Screen[row][j] != EMPTY  && Screen[row][j] == Screen[row][j + 1])
			count++;
		else
			break;
	}

	count = 0;

	for (i = row; i<SIZE; i++) // Diagonal + direction
	{
		for (j = col; j<SIZE; j++)
		{
			if (count == 4)
				game_end = true;

			if (Boundary(i, j))
				break;

			if (Screen[i][j] != EMPTY  && Screen[i][j] == Screen[i + 1][j + 1])
				count++;
		}
	}

	count = 0;

	for (i = row; i>0; i--) // Diagonal - direction
	{
		for (j = col; j>0; j--)
		{
			if (count == 4)
				game_end = true;

			if (Boundary(i, j))
				break;

			if (Screen[i][j] != EMPTY && Screen[i][j] == Screen[i - 1][j - 1])
				count++;
		}
	}

	count = 0;


	for (i = row; i>0; i--) // Another diagonal direction i--, j++
	{
		for (j = col; j<SIZE; j++)
		{
			if (count == 4)
				game_end = true;

			if (Boundary(i, j))
				break;

			if (Screen[i][j] != EMPTY && Screen[i][j] == Screen[i - 1][j + 1])
				count++;
		}
	}

	count = 0;


	for (i = row; i<SIZE; i++) // Another diagonal direction i++, j--
	{
		for (j = col; j>0; j--)
		{
			if (count == 4)
				game_end = true;

			if (Boundary(i, j))
				break;

			if (Screen[i][j] != EMPTY && Screen[i][j] == Screen[i + 1][j - 1])
				count++;
		}
	}
}


void GameOver()
{
	int key;
	GotoXY(20, 10);
	if (black_turn)
		printf("White win!!!");
	else
		printf("Black win!!!");
	GotoXY(30, 15);
	printf("\nPress any key to continue!\n");
	printf("q to exit this game");
	game_end = false;
	while (_kbhit())
		_getch();
	key = _getch();

	if (key == 'q')
		exit(EXIT_SUCCESS);
	else
		Initialize();
}