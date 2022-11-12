#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int main( int argc, char *argv[] ) 
{
   char * mode =  argv[1];
   char * fileName =  argv[2];

   printf("Mode: %s\nFile Name: %s\n", mode, fileName);


   return 0;
 
}