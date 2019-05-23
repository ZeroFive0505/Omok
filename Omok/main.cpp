#include "pch.h"
#include "omok.h"

int main()
{
	Initialize();

	while (1)
	{
		for (int i = 0; i < 5; i++)
			Control();

		DrawBoard();
		if (game_end)
			GameOver();
	}

	return 0;
}