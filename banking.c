#include "banking.h"

Account* createAccount(int id, const char* name, const char* accountType, float balance) {
    Account* account = (Account*)malloc(sizeof(Account));
    if (!account) return NULL;
    account->id = id;
    strncpy(account->name, name, MAX_NAME_LENGTH - 1);
    account->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(account->accountType, accountType, MAX_ACCOUNT_TYPE - 1);
    account->accountType[MAX_ACCOUNT_TYPE - 1] = '\0';
    account->balance = balance;
    account->transactions = NULL;
    account->next = NULL;
    return account;
}

void addTransaction(Account* account, const char* type, float amount, const char* date, const char* details) {
    Transaction* txn = (Transaction*)malloc(sizeof(Transaction));
    if (!txn || !account) return;
    strncpy(txn->type, type, sizeof(txn->type) - 1);
    txn->type[sizeof(txn->type) - 1] = '\0';
    txn->amount = amount;
    strncpy(txn->date, date, sizeof(txn->date) - 1);
    txn->date[sizeof(txn->date) - 1] = '\0';
    strncpy(txn->details, details, sizeof(txn->details) - 1);
    txn->details[sizeof(txn->details) - 1] = '\0';
    txn->next = account->transactions;
    account->transactions = txn;
}

Account* findAccount(Account* head, int id) {
    while (head) {
        if (head->id == id) return head;
        head = head->next;
    }
    return NULL;
}

void deposit(Account* account, float amount) {
    if (!account || amount <= 0) return;
    account->balance += amount;
    addTransaction(account, "Deposit", amount, "2026-07-14", "Manual deposit");
}

int withdraw(Account* account, float amount) {
    if (!account || amount <= 0 || amount > account->balance) return 0;
    account->balance -= amount;
    addTransaction(account, "Withdrawal", amount, "2026-07-14", "Manual withdrawal");
    return 1;
}

int transfer(Account* from, Account* to, float amount) {
    if (!from || !to || amount <= 0 || amount > from->balance) return 0;
    from->balance -= amount;
    to->balance += amount;
    addTransaction(from, "Transfer", amount, "2026-07-14", "Sent transfer");
    addTransaction(to, "Transfer", amount, "2026-07-14", "Received transfer");
    return 1;
}

Account* loadAccounts(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    Account* head = NULL;
    Account* tail = NULL;
    int id;
    char name[MAX_NAME_LENGTH];
    char accountType[MAX_ACCOUNT_TYPE];
    float balance;

    while (fscanf(file, "%d,%99[^,],%19[^,],%f\n", &id, name, accountType, &balance) == 4) {
        Account* account = createAccount(id, name, accountType, balance);
        if (!account) continue;
        if (!head) head = account;
        else tail->next = account;
        tail = account;
    }

    fclose(file);
    return head;
}

void saveAccounts(Account* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    while (head) {
        fprintf(file, "%d,%s,%s,%.2f\n", head->id, head->name, head->accountType, head->balance);
        head = head->next;
    }

    fclose(file);
}

void freeAccounts(Account* head) {
    while (head) {
        Transaction* txn = head->transactions;
        while (txn) {
            Transaction* nextTxn = txn->next;
            free(txn);
            txn = nextTxn;
        }
        Account* nextAccount = head->next;
        free(head);
        head = nextAccount;
    }
}
