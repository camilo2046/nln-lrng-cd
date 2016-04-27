#include <iostream>
#include <stdio.h>						// scanf, printf

using namespace std;

void _print_int_array (int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf ("%d", a[i]);

		if (i < (n - 1))
		{
			printf (", ");
		}
	}

	printf ("\n");
}

void _print_int_array_2d (int** a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf ("%d", a[i][j]);

			if (j < (m - 1))
			{
				printf (", ");
			}
		}

		printf ("\n");
	}
}

/*
int main ()
{

    return 0;
}
*/
