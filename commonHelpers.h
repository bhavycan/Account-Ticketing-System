
// #############################################################################################
//  Student Name  : Patel Bhavy Pyushkumar
//  Student ID    : 121048219
//  Student Email : bppatel16@myseneca.ca
//  Course Section: NMM
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_


int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger();
int getPositiveInteger();
int getIntFromRange(int, int);
double getDouble();
double getPositiveDouble();
char getCharOption(char[]);
void getCString(char*, int, int);

int countUpper(const char* str);
int countLower(const char* str);
int countDigit(const char* str);
int countSymbol(const char* str);
void convertUpper(char* str);

#endif // !COMMON_HELPERS_H_