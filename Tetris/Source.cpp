#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define GAME_WIDTH 31

#define TRIANGLE 2, 2, 1, 2, 3, 2, 2, 1
#define LINE 0, 2, 1, 2, 2, 2, 3, 2
#define CUBE 0, 2, 1, 2, 0, 1, 1, 1
#define S_BLOCK 2, 2, 1, 2, 2, 1, 3, 1
#define Z_BLOCK 3, 2, 4, 2, 2, 1, 3, 1
#define L_BLOCK 2, 1, 2, 2, 2, 3, 3, 3
#define RL_BLOCK 2, 1, 2, 2, 2, 3, 1, 3

uint32_t data[26];
uint16_t score = 0;

#define posX1 pos[0]
#define posX2 pos[1]
#define posX3 pos[2]
#define posX4 pos[3]

#define posY1 pos[4]
#define posY2 pos[5]
#define posY3 pos[6]
#define posY4 pos[7]

char index = 0;
char a = '0';

struct Block
{
	char* pos = (char*)malloc(8);

	~Block()
	{
		if (pos != NULL) 
		{
			free(pos);
			pos = NULL;
		}
	}

	void SpawnBlock(const char& _x1, const char& _y1, const char& _x2, const char& _y2, const char& _x3, const char& _y3, const char& _x4, const char& _y4)
	{
		posX1 = _x1;
		posX2 = _x2;
		posX3 = _x3;
		posX4 = _x4;

		posY1 = _y1;
		posY2 = _y2;
		posY3 = _y3;
		posY4 = _y4;

		data[_y1] |= 0x1 << _x1;
		data[_y2] |= 0x1 << _x2;
		data[_y3] |= 0x1 << _x3;
		data[_y4] |= 0x1 << _x4;
	}

	void SpawnRandomBlock()
	{

		srand(index);
		switch (rand() % 7)
		{
		case 0:
			SpawnBlock(LINE);
			break;
		case 1:
			SpawnBlock(TRIANGLE);
			break;
		case 2:
			SpawnBlock(CUBE);
			break;
		case 3:
			SpawnBlock(S_BLOCK);
			break;
		case 4:
			SpawnBlock(Z_BLOCK);
			break;
		case 5:
			SpawnBlock(L_BLOCK);
			break;
		case 6:
			SpawnBlock(RL_BLOCK);
			break;
		}
	}

	void MoveSideWays(const char& a)
	{
		if (posY1 < 25 && posY2 < 25 && posY3 < 25 && posY4 < 25) {
			if (posX1 > 0 && posX2 > 0 && posX3 > 0 && posX4 > 0 && a < 0 ||
				a > 0 && posX1 < GAME_WIDTH - 1 && posX2 < GAME_WIDTH - 1 && posX3 < GAME_WIDTH - 1&& posX4 < GAME_WIDTH - 1)
			{
				data[posY1] &= ~(0x1 << posX1);
				data[posY2] &= ~(0x1 << posX2);
				data[posY3] &= ~(0x1 << posX3);
				data[posY4] &= ~(0x1 << posX4);

				posX1 += a;
				posX2 += a;
				posX3 += a;
				posX4 += a;

				data[posY1] |= 0x1 << posX1;
				data[posY2] |= 0x1 << posX2;
				data[posY3] |= 0x1 << posX3;
				data[posY4] |= 0x1 << posX4;
			}
		}
	}
	
	bool CanMoveSideWays(const char& a)
	{
		if (posX1 > 0 && posX2 > 0 && posX3 > 0 && posX4 > 0 && a < 0 ||
			a > 0 && posX1 < GAME_WIDTH - 1 && posX2 < GAME_WIDTH - 1 && posX3 < GAME_WIDTH - 1 && posX4 < GAME_WIDTH - 1)
		{
			return true;
		}

		return false;
	}

	void Rotate(void)
	{
		char tmpX, tmpY;

		data[posY2] &= ~(0x1 << posX2);

		tmpX = -(posY2 - posY1);
		tmpY = (posX2 - posX1);

		posX2 = tmpX + posX1;
		posY2 = tmpY + posY1;

		data[posY3] &= ~(0x1 << posX3);
		
		tmpX = -(posY3 - posY1);
		tmpY = (posX3 - posX1);

		posX3 = tmpX + posX1;
		posY3 = tmpY + posY1;

		data[posY4] &= ~(0x1 << posX4);

		tmpX = -(posY4 - posY1);
		tmpY = (posX4 - posX1);

		posX4 = tmpX + posX1;
		posY4 = tmpY + posY1;

		data[posY1] |= 0x1 << posX1;
		data[posY2] |= 0x1 << posX2;
		data[posY3] |= 0x1 << posX3;
		data[posY4] |= 0x1 << posX4;
	}

	int MoveDown(void)
	{
		if (posY1 < 25 && posY2 < 25 && posY3 < 25 && posY4 < 25 &&
			CanMoveDown(posX1, posY1) &&
			CanMoveDown(posX2, posY2) &&
			CanMoveDown(posX3, posY3) &&
			CanMoveDown(posX4, posY4))
		{
			data[posY1] &= ~(0x1 << posX1);
			data[posY2] &= ~(0x1 << posX2);
			data[posY3] &= ~(0x1 << posX3);
			data[posY4] &= ~(0x1 << posX4);

			posY1++;
			posY2++;
			posY3++;
			posY4++;

			data[posY1] |= 0x1 << posX1;
			data[posY2] |= 0x1 << posX2;
			data[posY3] |= 0x1 << posX3;
			data[posY4] |= 0x1 << posX4;
		}

		else
		{
			if (posY1 <= 2)
			{
				return 0;
			}

			SpawnRandomBlock();
		}

		return 1;
	}

	bool CanMoveDown(const char& posX, const char& posY)
	{
		if (data[posY + 1] & 0x1 << posX)
		{
			if (posX1 == posX && posY + 1 == posY1 || posX2 == posX && posY + 1 == posY2 || posX3 == posX && posY + 1 == posY3 || posX4 == posX && posY + 1 == posY4)
			{
				return true;
			}
			return false;
		}

		return true;
	}

};

int main(void)
{
	system("color 9b");

	Block block;
	block.SpawnRandomBlock();

	char i;
	char j;
	do
	{

		if (_kbhit())
			a = _getch();

		if (index > 10) 
		{
			if (!block.MoveDown())
				break;
			index = 0;
		}

		switch (a)
		{
		case 'd':
			block.MoveSideWays(1);
			break;
		case 'a':
			block.MoveSideWays(-1);
			break;
		case 'w':
			block.Rotate();
			break;
		case 's':
			block.MoveDown();
			break;
		default:
			break;
		}

		system("cls");
		for (i = 0; i < 26; i++)
		{
			putchar(219);
			putchar(219);
			putchar(219);
			putchar(219);

			for (a = 0; a < GAME_WIDTH; a++)
			{
				if (data[i] & (0x1 << a))
					putchar('*');
				else
					putchar(' ');
			}

			putchar(219);
			putchar(219);
			putchar(219);
			putchar(219);

			if(i == 1)
			{
				printf("  Score : %u", score);
			}

			if (i == 2)
			{
				fputs("  S = 下", stdout);
			}

			if (i == 3)
			{
				fputs("  A/D = 左/右", stdout);
			}

			if (i == 4)
			{
				fputs("  W = 回転", stdout);
			}

			putchar('\n');


			if ((UINT32_MAX / 2) - data[i] <= 0)
			{
				data[i] = 0;
				score += 10;

				for (a = 25; a > 0; a--)
				{
					for (j = 0; j < GAME_WIDTH; j++)
					{
						if (!(data[a] & 0x1 << j) && data[a - 1] & 0x1 << j && a != 0)
						{
							data[a] |= (data[a - 1] & 0x1 << j);
							data[a - 1] &= ~(0x1 << j);

							j = 0;
						}
					}
				}
			}
		}

		for (a = 0; a < 120; a++)
		{
			putchar(219);
		}

		++index;
		fflush(stdout);

	} while (true);

	fputs("\n\nGAME OVER ", stdout);
	getchar();
	return 0;
}