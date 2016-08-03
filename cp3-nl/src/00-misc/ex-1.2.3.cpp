#include <stdio.h>						// scanf, printf, fopen, fclose fscanf, fprintf
#include <string.h>						// string functions (strlen, strcpy, strcat)
#include <math.h>						// Math Function  (M_PI for PI value), pow
#include <time.h>						// Time Functions (tm struct, mktime)
#include <cstdlib>						// Command Line Functions used (system)

//using namespace std;

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

void print_char_array (char* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf ("%c", a[i]);
	}

	printf ("\n");
}

void swap_char (char *x, char *y)
{
	char temp;
    temp = *x;
    *x   = *y;
    *y   = temp;
}

void print_permutations (char *input, int left, int right)
{
	int i;
	if (left == right)
	{
	   print_char_array (input, right);
	   return;
	}
	else
	{
	   for (i = left; i < right; i++)
	   {
		   swap_char ((input + left), (input + i));
		   print_permutations (input, left + 1, right);
		   swap_char ((input + left), (input + i));
	   }
	}
}

// 8


// https://compprog.wordpress.com/2007/10/10/generating-subsets/

void print_bool_array (bool* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%s", a[i] ? "1" : "0");
	}

	printf ("\n");
}

void print_int_array_with_mask (bool *mask, int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (mask[i])
		{
			printf ("%d ", a[i]);
		}
	}

	printf ("\n");
}

void convert_decimal_to_binary_bool_array (int n, bool *output, int n_output)
{
	int i = 0;
	int quotient = n;

	while (quotient > 0)
	{
		quotient  = n / 2;
		output[n_output - i - 1] = (n % 2 == 1);

		n = quotient;
		i = i + 1;
	}
}

void print_subsets (int *input, int n)
{
	int n_counter = pow (2, n);
	bool bin_array[n];

	for (int i = 0; i < n; i++)
	{
		bin_array[i] = false;
	}

	for (int i = 0; i < n_counter; i++)
	{
		convert_decimal_to_binary_bool_array (i, bin_array, n);
//		print_bool_array (bin_array, n);
		print_int_array_with_mask (bin_array, input, n);
	}
}

// 9

int binary_search_index (char* input, char v, int left, int right)
{
	int middle;

	if (left < right)
	{
		middle = (left + right) / 2;

		if (input[middle] == v)
		{
			return middle;
		}
		else if (input[middle] > v)
		{
			return binary_search_index (input, v, left, middle);
		}
		else
		{
			return binary_search_index (input, v, middle + 1, right);

		}
	}
	else
	{
		return -1;
	}
}

void convert_decimal_to_base (char *n, char *output, int base_to, int n_output)
{
	char DIGITS_ARRAY[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	double decimal_f = 0;
	long decimal_l = 0;

	for (int i = 0; i < n_output; i++)
	{
		int binary_search_index_value = binary_search_index (DIGITS_ARRAY, n[i], 0, 36);
		decimal_f = decimal_f + (binary_search_index_value * pow (10, n_output - i - 1));
		output[i] = '0';
	}

	decimal_l = (long) decimal_f;

	int idx = 0;
	int quotient = decimal_l;

	while (quotient > 0)
	{
		quotient  = decimal_l / base_to;
		output[n_output - idx - 1] = DIGITS_ARRAY[(decimal_l % base_to)];

		decimal_l = quotient;
		idx = idx + 1;
	}
}

void convert_base_to_decimal (char *n, char *output, int base_from, int n_output)
{
	char DIGITS_ARRAY[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	double decimal_f = 0;
	long decimal_l = 0;

	for (int i = 0; i < n_output; i++)
	{
		int binary_search_index_value = binary_search_index (DIGITS_ARRAY, n[i], 0, 36);
		decimal_f = decimal_f + (binary_search_index_value * pow (base_from, n_output - i - 1));
		output[i] = '0';
	}

	decimal_l = (long) decimal_f;

	int idx = 0;
	int quotient = decimal_l;

	while (quotient > 0)
	{
		quotient  = decimal_l / 10;
		output[n_output - idx - 1] = DIGITS_ARRAY[(decimal_l % 10)];

		decimal_l = quotient;
		idx = idx + 1;
	}
}

void convert_base_to_base (char *n, int base_from, int base_to, char *output, int n_output)
{
	unsigned long orig_len = strlen (n);

	for (unsigned long i = 0; i < orig_len; i++)
	{
		n[n_output - i - 1] = n[orig_len - i - 1];
	}

	for (unsigned long i = 0; i < n_output - orig_len; i++)
	{
		n[i] = '0';
	}

	n[n_output] = '\0';		// The for loop modified the original string array

	char input_n_decimal[n_output];

	if (base_from == 10)
	{
		strcpy (input_n_decimal, n);
	}
	else
	{
		convert_base_to_decimal (n, input_n_decimal, base_from, n_output);
	}

	if (base_to == 10)
	{
		strcpy (output, input_n_decimal);
	}
	else
	{
		convert_decimal_to_base (input_n_decimal, output, base_to, n_output);
	}
}

// 10

void replace_special_words (char *input, char *output)
{
	char DIGITS_ARRAY[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char LOWERCASE_LET_ARRAY[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	unsigned long i = 0;
	unsigned long orig_s_len = strlen (input);

	while (i <= orig_s_len)
	{
		int binary_search_index_value_1 = -1;
		int binary_search_index_value_2 = -1;
		int binary_search_index_value_3 = -1;

		if (i <= (orig_s_len - 4))
		{
			if (i == 0)
			{
				binary_search_index_value_1 = binary_search_index (LOWERCASE_LET_ARRAY, input[i], 0, 26);
				binary_search_index_value_2 = binary_search_index (DIGITS_ARRAY, input[i + 1], 0, 10);
				binary_search_index_value_3 = binary_search_index (DIGITS_ARRAY, input[i + 2], 0, 10);
			}
			else if (i >= (orig_s_len - 4))
			{
				if (input[i] == ' ')
				{
					binary_search_index_value_1 = binary_search_index (LOWERCASE_LET_ARRAY, input[i + 1], 0, 26);
					binary_search_index_value_2 = binary_search_index (DIGITS_ARRAY, input[i + 2], 0, 10);
					binary_search_index_value_3 = binary_search_index (DIGITS_ARRAY, input[i + 3], 0, 10);
				}
			}
			else
			{
				if ((input[i] == ' ') && (input[i + 4] == ' '))
				{
					binary_search_index_value_1 = binary_search_index (LOWERCASE_LET_ARRAY, input[i + 1], 0, 26);
					binary_search_index_value_2 = binary_search_index (DIGITS_ARRAY, input[i + 2], 0, 10);
					binary_search_index_value_3 = binary_search_index (DIGITS_ARRAY, input[i + 3], 0, 10);
				}

			}
		}

		if ((binary_search_index_value_1 >= 0) && (binary_search_index_value_2 >= 0) && (binary_search_index_value_3 >= 0))
		{
			if (i == 0)
			{
				output[i] = '*';
				output[i + 1] = '*';
				output[i + 2] = '*';
				i = i + 3;
			}
			else if (i >= (orig_s_len - 4))
			{
				output[i] = ' ';
				output[i + 1] = '*';
				output[i + 2] = '*';
				output[i + 3] = '*';
				i = i + 4;
			}
			else
			{
				output[i] = ' ';
				output[i + 1] = '*';
				output[i + 2] = '*';
				output[i + 3] = '*';
				i = i + 4;
			}
		}
		else
		{
			output[i] = input[i];
			i = i + 1;
		}
	}
}

// 11

double evaluate_expression (char *expr)
{
	// http://www.tutorialspoint.com/cprogramming/c_file_io.htm
	// http://www.tutorialspoint.com/c_standard_library/c_function_system.htm

	double result = 0;

	char command_line_str[strlen(expr) + 20] = "bc -l <<< ";
	strcat (command_line_str, "\"");
	strcat (command_line_str, expr);
	strcat (command_line_str, "\"");

	FILE *fp_temp;
	fp_temp = fopen ("/tmp/cmd_temp.sh", "w");
	fprintf (fp_temp, command_line_str);
	fclose (fp_temp);

	system ("bash < \"/tmp/cmd_temp.sh\" > \"/tmp/cmd_temp_output.txt\"");

	FILE *fp_temp_ouput;
	fp_temp_ouput = fopen ("/tmp/cmd_temp_output.txt", "r");
	fscanf (fp_temp_ouput, "%lf", &result);
	fclose (fp_temp_ouput);

	return result;
}

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

//	int n = 20;
//	int array_test []   = {1,1,2,2,3,30,4,3,5,6,7,10,1,2,3,4,5,6,10,9};
//	merge_sort_array (array_test, n, 0, n - 1);
//	print_int_array (array_test, n);

//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 1) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 3) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 7) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 10) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 30) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, -1) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 100) ? "true" : "false");
//	printf ("%s \n", is_element_in_sorted_array (array_test, n, 500) ? "true" : "false");

	// 7

//	int n = 10;
//	char array_test[] = "ABCDEFGHIJ";
//	print_char_array (array_test, n);

//	print_permutations (array_test, 0, n);

	// 8

//	int n = 20;
//	int array_test[]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//	print_int_array (array_test, n);
//	print_subsets (array_test, n);

	// 9

//	int n = 10;
//	char array_test[n] = "FF";
//	char array_test[n] = "0111101";
//	char array_test[n] = "255";
//	char array_test[n] = "1234567";
//	char array_output[n] = "";
//	int base1 = 2;
//	int base1 = 8;
//	int base1 = 10;
//	int base1 = 16;
//	int base2 = 2;
//	int base2 = 8;
//	int base2 = 10;
//	int base2 = 16;

//	print_char_array (array_test, n);
//	convert_base_to_base (array_test, base1, base2, array_output, n);
//	print_char_array (array_test, n);
//	print_char_array (array_output, n);

	// 10

//	http://en.cppreference.com/w/cpp/regex/regex_replace
//	http://www.cplusplus.com/reference/regex/regex_replace/

//	char *input_test = "line: a70 and z72 will be replaced, aa24 and a872 will not";
//	char *input_test = "a70 and z72 will be replaced, aa24 and a872 will not";
//	char *input_test = "line: a70 and z72 will be replaced, aa24 and a872 will not a70";
//	char *input_test = "a70 and z72 will be replaced, aa24 and a872 will not a70";

//	char output_test[strlen(input_test)];

//	replace_special_words (input_test, output_test);

//	print_char_array (input_test, strlen (input_test));
//	print_char_array (output_test, strlen (input_test));

	// 11

//	char *expr = "3 + (8 - 7.5) * 10 / 5 - (2 + 5 * 7)";

//	printf ("%f", evaluate_expression (expr));

	return 0;
}
