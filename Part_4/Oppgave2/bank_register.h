#ifndef BANK_REGISTER_H
#define BANK_REGISTER_H
#include <stdio.h>

struct clientData {
    long acctNum;
    char lastName[ 100];
    char firstName[ 100 ];
    double balance;
};




/* prototypes */
int enterChoice( void );
void textFile( FILE *readPtr );
void updateRecord( FILE *fPtr );
void newRecord( FILE *fPtr );
void deleteRecord( FILE *fPtr );


#endif
