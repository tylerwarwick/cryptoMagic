#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Opens and stores text file
FILE * openInputFile(char* n)
{       
    FILE * openedFile = fopen(n, "r");

    if (openedFile == NULL) 
    {
        printf("File couldn't be opened\n");
    }

    return openedFile;
}   

int readInputFile(FILE* k)
{
    int readFile = fprintf//(IDK what to put here);
    return readFile;
}

/*
void encrypt(void)
{

}

void decrypt(void)
{

}
*/

int main( int argc, char *argv[] ) 
{
   char * mode =  argv[1];
   char * fileName =  argv[2];

   printf("Mode: %s\nFile Name: %s\n", mode, fileName);


   return 0;
 
}