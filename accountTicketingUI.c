
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

void displayAccountDetailHeader()
{
	printf("\nAcct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}




void displayAccountDetailRecord(const struct Account* account)
{
	char agent[10] = "AGENT";
	char customer[10] = "CUSTOMER";
	char pass[9];
	int i;
	for (i = 0;i < 9;i++)
	{
		if (i % 2 == 0)
			pass[i] = account->login.pass[i];
		else
			pass[i] = '*';
	}

	if (account->account_type == 'A')
		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account->account_number , agent, account->person.name, account->person.birth_year, account->person.income, account->person.country, account->login.loginName, pass);
	else
		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account->account_number , customer, account->person.name, account->person.birth_year, account->person.income, account->person.country, account->login.loginName, pass);
}

//###############################################################################

void applicationStartup(struct AccountTicketingData* accounts)
{
	int i;
	do
	{
		i = menuLogin(accounts->accounts, accounts->ACCOUNT_MAX_SIZE);
		if (i == -1)
		{
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
		}
		else
		{
			if (accounts->accounts[i].account_type== 'A')
				menuAgent(accounts, &accounts->accounts[i]);
			else
			{
				printf("ERROR:  Login failed!\n");
				pauseExecution();
				putchar('\n');
			}

		}
	} while (i != -1);
}
int menuLogin(const struct Account accounts[], int max)
{
	int i = 0, selection, count = 3, flag = 0;;
	char input, id[50], pass[50];
	do
	{
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 1);

		switch (selection)
		{
		case 1:
			do
			{
				printf("\nEnter the account#: ");
				int ano = getInteger();

				printf("User Login        : ");
				getCString(id, 1, 50);

				printf("Password          : ");
				getCString(pass, 1, 50);

				for (i = 0;i < max;i++)
					if (ano == accounts[i].account_number )
					{
						selection = 0;
						break;
					}
				if (i == max)
				{
					printf("ERROR:  Login failed!\n");
					pauseExecution();
					putchar('\n');
				}

				if (strcmp(id, accounts[i].login.loginName))
				{
					count--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", count);
				}
				else if (strcmp(pass, accounts[i].login.pass))
				{
					count--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", count);
				}
				else
					flag = 1;
				if (count == 0)
				{
					printf("\nERROR:  Access Denied.\n");
					pauseExecution();
					putchar('\n');
					selection = 1;
				}

			} while (count > 0 && flag != 1);

			count = 3;

			break;
		case 0:
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			input = getCharOption("yYnN");
			printf("\n");
			if (input == 'y' || input == 'Y')
				i = -1;
			else
				selection = 1;
			break;
		default:
			break;
		}
	} while (selection != 0 && i != -1);

	return i;
}
void menuAgent(struct AccountTicketingData* acc, const struct Account* account)
{
	struct Ticket t = { 0 };
	int selection, i, j, acNumber, count = 0, tnumber, Saved_record;
	char confirm;
	do
	{
		if (account->account_type== 'A')
			printf("\nAGENT: %s (%d)", account->person.name, account->account_number );
		else
			printf("CUSTOMER: %s (%d)", account->person.name, account->account_number );

		printf("\n==============================================");
		printf("\nAccount Ticketing System - Agent Menu");
		printf("\n==============================================");
		printf("\n1) Add a new account");
		printf("\n2) Modify an existing account");
		printf("\n3) Remove an account");
		printf("\n4) List accounts: detailed view");
		printf("\n----------------------------------------------");
		printf("\n5) List new tickets");
		printf("\n6) List active tickets");
		printf("\n7) List closed tickets");
		printf("\n8) Add a new ticket");
		printf("\n9) Manage a ticket");
		printf("\n----------------------------------------------");
		printf("\n0) Logout\n");
		printf("\nSelection: ");

		selection = getIntFromRange(0, 9);

		switch (selection)
		{
		case 1:
			for (i = 0;i < acc->ACCOUNT_MAX_SIZE;i++)
				if (acc->accounts[i].account_number  == 0)
					break;
			if (i == acc->ACCOUNT_MAX_SIZE)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n");
				pauseExecution();
			}
			else
			{
				acNumber = acc->accounts[0].account_number ;
				for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
				{
					if (acNumber < acc->accounts[j].account_number )
					{
						acNumber = acc->accounts[j].account_number ;
					}
				}
				getAccount(&acc->accounts[i], acNumber);
			}
			break;
		case 2:
			printf("\nEnter the account#: ");
			acNumber = getPositiveInteger();
			for (i = 0;i < acc->ACCOUNT_MAX_SIZE;i++)
			{
				if (acNumber == acc->accounts[i].account_number )
				{
					updateAccount(&acc->accounts[i]);
					break;
				}
			}
			if (i == acc->ACCOUNT_MAX_SIZE)
			{
				printf("\nERROR: Account Not Found!");
				pauseExecution();
			}
			break;
		case 3:
			printf("\nEnter the account#: ");
			acNumber = getPositiveInteger();
			for (i = 0;i < acc->ACCOUNT_MAX_SIZE;i++)
			{
				if (acNumber == acc->accounts[i].account_number )
				{
					if (acNumber == account->account_number )
					{
						printf("\nERROR: You can't remove your own account!\n");
						pauseExecution();
						break;
					}
					else
					{
						printf("\nAcct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
						printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
						displayAccountDetailRecord(&acc->accounts[i]);

						printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
						confirm = getCharOption("yYnN");
						if (confirm == 'y' || confirm == 'Y')
						{
							for (j = 0;j < acc->TICKET_MAX_SIZE;j++)
								if (acc->accounts[i].account_number == acc->tickets[j].account_number )
								{
									count++;
									acc->tickets[j] = t;
								}

							acc->accounts[i].account_number = 0;
							printf("\n*** Account Removed! (%d ticket(s) removed) ***\n", count);
							pauseExecution();
							count = 0;
							break;
						}
					}
				}
			}
			if (i == acc->ACCOUNT_MAX_SIZE)
				printf("\nERROR: Account Not Found!");
			break;
		case 4:
			displayAllAccountDetailRecords(acc->accounts, acc->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;
		case 5:
			//printf("\nFeature #%d currently unavailable!", selection);

			do
			{

				DisplayTicketHeader();
				for (i = 0;i < acc->TICKET_MAX_SIZE;i++)
				{
					if (acc->tickets[i].counter == 1)
					{
						for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
							if (acc->tickets[i].account_number == acc->accounts[j].account_number )
								break;
						if (acc->tickets[i].ticket_status == 1)
							printf("%06d %05d %-15s ACTIVE %-30s %5d\n", acc->tickets[i].ticket_number, acc->tickets[i].account_number , acc->accounts[j].person.name, acc->tickets[i].subjectLine, acc->tickets[i].counter);
					}

				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &tnumber);

				if (tnumber != 0)
				{
					for (i = 0;i < acc->TICKET_MAX_SIZE; i++)
					{
						if (acc->tickets[i].ticket_number == tnumber)
							if (acc->tickets[i].counter== 1)
								if (acc->tickets[i].ticket_status== 1)
									break;
					}
					if (i == acc->TICKET_MAX_SIZE)
					{
						printf("\nERROR: Invalid ticket number.\n");
					}
					else
					{
						DisplayTicketDetails(acc->tickets[i]);
					}
					pauseExecution();
					getchar();
				}
			} while (tnumber != 0);

			break;
		case 6:
			//printf("\nFeature #%d currently unavailable!", selection);

			do
			{
				DisplayTicketHeader();
				for (i = 0;i < acc->TICKET_MAX_SIZE;i++)
				{
					if (acc->tickets[i].ticket_status== 1)
					{
						for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
							if (acc->tickets[i].account_number == acc->accounts[j].account_number )
								break;

						printf("%06d %05d %-15s ACTIVE %-30s %5d\n", acc->tickets[i].ticket_number, acc->tickets[i].account_number , acc->accounts[j].person.name, acc->tickets[i].subjectLine, acc->tickets[i].counter);
					}

				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &tnumber);

				if (tnumber != 0)
				{
					for (i = 0;i < acc->TICKET_MAX_SIZE; i++)
					{
						if (acc->tickets[i].ticket_number == tnumber)
							if (acc->tickets[i].ticket_status== 1)
								break;
					}
					if (i == acc->TICKET_MAX_SIZE)
					{
						printf("\nERROR: Invalid ticket number.\n");
					}
					else
					{
						DisplayTicketDetails(acc->tickets[i]);
					}
					pauseExecution();
					getchar();
				}

			} while (tnumber != 0);

			break;
		case 7:
			//printf("\nFeature #%d currently unavailable!", selection);
			do
			{

				DisplayTicketHeader();
				for (i = 0;i < acc->TICKET_MAX_SIZE;i++)
				{
					if (acc->tickets[i].ticket_status== 0 && acc->tickets[i].counter>= 1)
					{
						for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
							if (acc->tickets[i].account_number == acc->accounts[j].account_number )
								break;

						printf("%06d %05d %-15s CLOSED %-30s %5d\n", acc->tickets[i].ticket_number, acc->tickets[i].account_number , acc->accounts[j].person.name, acc->tickets[i].subjectLine, acc->tickets[i].counter);
					}

				}
				printf("------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &tnumber);

				if (tnumber != 0)
				{
					for (i = 0;i < acc->TICKET_MAX_SIZE; i++)
					{
						if (acc->tickets[i].ticket_number == tnumber)
							if (acc->tickets[i].ticket_status== 0)
								break;
					}
					if (i == acc->TICKET_MAX_SIZE)
					{
						printf("\nERROR: Invalid ticket number.\n");
					}
					else
					{
						DisplayTicketDetails(acc->tickets[i]);
					}
					pauseExecution();
					getchar();
				}

			} while (tnumber != 0);



			break;
		case 8:
			//printf("\nFeature #%d currently unavailable!", selection);

			printf("\nEnter the account#: ");
			acNumber = getPositiveInteger();
			for (i = 0;i < acc->ACCOUNT_MAX_SIZE; i++)
				if (acNumber == acc->accounts[i].account_number )
					break;
			if (i == acc->ACCOUNT_MAX_SIZE)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n");
				pauseExecution();
			}
			else
			{
				if (acc->accounts[i].account_type== 'A')
				{
					printf("\nERROR: Agent accounts can't have tickets!\n");
					pauseExecution();
				}
				else
				{

					displayAccountDetailHeader();
					displayAccountDetailRecord(&acc->accounts[i]);

					printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
					confirm = getCharOption("YyNn");

					if (confirm == 'Y' || confirm == 'y')
					{
						tnumber = acc->tickets[0].ticket_number;
						for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
						{
							if (tnumber < acc->tickets[j].ticket_number)
							{
								tnumber = acc->tickets[j].ticket_number;
							}
						}

						for (j = 0;j < acc->TICKET_MAX_SIZE;j++)
							if (acc->tickets[j].ticket_number == 0)
								break;

						int j;
						tnumber = acc->tickets[0].ticket_number;
						for (j = 0;j < acc->ACCOUNT_MAX_SIZE;j++)
						{
							if (tnumber < acc->tickets[j].ticket_number)
							{
								tnumber = acc->tickets[j].ticket_number;;
							}
						}

						for (j = 0;j < acc->TICKET_MAX_SIZE;j++)
							if (acc->tickets[j].ticket_number == 0)
								break;
						acc->tickets[j].ticket_number = tnumber + 1;
						acc->tickets[j].ticket_status= 1;
						acc->tickets[j].account_number = acc->accounts[i].account_number ;
						acc->tickets[j].message[0].account_type= 'C';
						strcpy(acc->tickets[j].message[0].name, acc->accounts[i].person.name);
						printf("\nNew Ticket (Ticket#:%06d)", acc->tickets[j].ticket_number);
						printf("\n----------------------------------------");
						printf("\nEnter the ticket SUBJECT (30 chars. maximum): ");
						getCString(acc->tickets[j].subjectLine, 1, 30);

						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(acc->tickets[j].message[0].messageDetails, 1, 150);
						acc->tickets[j].counter= 1;

						printf("\n*** New ticket created! ***\n");



						pauseExecution();
					}
				}
			}
			break;
		case 9:
			//printf("\nFeature #%d currently unavailable!", selection);
			printf("\nEnter ticket number: ");
			tnumber = getPositiveInteger();

			for (i = 0;i < acc->TICKET_MAX_SIZE;i++)
				if (tnumber == acc->tickets[i].ticket_number)
					break;
			if (i == acc->TICKET_MAX_SIZE)
			{
				printf("Invalid Ticket Number!\n");
				pauseExecution();
			}
			else
			{
				int choice;
				do
				{
					printf("\n----------------------------------------");
					printf("\nTicket %06d - Update Options", acc->tickets[i].ticket_number);
					printf("\n----------------------------------------");
					if (acc->tickets[i].ticket_status== 1)
						printf("\nStatus  : ACTIVE");
					else
						printf("\nStatus  : CLOSED");
					printf("\nSubject : %s", acc->tickets[i].subjectLine);
					printf("\nAcct#   : %d", acc->tickets[i].account_number );
					printf("\nCustomer: %s", acc->tickets[i].message[0].name);
					printf("\n----------------------------------------");
					printf("\n1) Add CUSTOMER message");
					printf("\n2) Add AGENT message");
					printf("\n3) Close ticket");
					printf("\n4) Re-activate ticket");
					printf("\n0) Done");
					printf("\nSelection: ");
					choice = getIntFromRange(0, 4);

					switch (choice)
					{
					case 1:
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(acc->tickets[i].message[acc->tickets[i].counter].messageDetails, 1, 150);
						strcpy(acc->tickets[i].message[acc->tickets[i].counter].name, acc->tickets[i].message->name);
						acc->tickets[i].message[acc->tickets[i].counter].account_type= 'C';
						acc->tickets[i].counter++;
						break;
					case 2:
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(acc->tickets[i].message[acc->tickets[i].counter].messageDetails, 1, 150);
						strcpy(acc->tickets[i].message[acc->tickets[i].counter].name, account->person.name);
						acc->tickets[i].message[acc->tickets[i].counter].account_type= 'A';
						acc->tickets[i].counter++;
						break;
					case 3:

						if (acc->tickets[i].ticket_status== 0)
							printf("\nERROR: Ticket is already closed!\n");
						else
						{
							printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
							char aa = getCharOption("YyNn");
							if (aa == 'Y' || aa == 'y')
							{
								acc->tickets[i].ticket_status= 0;
								printf("\n*** Ticket closed! ***\n");
							}
						}

						break;
					case 4:
						if (acc->tickets[i].ticket_status== 1)
							printf("\nERROR: Ticket is already active!\n");
						else
						{
							printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
							char aa = getCharOption("YyNn");
							if (aa == 'Y' || aa == 'y')
							{
								acc->tickets[i].ticket_status= 1;
								printf("\n*** Ticket re-activated! ***\n");
							}
						}

						break;
					case 0:
						break;
					default:
						break;
					}

				} while (choice != 0);
			}

			break;
		case 0:
			printf("\nSaving session modifications...");
			Saved_record = saveAccounts(acc->accounts, acc->ACCOUNT_MAX_SIZE);
			printf("\n   %d account(s) saved.", Saved_record);
			Saved_record = saveTickets(acc->tickets, acc->TICKET_MAX_SIZE);
			printf("\n   %d ticket(s) saved.", Saved_record);
			printf("\n### LOGGED OUT ###\n\n");
			break;
		default:
			break;
		}
	} while (selection != 0);

}
int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int max, int flag)
{
	int i;
	if (flag != 0)
	{
		printf("Enter the account#: ");
		accountNumber = getPositiveInteger();
	}
	for (i = 0;i < max;i++)
		if (accountNumber == accounts[i].account_number )
			break;
	if (i == max)
		i = -1;

	return i;
}
void displayAllAccountDetailRecords(const struct Account accounts[], int max)
{
	int i;
	displayAccountDetailHeader();
	for (i = 0;i < max;i++)
	{
		if (accounts[i].account_number != 0)
			displayAccountDetailRecord(&accounts[i]);
	}
}






void pauseExecution(void)
{
	printf("\n<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	//putchar('\n');
}