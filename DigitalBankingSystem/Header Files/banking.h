#ifndef BANKING_H
#define BANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_ACCOUNT_TYPE 20
#define DATA_FILE "Data/accounts.txt"

typedef struct Transaction {
    char type[20];
    float amount;
    char date[20];
    char details[128];
    struct Transaction* next;
} Transaction;

typedef struct Account {
    int id;
    char name[MAX_NAME_LENGTH];
    char accountType[MAX_ACCOUNT_TYPE];
    float balance;
    Transaction* transactions;
    struct Account* next;
} Account;

Account* loadAccounts(const char* filename);
void saveAccounts(Account* head, const char* filename);
Account* createAccount(int id, const char* name, const char* accountType, float balance);
Account* findAccount(Account* head, int id);
void deposit(Account* account, float amount);
int withdraw(Account* account, float amount);
int transfer(Account* from, Account* to, float amount);
void addTransaction(Account* account, const char* type, float amount, const char* date, const char* details);
void freeAccounts(Account* head);

#endif // BANKING_H
