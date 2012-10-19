#include <stdio.h>
#include "bank_register.h"

int main( void )
{ 
   int i; 

   struct clientData blankClient = {0, "", "", 0.0 }; 
   
   FILE *cfPtr; 

   if ( ( cfPtr = fopen( "backup.bak", "wb" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } 
   else { 
 
      for ( i = 1; i <= 100; i++ ) {
         fwrite( &blankClient, sizeof( struct clientData ), 1, cfPtr );
      } 

      fclose ( cfPtr ); 
   } 

   return 0;
}
