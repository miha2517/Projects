#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool LoseRound;
int Width = 20;
int Height = 20;
int x, y, mouseX, mouseY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { Stop = 0, Up, Down, Left, Right };
eDirecton dir;

class Settings
{
	public:
		void SettingsGame()
		{
			LoseRound = false;
			dir = Stop;
			x = Width / 2;
			y = Height / 2;
			mouseX = (rand() % (Width - 1)) + 1;
			mouseY = (rand() % (Height - 1)) + 1;
			score = 0;
		}
};

class Rendering:Settings
{
	public:
		void RenderingBox()
		{
			system("cls");
			for (int i = 0; i < Width + 1; i++)
				cout << "#";
			cout << endl;

			for (int i = 0; i < Height; i++)
			{
				for (int r = 0; r < Width; r++)
				{
					if (r == 0)
						cout << "#";
					if (i == y && r == x)
						cout << "O";
					else if (i == mouseY && r == mouseX)
						cout << "*";
					else
					{
						bool print = false;
						for (int k = 0; k < nTail; k++)
						{
							if (tailX[k] == r && tailY[k] == i)
							{
								cout << "o";
								print = true;
							}
						}
						if (!print)
							cout << " ";
					}
					if (r == Width - 1)
						cout << "#";
				}
				cout << endl;
			}
			for (int i = 0; i < Width + 2; i++)
				cout << "#";
			cout << endl;
			cout << "Score:" << score << endl;
		}
};

class Сontrol:Settings
{
	public:
		void ControlGame()
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 'a':
					dir = Left;
					break;
				case 'd':
					dir = Right;
					break;
				case 'w':
					dir = Up;
					break;
				case 's':
					dir = Down;
					break;
				case 'x':
					LoseRound = true;
					break;
				}
			}
		}
};

class Logic:Settings
{
	public:
		void LogicGame()
		{
			int prevX = tailX[0];
			int prevY = tailY[0];
			int prev2X, prev2Y;
			tailX[0] = x;
			tailY[0] = y;
			for (int i = 1; i < nTail; i++)
			{
				prev2X = tailX[i];
				prev2Y = tailY[i];
				tailX[i] = prevX;
				tailY[i] = prevY;
				prevX = prev2X;
				prevY = prev2Y;
			}
			switch (dir)
			{
			case Left:
				x--;
				break;
			case Right:
				x++;
				break;
			case Up:
				y--;
				break;
			case Down:
				y++;
				break;
			default:
				break;
			}
			if (x >= Width) x = 0; else if (x < 0) x = Width - 1;
			if (y >= Height) y = 0; else if (y < 0) y = Height - 1;
			for (int i = 0; i < nTail; i++)
				if (tailX[i] == x && tailY[i] == y)
					LoseRound = true;
			if (x == mouseX && y == mouseY)
			{
				score += 10;
				mouseX = rand() % Width;
				mouseY = rand() % Height;
				nTail++;
			}
		}
};

int main()
{
	Settings SettingGame1;
	SettingGame1.SettingsGame();
	Rendering RenderingBox1;
	Сontrol ControlSnake;
	Logic LogicSnake;
	
	while (!LoseRound)
	{
		RenderingBox1.RenderingBox();
		ControlSnake.ControlGame();
		LogicSnake.LogicGame();
		Sleep(10);
	}
	return 0;
}


