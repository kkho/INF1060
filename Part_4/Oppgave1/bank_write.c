#include <stdio.h>
#include "bank_register.h"

int main(void) {
    FILE *cfPtr;

    struct clientData client = {0, "", "", 0.0};

    if ((cfPtr = fopen("backup.bak", "rb+")) == NULL) {
        printf("File could not be opened.\n");
    }
    else {

        printf("Enter account number"
                " ( 1 to 100, 0 to end input )\n? ");
        scanf("%d", &client.acctNum);

        while (client.acctNum != 0) {
            printf("Enter lastname, firstname, balance\n? ");

            fscanf(stdin, "%s%s%lf", client.lastName,
                    client.firstName, &client.balance);

            fseek(cfPtr, (client.acctNum - 1) *
                    sizeof ( struct clientData), SEEK_SET);

            fwrite(&client, sizeof ( struct clientData), 1, cfPtr);

            printf("Enter account number\n? ");
            scanf("%d", &client.acctNum);
        } /* end while */

        fclose(cfPtr);
    }

    return 0;
}

