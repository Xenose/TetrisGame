#include<stdint.h>
#include<stdio.h>
#include<conio.h>
#include<Windows.h>


#define GAME_WIDTH 31

#define TRIANGLE 2, 2, 1, 2, 3, 2, 2, 1
#define LINE 0, 2, 1, 2, 2, 2, 3, 2
#define CUBE 0, 2, 1, 2, 0, 1, 1, 1
#define S_BLOCK 2, 2, 1, 2, 2, 1, 3, 1

uint32_t data[26];
uint16_t score = 0;

struct Block
{
	char x1;
	char y1;

	char x2;
	char y2;
	
	char x3;
	char y3;

	char x4;
	char y4;

	Block(){}

	void SpawnBlock(const char& _x1, const char& _y1, const char& _x2, const char& _y2, const char& _x3, const char& _y3, const char& _x4, const char& _y4)
	{
		x1 = _x1;
		x2 = _x2;
		x3 = _x3;
		x4 = _x4;

		y1 = _y1;
		y2 = _y2;
		y3 = _y3;
		y4 = _y4;

		data[_y1] |= 0x1 << _x1;
		data[_y2] |= 0x1 << _x2;
		data[_y3] |= 0x1 << _x3;
		data[_y4] |= 0x1 << _x4;
	}

	void MoveSideWays(const char& a)
	{
		if (y1 < 25 && y2 < 25 && y3 < 25 && y4 < 25) {
			if (x1 > 0 && x2 > 0 && x3 > 0 && x4 > 0 && a < 0 || 
				a > 0 && x1 < GAME_WIDTH - 1 && x2 < GAME_WIDTH - 1 && x3 < GAME_WIDTH - 1&& x4 < GAME_WIDTH - 1)
			{
				data[y1] &= ~(0x1 << x1);
				data[y2] &= ~(0x1 << x2);
				data[y3] &= ~(0x1 << x3);
				data[y4] &= ~(0x1 << x4);

				x1 += a;
				x2 += a;
				x3 += a;
				x4 += a;

				data[y1] |= 0x1 << x1;
				data[y2] |= 0x1 << x2;
				data[y3] |= 0x1 << x3;
				data[y4] |= 0x1 << x4;
			}
		}
	}

	void Rotate(void)
	{
		char tmpX, tmpY;

		data[y2] &= ~(0x1 << x2);
		//tmpX = (x2 * cos(90)) - (y2 * sin(90));
		//tmpY = (x2 * sin(90)) - (y2 * cos(90));
		tmpY = y2 - y1;
		tmpX = x2 - x1;

		x2 = x1 - tmpY;
		y2 = y1 - tmpX;

		data[y3] &= ~(0x1 << x3);
		tmpY = y3 - y1;
		tmpX = x3 - x1;

		x3 = x1 - tmpY;
		y3 = y1 - tmpX;

		data[y4] &= ~(0x1 << x4);
		tmpY = y4 - y1;
		tmpX = x4 - x1;

		x4 = x1 - tmpY;
		y4 = y1 - tmpX;

		data[y1] |= 0x1 << x1;
		data[y2] |= 0x1 << x2;
		data[y3] |= 0x1 << x3;
		data[y4] |= 0x1 << x4;
	}

	void MoveDown(void)
	{
		if (y1 < 25 && y2 < 25 && y3 < 25 && y4 < 25 &&
			CanMoveDown(x1, y1) &&
			CanMoveDown(x2, y2) &&
			CanMoveDown(x3, y3) &&
			CanMoveDown(x4, y4))
		{
			data[y1] &= ~(0x1 << x1);
			data[y2] &= ~(0x1 << x2);
			data[y3] &= ~(0x1 << x3);
			data[y4] &= ~(0x1 << x4);

			y1++;
			y2++;
			y3++;
			y4++;

			data[y1] |= 0x1 << x1;
			data[y2] |= 0x1 << x2;
			data[y3] |= 0x1 << x3;
			data[y4] |= 0x1 << x4;
		}

		else
		{
			switch (rand() % 4)
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
			}
		}
	}

	bool CanMoveDown( const char& posX, const char& posY)
	{
		if (data[posY + 1] & 0x1 << posX)
		{
			if (x1 == posX && posY + 1 == y1 || x2 == posX && posY + 1 == y2 || x3 == posX && posY + 1 == y3 || x4 == posX && posY + 1 == y4)
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

	char a = '0';
	Block block;
	block.SpawnBlock(TRIANGLE);

	char index = 0;

	do
	{

		if (_kbhit())
			a = _getch();

		if (index > 10) 
		{
			block.MoveDown();
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
		char i;
		for (i = 0; i < 26; i++)
		{
			for (a = 0; a < 4; a++)
			{
				putchar(178);
			}

			for (a = 0; a < GAME_WIDTH; a++)
			{
				if (data[i] & (0x1 << a))
					putchar('*');
				else
					putchar(' ');
			}

			for (a = 0; a < 4; a++)
			{
				putchar(178);
			}

			if(i == 1)
			{
				printf("  Score : %u", score);
			}

			if (i == 2)
			{
				fputs("  A/D = 左/右", stdout);
			}

			if (i == 3)
			{
				fputs("  S = 下", stdout);
			}

			putchar('\n');


			if ((UINT32_MAX / 2) - data[i] <= 0)
			{
				data[i] = 0;
				score += 100;

				for (a = 25; a > 0; a--)
				{
					data[a] = data[a - 1];
				}
			}
		}

		for (a = 0; a < 120; a++)
		{
			putchar(178);
		}

		//printf("\n x1 = %d, x2 = %d, x3 = %d, x4 = %d \n data[25] = %u : INT_MAX = %u : Sum %u", block.x1, block.x2, block.x3, block.x4, data[25], UINT32_MAX/2, UINT32_MAX/2 - data[25]);
		
		index++;
		fflush(stdout);
		Sleep(10);

	} while (true);

	return 0;
}