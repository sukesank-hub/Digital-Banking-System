#include "ui.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showMainMenu() {
    printf("==============================\n");
    printf("   Digital Banking System     \n");
    printf("==============================\n\n");
    printf("1. View Account Summary\n");
    printf("2. View Statements\n");
    printf("3. Transfer Money\n");
    printf("4. Exit\n\n");
    printf("Choose an option: ");
}

int getMenuChoice() {
    int choice;
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return choice;
}

void displayAccountSummary(Account* account) {
    if (!account) {
        printf("No account available.\n");
        return;
    }

    printf("Account Summary\n");
    printf("---------------\n");
    printf("ID: %d\n", account->id);
    printf("Name: %s\n", account->name);
    printf("Type: %s\n", account->accountType);
    printf("Balance: $%.2f\n", account->balance);
}

void displayTransactions(Account* account) {
    if (!account) {
        printf("No account available.\n");
        return;
    }

    printf("Recent Transactions\n");
    printf("-------------------\n");
    if (!account->transactions) {
        printf("No transactions found.\n");
        return;
    }

    Transaction* txn = account->transactions;
    while (txn) {
        printf("%s: $%.2f - %s (%s)\n", txn->type, txn->amount, txn->details, txn->date);
        txn = txn->next;
    }
}

void displayMessage(const char* message) {
    printf("%s\n", message);
}

void promptContinue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}
