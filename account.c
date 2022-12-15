
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"

void getAccount(struct Account* account, int acNumber)
{
	struct UserLogin ul = { { 0 } };
	account->account_number = acNumber + 1;
	printf("\nNew Account Data (Account#:%d)", account->account_number);
	printf("\n----------------------------------------");

	//printf("\nEnter the account number: ");
	//account->accountNumber = getPositiveInteger();

	printf("\nEnter the account type (A=Agent | C=Customer): ");
	account->account_type = getCharOption("AC");

	getPerson(&account->person);

	if (account->account_type == 'A')
		getUserLogin(&account->login);
	else
		account->login = ul;

	printf("\n*** New account added! ***\n");
	pauseExecution();
}

void getPerson(struct Person* person)
{
	printf("\nPerson Data Input");
	printf("\n----------------------------------------");

	printf("\nEnter the person's full name (30 chars max): ");
	getCString(person->name, 1, 30);

	printf("Enter birth year (current age must be between 18 and 110): ");
	person->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);
	printf("Enter the household Income: $");
	person->income = getPositiveDouble();

	printf("Enter the country (30 chars max.): ");
	getCString(person->country, 1, 30);
	convertUpper(person->country);
}
void getUserLogin(struct UserLogin* login)
{
	int flag = 1, i;
	printf("\nUser Login Data Input\n");
	printf("----------------------------------------\n");

	do
	{
		printf("Enter user login (10 chars max): ");
		getCString(login->loginName, 1, 10);
		for (i = 0; i <= 10; i++)
			if (isblank(login->loginName[i]))
			{
				flag = 0;
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				break;
			}
			else
				flag = 1;
	} while (flag != 1);

	flag = 1;

	do
	{
		printf("Enter the password (must be 8 chars in length): ");
		getCString(login->pass, 8, 8);

		if (countDigit(login->pass) != 2 || countLower(login->pass) != 2 || countUpper(login->pass) != 2 || countSymbol(login->pass) != 2)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
			flag = 0;
		}
		else
			flag = 1;

	} while (flag != 1);

}

void updateAccount(struct Account* account)
{
	int selection;
	char acType;
	struct UserLogin ul = { { 0 } };

	do
	{
		printf("\nUpdate Account: %d (%s)", account->account_number, account->person.name);
		printf("\n----------------------------------------");
		printf("\n1) Update account type (current value: %c)", account->account_type);
		printf("\n2) Person");
		printf("\n3) Login");
		printf("\n0) Done");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 3);
		switch (selection)
		{
		case 1:
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			acType = getCharOption("AC");
			if (acType == 'A')
			{
				account->account_type = 'A';
				printf("\nAgent type accounts require a user login.  Please enter this information now:\n");
				getUserLogin(&account->login);
			}
			else
			{
				account->account_type = 'C';
				account->login = ul;
			}
			break;
		case 2:
			updatePerson(&account->person);
			break;
		case 3:
			if (account->account_type == 'C')
				printf("\nERROR:  Customer account types don't have user logins!\n");
			else
				updateUserLogin(&account->login);
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (selection != 0);
}
void updatePerson(struct Person* person)
{
	int selection;
	do
	{
		printf("\nPerson Update Options");
		printf("\n----------------------------------------");
		printf("\n1) Full name (current value: %s)", person->name);
		printf("\n2) Household Income (current value: $%.2lf)", person->income);
		printf("\n3) Country (current value: %s)", person->country);
		printf("\n0) Done");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 3);

		switch (selection)
		{
		case 1:
			printf("\nEnter the person's full name (30 chars max): ");
			getCString(person->name, 1, 30);
			break;
		case 2:
			printf("\nEnter the household Income: $");
			person->income = getPositiveDouble();
			break;
		case 3:
			printf("\nEnter the country (30 chars max.): ");
			getCString(person->country, 1, 30);
			convertUpper(person->country);
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (selection != 0);
}
void updateUserLogin(struct UserLogin* login)
{
	int selection;
	do
	{
		printf("\nUser Login: %s - Update Options", login->loginName);
		printf("\n----------------------------------------");
		printf("\n1) Password");
		printf("\n0) Done");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 1);

		switch (selection)
		{
		case 1:
			printf("\nEnter the password (must be 8 chars in length): ");
			getCString(login->pass, 8, 8);
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (selection != 0);
}

int loadAccounts(struct Account* accounts, int ACCOUNT_SIZE)
{
	FILE* fp = NULL;
	char* info;
	int i = 0, flag = 0, j = 0;
	char acc[100], atype = 'X';
	char char2[2] = "~";
	char char3[2] = "A";

	fp = fopen("accounts.txt", "r");

	while (fscanf(fp, "%[^\n] ", acc) != EOF && flag == 0)
	{
		info = strtok(acc, char2);
		while (info)
		{
			if (j == 0)
				accounts[i].account_number = atoi(info);
			else if (j == 1)
			{
				if (!strcmp(info, char3))
				{
					accounts[i].account_type = 'A';
					atype = 'A';
				}
				else
				{
					accounts[i].account_type = 'C';
					atype = 'C';
				}


			}
			else if (j == 2)
				strcpy(accounts[i].person.name, info);
			else if (j == 3)
				accounts[i].person.birth_year = atoi(info);
			else if (j == 4)
				accounts[i].person.income = atof(info);
			else if (j == 5)
				strcpy(accounts[i].person.country, info);

			if (atype == 'A' && (j == 6 || j == 7))
			{
				if (j == 6)
					strcpy(accounts[i].login.loginName, info);
				else if (j == 7)
					strcpy(accounts[i].login.pass, info);
			}

			j++;
			info = strtok(NULL, char2);
		}
		j = 0;
		i++;
		if (i == ACCOUNT_SIZE)
			flag = 1;
	}
	fclose(fp);

	return i;
}

int saveAccounts(struct Account* accounts, int ACCOUNT_MAX_SIZE)
{
	FILE* fp = NULL;
	int i = 0;

	fp = fopen("accounts.txt", "w");

	if (fp != NULL)
	{
		for (i = 0; i < ACCOUNT_MAX_SIZE; i++)
		{
			if (accounts[i].account_type == 'C')
				fprintf(fp, "%d~%c~%s~%d~%.2lf~%s\n", accounts[i].account_number, accounts[i].account_type, accounts[i].person.name, accounts[i].person.birth_year, accounts[i].person.income, accounts[i].person.country);
			else
				fprintf(fp, "%d~%c~%s~%d~%.2lf~%s~%s~%s\n", accounts[i].account_number, accounts[i].account_type, accounts[i].person.name, accounts[i].person.birth_year, accounts[i].person.income, accounts[i].person.country, accounts[i].login.loginName, accounts[i].login.pass);
		}
		fclose(fp);
	}
	else
	{
		printf("\nFailed to open the file.\n");
	}
	return i;
}