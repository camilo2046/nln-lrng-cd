#include <stdio.h>						// scanf, printf
#include <math.h>						// Math Function (M_PI for PI value)
#include <time.h>						// Time Functions (tm struct, mktime)

using namespace std;

// Exercise 1.2.3

// 1

void read_write_double_number ()
{
	// http://www.cplusplus.com/reference/cstdio/scanf/
    // http://www.cplusplus.com/reference/cstdio/printf/

	double a = 10;

	printf ("Numero: ");
	scanf ("%lf", &a);

	printf ("Numero: %7.3lf \n", a);
}

// 2

void print_pi_n_digits (int n)
{
	printf ("Numero: %.*lf \n", n, M_PI);
}

// 3

const char* get_week_day (int day, int month, int year)
{
	// http://www.cplusplus.com/reference/ctime/
	// http://www.cplusplus.com/reference/ctime/tm/

	const char* week_day = "";

	tm time_struct = {};

	time_struct.tm_year = year - 1900;
	time_struct.tm_mon  = month - 1;
	time_struct.tm_mday = day;

	mktime (&time_struct);

	switch (time_struct.tm_wday)
	{
		case 0:
			week_day = "Sunday";
			break;

		case 1:
			week_day = "Monday";
			break;

		case 2:
			week_day = "Tuesday";
			break;

		case 3:
			week_day = "Wednesday";
			break;

		case 4:
			week_day = "Thursday";
			break;

		case 5:
			week_day = "Friday";
			break;

		case 6:
			week_day = "Saturday";
			break;

		default:
			week_day = "";
			break;
	}


	return week_day;
}

// 4

#define N_MAX = 50;

void print_int_array (int* a, int n)
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

int get_unique_elements (int* input, int* output, int n)
{
	int idx = 0;
	bool sw_unique = true;

	for (int i = 0; i < n; i++)
	{
		sw_unique = true;

		for (int j = 0; j < idx; j++)
		{
			if (output[j] == input[i])
			{
				sw_unique = false;
			}
		}

		if (sw_unique)
		{
			output[idx] = input[i];
			idx = idx + 1;
		}
	}

	return idx;
}

void merge_array (int* input, int n, int left, int right, int middle)
{
	int x = left;
	int y = middle + 1;
	int z = x;

	int aux[n] = {};

	while (x <= middle && y <= right)
	{
		if (input[x] < input[y])
		{
			aux[z] = input[x];
			x++;
		}
		else
		{
			aux[z] = input[y];
			y++;
		}

		z++;
	}

	while (x <= middle)
	{
		aux[z] = input[x];
		x++;
		z++;
	}

	while (y <= right)
	{
		aux[z] = input[y];
		y++;
		z++;
	}

   for (x = left; x <= right; x++)
   {
	   input[x] = aux[x];
   }
}

void merge_sort_array (int* input, int n, int left, int right)
{
	int middle;

	if (left < right)
	{
		middle = (left + right) / 2;

		// Order left half
		merge_sort_array (input, n, left, middle);

		// Order right half
		merge_sort_array (input, n, middle + 1, right);

		// Merge
		merge_array (input, n, left, right, middle);
	}
}

// 5

#define M_MAX = 50;

void print_int_array_2d (int a[][3], int n, int m)
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

void merge_array_2d_3col (int input[][3], int n, int left, int right, int middle)
{
	int x = left;
	int y = middle + 1;
	int z = x;

	int aux[n][3] = {};

	while (x <= middle && y <= right)
	{
		if (input[x][1] < input[y][1])
		{
			for (int i = 0; i < 3; i++)
			{
				aux[z][i] = input[x][i];
			}

			x++;
		}
		else if ((input[x][1] == input[y][1]) && (input[x][0] < input[y][0]))
		{
			for (int i = 0; i < 3; i++)
			{
				aux[z][i] = input[x][i];
			}

			x++;
		}
		else if (((input[x][1] == input[y][1]) && (input[x][0] == input[y][0])) && (input[x][2] < input[y][2]))
		{
			for (int i = 0; i < 3; i++)
			{
				aux[z][i] = input[x][i];
			}

			x++;
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				aux[z][i] = input[y][i];
			}

			y++;
		}

		z++;
	}

	while (x <= middle)
	{
		for (int i = 0; i < 3; i++)
		{
			aux[z][i] = input[x][i];
		}

		x++;
		z++;
	}

	while (y <= right)
	{
		for (int i = 0; i < 3; i++)
		{
			aux[z][i] = input[y][i];
		}

		y++;
		z++;
	}

   for (x = left; x <= right; x++)
   {
		for (int i = 0; i < 3; i++)
		{
			input[x][i] = aux[x][i];
		}
   }
}

void merge_sort_array_2d_3col (int input[][3], int n, int left, int right)
{
	int middle;

	if (left < right)
	{
		middle = (left + right) / 2;

		// Order left half
		merge_sort_array_2d_3col (input, n, left, middle);

		// Order right half
		merge_sort_array_2d_3col (input, n, middle + 1, right);

		// Merge
		merge_array_2d_3col (input, n, left, right, middle);
	}
}

// 6

bool binary_search (int* input, int v, int left, int right)
{
	int middle;

	if (left < right)
	{
		middle = (left + right) / 2;

		if (input[middle] == v)
		{
			return true;
		}
		else if (input[middle] > v)
		{
			return binary_search (input, v, left, middle);
		}
		else
		{
			return binary_search (input, v, middle + 1, right);

		}
	}
	else
	{
		return false;
	}
}

bool is_element_in_sorted_array (int* input, int n, int v)
{
	return binary_search (input, v, 0, n);
}

// 7

// 8

// 9

// 10

// 11

int main ()
{
	// 1

//	read_write_double_number ();

	// 2

//	print_pi_n_digits (2);
//	print_pi_n_digits (4);
//	print_pi_n_digits (5);

	// 3

//	printf ("(%02d, %02d, %04d): %s \n", 9, 8, 2010, get_week_day (9, 8, 2010));

	// 4

//	int n = 20;
//	int array_test []   = {1,1,2,2,3,30,4,3,5,6,7,10,1,2,3,4,5,6,10,9};
//	print_int_array (array_test, n);

//	int array_result[n] = {};
//	int n_unique = get_unique_elements (array_test, array_result, n);

//	printf ("%d\n", n_unique);
//	print_int_array (array_result, n_unique);
//	print_int_array (array_test, n);
//	merge_sort_array (array_result, n_unique, 0, n_unique - 1);
//	print_int_array (array_result, n_unique);

	// 5

//	int n = 10;
//	int m = 3;

//	int array_triple_test[10][3] = {{1,5,1880},
//									{10,5,1880},
//									{1,1,1870},
//									{20,1,1870},
//									{5,4,1860},
//									{3,2,1860},
//									{3,2,1890},
//									{25,4,1890},
//									{2,2,1890},
//									{1,8,1895}};

//	print_int_array_2d (array_triple_test, n, m);
//	merge_sort_array_2d_3col (array_triple_test, n, 0, n-1);
//	printf ("****************************** \n");
//	print_int_array_2d (array_triple_test, n, m);

	// 6

	int n = 20;
	int array_test []   = {1,1,2,2,3,30,4,3,5,6,7,10,1,2,3,4,5,6,10,9};
	merge_sort_array (array_test, n, 0, n - 1);
	print_int_array (array_test, n);

	printf ("%s \n", is_element_in_sorted_array (array_test, n, 1) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 3) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 7) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 10) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 30) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, -1) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 100) ? "true" : "false");
	printf ("%s \n", is_element_in_sorted_array (array_test, n, 500) ? "true" : "false");

	// 7
	// 8
	// 9
	// 10
	// 11

    return 0;
}









