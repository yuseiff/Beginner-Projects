#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;

void Shift_Right(int arr[], int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}

//----------------------------Properties-----------------------//
enum enDirection { Top = 1, Down, Right, Left };

struct Map
{
	int Height, width, fruitX, fruitY;
};

struct Snake
{
	int HeadX, HeadY, Tail_N, Tail_X[50], Tail_Y[50];
	char Dir;
	bool Tail_P;
};

struct Player
{
	int score;
	bool lose;
};
//-------------------------------------------------------------//

Map Map1;
Snake Snake1;
Player Player1;

void Line()
{
	for (int i = 0; i <= 40; i++)
	{
		cout << "*";
	}
	//cout << endl;
}

void GenerateFruit()
{
	srand(time(NULL));
	Map1.fruitX = rand() % (Map1.width - 2) + 1;//1 to 38
	Map1.fruitY = rand() % (Map1.Height - 2) + 1;//1 to 18
}

void Setup()
{

	Map1.width = 40;
	Map1.Height = 20;
	GenerateFruit();
	//-----------------------------------------------------------

	Snake1.HeadX = Map1.width / 2;
	Snake1.HeadY = Map1.Height / 2;
	Snake1.Tail_N = 0;

	//------------------------------------------------------------
	Player1.score = 0;
	Player1.lose = false;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < Map1.Height; i++)
	{
		for (int j = 0; j < Map1.width; j++)
		{
			if (i == 0 || i == Map1.Height - 1)
			{
				cout << "*";
			}

			else if (j == 0 || j == Map1.width - 1)
			{
				cout << "*";
			}

			else if (i == Snake1.HeadY && j == Snake1.HeadX)
			{
				cout << "O";
			}

			else if (i == Map1.fruitY && j == Map1.fruitX)
			{
				cout << "$";
			}

			else
			{
				Snake1.Tail_P = false;

				for (int z = 0; z < Snake1.Tail_N; z++)
				{
					if (Snake1.Tail_X[z] == j && Snake1.Tail_Y[z] == i)
					{
						cout << "o";
						Snake1.Tail_P = true;
						break;
					}
				}

				if (!Snake1.Tail_P)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << "Player score: " << Player1.score << endl;
}

void Input()
{
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case'w':
			Snake1.Dir = Top;
			break;

		case 'a':
			Snake1.Dir = Left;
			break;

		case'd':
			Snake1.Dir = Right;
			break;

		case 's':
			Snake1.Dir = Down;
			break;

		case 'x':
			//system("cls");
			exit(0);
		}
	}
}

void GameOver()
{
	system("cls");

	Line();
	cout << "\tGame over\t";
	Line();
	cout << endl;

	system("color 4F");
	Player1.lose = true;
}

void Move()
{
	Shift_Right(Snake1.Tail_X, 50);
	Shift_Right(Snake1.Tail_Y, 50);
	Snake1.Tail_X[0] = Snake1.HeadX;
	Snake1.Tail_Y[0] = Snake1.HeadY;


	switch (Snake1.Dir)
	{
	case Top:
		Snake1.HeadY--;
		break;

	case Down:
		Snake1.HeadY++;
		break;

	case Left:
		Snake1.HeadX--;
		break;

	case Right:
		Snake1.HeadX++;
		break;
	}

	if (Snake1.HeadX == 0 || Snake1.HeadX == Map1.width)
	{
		GameOver();
	}

	else if (Snake1.HeadY == 0 || Snake1.HeadY == Map1.Height)
	{
		GameOver();
	}

	if (Snake1.HeadX == Map1.fruitX && Snake1.HeadY == Map1.fruitY)
	{
		GenerateFruit();
		Player1.score = Player1.score + 1;
		Snake1.Tail_N++;
	}

	for (int y = Snake1.Tail_N; y >= 3; y--)
	{

		if (Snake1.HeadX == Snake1.Tail_X[y] && Snake1.HeadY == Snake1.Tail_Y[y])
		{
			GameOver();
		}
	}
}



int main()
{
	system("Pasue");

	system("color 0a");
	Setup();
	while (Player1.lose == false)
	{
		Draw();
		Input();
		Move();
		Sleep(80);
	}
}