
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#include "account.h"
#include "ticket.h"

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

void displayAccountDetailHeader();

void displayAccountDetailRecord(const struct Account*);

//There is no need to define variable name when we declaring function

void applicationStartup(struct AccountTicketingData* data);

int menuLogin(const struct Account[], int);

void menuAgent(struct AccountTicketingData*, const struct Account*);

int findAccountIndexByAcctNum(int, const struct Account[], int, int);

void displayAllAccountDetailRecords(const struct Account[], int);

void pauseExecution(void);

#endif // !ACCOUNT_TICKETING_UI_H_
