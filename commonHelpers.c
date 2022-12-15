
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include "commonHelpers.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

// As demonstrated in the course notes:
//https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}


int getInteger()
{
	int n;
	char c;
	do
	{
		scanf("%d%c", &n, &c);
		if (c != '\n')
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
	} while (c != '\n');

	return n;
}
int getPositiveInteger()
{
	int n;
	char c;
	do
	{
		scanf("%d%c", &n, &c);
		if (c != '\n')
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
		if (n <= 0)
			printf("ERROR: Value must be a positive integer greater than zero: ");
	} while (c != '\n' || n <= 0);

	return n;
}
int getIntFromRange(int low, int high)
{
	int n;
	char c;
	do
	{
		scanf("%d%c", &n, &c);
		if (c != '\n')
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
		else
		{
			if (n<low || n>high)
			{
				printf("ERROR: Value must be between %d and %d inclusive: ", low, high);
				if (c == '\n')
					c = 'c';
			}
		}
	} while (c != '\n' || n<low || n>high);

	return n;
}
double getDouble()
{
	double d;
	char c;
	do
	{
		scanf("%lf%c", &d, &c);
		if (c != '\n')
		{
			printf("ERROR: Value must be a double floating-point number: ");
			clearStandardInputBuffer();
		}
	} while (c != '\n');

	return d;
}
double getPositiveDouble()
{
	double d;
	char c;
	do
	{
		scanf("%lf%c", &d, &c);
		if (c != '\n')
		{
			printf("ERROR: Value must be a double floating-point number: ");
			clearStandardInputBuffer();
		}
		if (d <= 0)
			printf("ERROR: Value must be a positive double floating-point number: ");
	} while (c != '\n' || d <= 0);

	return d;
}
char getCharOption(char c[])
{
	int i, flag = 0, forFlag = 0;
	char ch[10];

	do
	{
		forFlag = 0;
		scanf("%10[^\n]", ch);
		if (ch[1] != '\0')
		{
			printf("ERROR: Character must be one of [%s]: ", c);
			forFlag = 1;
		}
		if (forFlag == 0)
		{
			for (i = 0; c[i] != '\0' && flag == 0; i++)
			{
				if (c[i] == ch[0])
					flag = 1;
			}
			if (flag == 0)
				printf("ERROR: Character must be one of [%s]: ", c);
		}
		clearStandardInputBuffer();

	} while (flag != 1);

	return ch[0];
}
void getCString(char* cstring, int min, int max)
{
	int i, j = 0;
	char cs[151];
	do
	{
		scanf("%150[^\n]", cs);

		for (i = 0; cs[i] != '\0'; i++);

		if (i < min)
		{
			if (min == max)
				printf("ERROR: String length must be exactly %d chars: ", min);
			else
				printf("ERROR: String length must be between %d and %d chars: ", min, max);
		}
		if (i > max)
		{
			if (min == max)
				printf("ERROR: String length must be exactly %d chars: ", min);
			else
				printf("ERROR: String length must be no more than %d chars: ", max);
		}

		clearStandardInputBuffer();
	} while (i<min || i>max);

	do
	{
		cstring[j] = cs[j];
		j++;
	} while (cs[j] != '\0');
	cstring[j] = cs[j];
}

int countUpper(const char* str)
{
	int i, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isupper(str[i]))
		{
			count++;
		}
	}

	return count;
}

int countLower(const char* str)
{
	int i, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (islower(str[i]))
		{
			count++;
		}
	}

	return count;
}

int countDigit(const char* str)
{
	int i, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]))
		{
			count++;
		}
	}

	return count;
}

int countSymbol(const char* str)
{
	int i, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isalpha(str[i]))
			if (!isdigit(str[i]))
				if (!isblank(str[i]))
				{
					if (str[i] == '!')
						count++;
					if (str[i] == '@')
						count++;
					if (str[i] == '#')
						count++;
					if (str[i] == '$')
						count++;
					if (str[i] == '%')
						count++;
					if (str[i] == '^')
						count++;
					if (str[i] == '&')
						count++;
					if (str[i] == '*')
						count++;
				}
	}

	return count;
}

void convertUpper(char* str)
{
	int i;


	for (i = 0; str[i] != '\0'; i++)
	{
		str[i] = toupper(str[i]);
	}
}