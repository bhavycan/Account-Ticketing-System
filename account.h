
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#ifndef ACCOUNT_H_
#define ACCOUNT_H_ 

struct Person
{
	char name[31];
	int birth_year;
	double income;
	char country[31];
};

struct UserLogin
{
	char loginName[11];
	char pass[9];
};

struct Account
{

	int account_number;
	char account_type;
	struct Person person;
	struct UserLogin login;
};

void getAccount(struct Account*, int);

void getPerson(struct Person*);

void getUserLogin(struct UserLogin*);

void updateAccount(struct Account*);

void updatePerson(struct Person*);

void updateUserLogin(struct UserLogin*);
int loadAccounts(struct Account*, int);

int saveAccounts(struct Account*, int);



#endif // !ACCOUNT_H_
