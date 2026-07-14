#include "banking.h"
#include "ui.h"

int main() {
    Account* accounts = loadAccounts(DATA_FILE);
    if (!accounts) {
        accounts = createAccount(1, "Alex", "Savings", 24580.00f);
        addTransaction(accounts, "Deposit", 24580.00f, "2026-07-14", "Initial balance");
        saveAccounts(accounts, DATA_FILE);
    }

    int choice;
    Account* active = accounts;

    while (1) {
        clearScreen();
        showMainMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                clearScreen();
                displayAccountSummary(active);
                promptContinue();
                break;
            case 2:
                clearScreen();
                displayTransactions(active);
                promptContinue();
                break;
            case 3:
                clearScreen();
                displayMessage("Feature not implemented yet.\n");
                promptContinue();
                break;
            case 4:
                saveAccounts(accounts, DATA_FILE);
                freeAccounts(accounts);
                return 0;
            default:
                displayMessage("Invalid choice. Please try again.\n");
                promptContinue();
                break;
        }
    }
}
