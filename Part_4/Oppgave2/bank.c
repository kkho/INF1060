#include "bank_register.h"

int main(void) {
    FILE *cfPtr;
    int choice;

    if ((cfPtr = fopen("backup.bak", "rb+")) == NULL) {
        printf("File could not be opened.\n");
    }
    else {

        while ((choice = enterChoice()) != 5) {
            switch (choice) {
                case 1:
                    textFile(cfPtr);
                    break;
                case 2:
                    updateRecord(cfPtr);
                    break;
                case 3:
                    newRecord(cfPtr);
                    break;
                case 4:
                    deleteRecord(cfPtr);
                    break;
                default:
                    printf("Incorrect choice\n");
                    break;
            }
        }

        fclose(cfPtr);
    }

    return 0;
}

/**
 * make a textfile of records of the account information
 * @param readPtr
 *
 */

void textFile(FILE *readPtr) {
    FILE *writePtr;

    struct clientData client = {0, "", "", 0.0};

    if ((writePtr = fopen("accounts.txt", "w")) == NULL) {
        printf("File could not be opened.\n");
    }
    else {
        rewind(readPtr);
        fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
                "Acct", "Last Name", "First Name", "Balance");

        while (!feof(readPtr)) {
            fread(&client, sizeof ( struct clientData), 1, readPtr);

            if (client.acctNum != 0) {
                fprintf(writePtr, "%-6ld%-16s%-11s%10.2f\n",
                        client.acctNum, client.lastName,
                        client.firstName, client.balance);
            }
        }

        fclose(writePtr);
    }
}

/**
 * updates the account with given balance
 * @param fPtr
 */
void updateRecord(FILE *fPtr) {
    int account;
    double transaction;

    struct clientData client = {0, "", "", 0.0};

    printf("Enter account to update ( 1 - 100 ): ");
    scanf("%d", &account);

    fseek(fPtr, (account - 1) * sizeof ( struct clientData),
            SEEK_SET);

    fread(&client, sizeof ( struct clientData), 1, fPtr);

    if (client.acctNum == 0) {
        printf("Acount #%d has no information.\n", account);
    }
    else {
        printf("%-6ld%-16s%-11s%10.2f\n\n",
                client.acctNum, client.lastName,
                client.firstName, client.balance);

        /* request transaction amount from user */
        printf("Enter charge ( + ) or payment ( - ): ");
        scanf("%lf", &transaction);
        client.balance += transaction;

        printf("%-6ld%-16s%-11s%10.2f\n",
                client.acctNum, client.lastName,
                client.firstName, client.balance);

        /* move file pointer to correct record in file */
        fseek(fPtr, (account - 1) * sizeof ( struct clientData),
                SEEK_SET);

        /* write updated record over old record in file */
        fwrite(&client, sizeof ( struct clientData), 1, fPtr);
    }
}

/**
 * delete an existing record
 * @param fPtr
 */
void deleteRecord(FILE *fPtr) {
    struct clientData client;
    struct clientData blankClient = {0, "", "", 0};

    int accountNum;

    /* obtain number of account to delete */
    printf("Enter account number to delete ( 1 - 100 ): ");
    scanf("%d", &accountNum);

    /* move file pointer to correct record in file */
    fseek(fPtr, (accountNum - 1) * sizeof ( struct clientData),
            SEEK_SET);

    /* read record from file */
    fread(&client, sizeof ( struct clientData), 1, fPtr);

    if (client.acctNum == 0) {
        printf("Account %d does not exist.\n", accountNum);
    }
    else {
        fseek(fPtr, (accountNum - 1) * sizeof ( struct clientData),
                SEEK_SET);

        /* replace existing record with blank record */
        fwrite(&blankClient,
                sizeof ( struct clientData), 1, fPtr);
    }
}

/**
 * create and insert record
 * @param fPtr
 */
void newRecord(FILE *fPtr) {
    struct clientData client = {0, "", "", 0.0};

    int accountNum;

    /* obtain number of account to create */
    printf("Enter new account number ( 1 - 100 ): ");
    scanf("%d", &accountNum);

    fseek(fPtr, (accountNum - 1) * sizeof ( struct clientData),
            SEEK_SET);

    fread(&client, sizeof ( struct clientData), 1, fPtr);

    if (client.acctNum != 0) {
        printf("Account #%ld already contains information.\n",
                client.acctNum);
    }
    else {

        printf("Enter lastname, firstname, balance\n? ");
        scanf("%s%s%lf", client.lastName, client.firstName,
                &client.balance);

        client.acctNum = accountNum;

        fseek(fPtr, (client.acctNum - 1) *
                sizeof ( struct clientData), SEEK_SET);

        fwrite(&client,
                sizeof ( struct clientData), 1, fPtr);
    }
}

/**
 * enable user to input menu choice
 * @return menuChoice
 */
int enterChoice(void) {
    int menuChoice;

    printf("\nEnter your choice\n"
            "1 - store a formatted text file of acounts called\n"
            "    \"accounts.txt\" for printing\n"
            "2 - update an account\n"
            "3 - add a new account\n"
            "4 - delete an account\n"
            "5 - end program\n? ");

    scanf("%d", &menuChoice);
    return menuChoice;
}
