#include <stdio.h>
#include <stdlib.h>
#include <Windows.h >

typedef struct field_
{
	int* field_data;
} field;

int fieldsize;

int combining(int a, int b)
{
	int comb = 1;
	while (comb <= b)
		comb *= 10;
	return a * comb + b;
}

static int combi;

field* scan(field* f) {
	printf("enter a number from 1 to 9: ");
	scanf("%i", &fieldsize);
	if (fieldsize > 0 && fieldsize < 10) {
		combi = combining(fieldsize, fieldsize);
		int* data = malloc(sizeof(int) * fieldsize * fieldsize);
		data = memset(data, 0, sizeof(int) * fieldsize * fieldsize);
		f->field_data = data;
		return f;
	}
	else
	{
		scan(f);
	}
}


void visual(field* f)
{
	int pointer = fieldsize;
	int i, j;
	printf("%s", "  ");
	for (i = 1; i <= fieldsize; i++) {
		printf("%i ", i);
	}
	printf("%s\n", "");
	for (i = 1; i <= fieldsize; i++)
	{
		printf("%d", i);

		for (j = i * fieldsize - pointer; j < fieldsize*i; j++)
		{
			if (f->field_data[j] == 0) { printf("| "); };
			if (f->field_data[j] == 1) { printf("|X"); };
			if (f->field_data[j] == 2) { printf("|O"); };
		}

		printf("|\n");
		for (int z = 1; z <= fieldsize + 1; z++) {
			printf("__");
		}
		printf("%s\n", "");
	}
}

void Move(int n, field* f)
{
	int move; //ход
	int column;
	int row;
	int ver = 0; //корректность
	while (ver == 0)
	{
		printf("Your move. Enter the row and column number.\n");
		scanf("%d", &move);
		column = move % 10;
		row = (move - column) / 10;
		int cage = (row - 1) * fieldsize + (column - 1);
		if (f->field_data[cage] == 0 && (cage >= 0 && cage <= combi)) { ver = 1; }
		if (n == 1) { f->field_data[cage] = 1; }
		if (n == 2) { f->field_data[cage] = 2; }
	}
}

int gorizontal(int x, field* f)
{
	int result = 0;
	int z = x + fieldsize;
	int i = x;
	for (i = x; i < z; i++)
	{
		if (f->field_data[i] == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == z - 1)
		{
			return result;
		}
	}
	for (i = x; i < z; i++)
	{
		if (f->field_data[i] == 2)
		{
			result = 2;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == z - 1)
		{
			return result;
		}
	}
	return result;
}
int vertical(int x, field* f)
{
	int result = 0;
	int i = x;
	int z = fieldsize * fieldsize - (fieldsize - x);
	for (i = x; i <= z; i += fieldsize)
	{
		if (f->field_data[i] == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == z)
		{
			return result;
		}
	}
	for (i = x; i <= z; i += fieldsize)
	{
		if (f->field_data[i] == 2)
		{
			result = 2;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == z)
		{
			return result;
		}
	}
	return result;
}
int diagonal(field* f)
{
	int result = 0;
	for (int i = 0; i < fieldsize * fieldsize; i += fieldsize + 1)
	{
		if (f->field_data[i] == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			break;
		}
		if(i == fieldsize * fieldsize - 1)
		{
			return result;
		}
	}
	for(int i = fieldsize - 1; i <= fieldsize * fieldsize - fieldsize; i += fieldsize - 1)
	{
		if (f->field_data[i] == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == fieldsize * fieldsize - fieldsize)
		{
			return result;
		}
	}

	for (int i = 0; i < fieldsize * fieldsize; i += fieldsize + 1)
	{
		if (f->field_data[i] == 2)
		{
			result = 2;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == fieldsize * fieldsize - 1)
		{
			return result;
		}
	}
	for (int i = fieldsize - 1; i <= fieldsize * fieldsize - fieldsize; i += fieldsize - 1)
	{
		if (f->field_data[i] == 2)
		{
			result = 2;
		}
		else
		{
			result = 0;
			break;
		}
		if (i == fieldsize * fieldsize - fieldsize)
		{
			return result;
		}
	}

	return result;
}

int check(field* f)
{
	int res = 0;
	int t = 1;

	for (int i = 0; i < fieldsize * fieldsize; i += fieldsize)
	{
		if (res == 1 || res == 2)
		{
			return res;
		}
		else
		{
			res = gorizontal(i, f);
		}
	}
	res = 0;
	for(int i = 0; i < fieldsize; i++)
	{
		if (res == 1 || res == 2)
		{
			return res;
		}
		else
		{
			res = vertical(i, f);
		}
	}

	res = diagonal(f);

	for (int i = 0; i < fieldsize * fieldsize; i++)
	{
		if (f->field_data[i] == 0)
		{
			break;
		}
		else
		{
			if (i == fieldsize * fieldsize - 1)
			{
				res = 3;
				return res;
			}

		}
	}

	return res;
}
int main()
{
	int game;
	field* f = malloc(sizeof(field));
	visual(scan(f));
	game = 0;
	while (game == 0)
	{
		Move(1, f);
		visual(f);
		game = check(f);
		if (game == 0)
		{
			Move(2, f);
			visual(f);
			game = check(f);
		}
	}
	if (game == 1) { printf("win X\n"); }
	if (game == 2) { printf("win O\n"); }
	if (game == 3) { printf("drawn game\n"); }
	return 0;
};
