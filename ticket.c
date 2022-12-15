// #############################################################################################
//  Assignment: 2 
//  Milestone : 4

// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "accountTicketingUI.h"
#include "commonHelpers.h"

void DisplayTicketHeader()
{
	printf("\n------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void DisplayTicketDetails(struct Ticket ticket)
{
	char status[7], ch[10];
	int j;

	if (ticket.ticket_status == 1)
		strcpy(status, "ACTIVE");
	else
		strcpy(status, "CLOSED");

	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticket.ticket_number, status, ticket.subjectLine);
	printf("================================================================================");

	for (j = 0; j < ticket.counter; j++)
	{
		if (ticket.message[j].account_type == 'A')
			strcpy(ch, "AGENT");
		else
			strcpy(ch, "CUSTOMER");

		printf("\n%s (%s):\n", ch, ticket.message[j].name);
		printf("   %s\n", ticket.message[j].messageDetails);
	}

}

int loadTickets(struct Ticket* tickets, int TICKET_SIZE)
{
	FILE* fp = NULL;
	char* info;
	int i = 0, flag = 0, j = 0, m = 0, n = 1;
	char tkt[1500];
	char char1[2] = "|";

	fp = fopen("tickets.txt", "r");


	while (fscanf(fp, "%[^\n] ", tkt) != EOF && flag == 0)
	{
		info = strtok(tkt, char1);
		while (info)
		{
			if (j == 0)
				tickets[i].ticket_number = atoi(info);
			else if (j == 1)
				tickets[i].account_number = atoi(info);
			else if (j == 2)
				tickets[i].ticket_status = atoi(info);
			else if (j == 3)
				strcpy(tickets[i].subjectLine, info);
			else if (j == 4)
				tickets[i].counter = atoi(info);
			else if (j == 5)
			{
				if (n % 3 == 1)
				{
					if (!strcmp(info, "A"))
						tickets[i].message[m].account_type = 'A';
					else
						tickets[i].message[m].account_type = 'C';
				}
				else if (n % 3 == 2)
					strcpy(tickets[i].message[m].name, info);
				else if (n % 3 == 0)
				{
					strcpy(tickets[i].message[m].messageDetails, info);
					m++;
				}

				n++;
			}

			if (j < 5)
				j++;

			info = strtok(NULL, char1);
		}
		j = 0;
		n = 1;
		m = 0;
		i++;
		if (i == TICKET_SIZE)
			flag = 1;
	}
	fclose(fp);

	return i;
}

int saveTickets(struct Ticket* tickets, int TICKET_MAX_SIZE)
{
	FILE* fp = NULL;
	int i, j, count = 0;
	

	fp = fopen("tickets.txt", "w");

	if (fp != NULL)
	{
		for (i = 0; i < TICKET_MAX_SIZE; i++)
		{
			if (tickets[i].ticket_number != 0)
			{
				count++;
				fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticket_number, tickets[i].account_number, tickets[i].ticket_status, tickets[i].subjectLine, tickets[i].counter);
				for (j = 0; j < tickets[i].counter; j++)
				{
					fprintf(fp, "%c|%s|%s|", tickets[i].message[j].account_type, tickets[i].message[j].name, tickets[i].message[j].messageDetails);
				}
				fprintf(fp, "\n");
			}

		}
		fclose(fp);
	}
	else
	{
		printf("\nFailed to open the file.\n");
	}
	return count;
}