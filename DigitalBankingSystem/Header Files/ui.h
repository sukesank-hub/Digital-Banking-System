#ifndef UI_H
#define UI_H

#include "banking.h"

void showMainMenu();
int getMenuChoice();
void displayAccountSummary(Account* account);
void displayTransactions(Account* account);
void displayMessage(const char* message);
void promptContinue();
void clearScreen();

#endif // UI_H
