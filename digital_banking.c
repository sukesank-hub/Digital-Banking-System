#include <stdio.h>
#include <stdlib.h>

void waitForEnter() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}

int main() {
    float balance = 10000.00f;
    int choice = 0;
    float amount = 0.0f;
    char account[40];

    while (1) {
        printf("==============================\n");
        printf("   Digital Banking System     \n");
        printf("==============================\n\n");
        printf("Welcome back, Alex\n");
        printf("Available Balance: $%.2f\n\n", balance);
        printf("Please choose an option:\n");
        printf("1. View Balance\n");
        printf("2. Transfer Money\n");
        printf("3. View Statements\n");
        printf("4. Exit\n\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid selection. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("\nCurrent balance: $%.2f\n", balance);
                waitForEnter();
                break;

            case 2:
                printf("\nEnter transfer amount: $");
                if (scanf("%f", &amount) != 1 || amount <= 0.0f) {
                    printf("Invalid amount.\n");
                    while (getchar() != '\n');
                    waitForEnter();
                    break;
                }
                while (getchar() != '\n');
                if (amount > balance) {
                    printf("Insufficient funds for this transfer.\n");
                } else {
                    printf("Enter recipient account name: ");
                    fgets(account, sizeof(account), stdin);
                    if (account[0] == '\n') {
                        printf("Recipient account is required.\n");
                    } else {
                        if (account[strlen(account) - 1] == '\n') {
                            account[strlen(account) - 1] = '\0';
                        }
                        balance -= amount;
                        printf("Transferred $%.2f to %s successfully.\n", amount, account);
                        printf("New balance: $%.2f\n", balance);
                    }
                }
                waitForEnter();
                break;

            case 3:
                printf("\nRecent Statements:\n");
                printf("- Deposit: $5,000.00 on 2026-07-01\n");
                printf("- Bill payment: $120.50 on 2026-07-05\n");
                printf("- Transfer: $450.00 to sam thambi 2026-07-08\n");
                printf("- ATM withdrawal: $200.00 on 2026-07-10\n");
                waitForEnter();
                break;

            case 4:
                printf("\nThank you for using the digital banking system.\n");
                return 0;

            default:
                printf("Invalid choice. Please select 1-4.\n");
                waitForEnter();
                break;
        }

        printf("\n");
    }

    return 0;
}
