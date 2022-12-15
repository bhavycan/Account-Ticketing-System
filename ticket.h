
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#ifndef TICKET_H_
#define TICKET_H_

#define LENGTH_OF_MESSAGE 150
#define NAME 30
#define SUBJECTLINE_LENGTH 30


struct Message
{
	char account_type;
	char name[NAME + 1];
	char messageDetails[LENGTH_OF_MESSAGE + 1];
};

struct Ticket
{
	int ticket_number;
	int account_number;
	int ticket_status;
	char subjectLine[SUBJECTLINE_LENGTH + 1];
	int counter;
	struct Message message[20];
};
//**************************************************Ticket.c Function Declaration***************************************************

void DisplayTicketHeader();

void DisplayTicketDetails(struct Ticket);	//At the declaration  time, we dont need to define variable name

int saveTickets(struct Ticket*, int);

int loadTickets(struct Ticket*, int);

#endif // TICKET_H_
