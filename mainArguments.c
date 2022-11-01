#include <stdio.h>
#include <string.h>


FILE* openInputFile(char* n)
{       
    FILE * uf;

    uf = fopen(n, "r+");
    return uf;
}

char* readInputFile(FILE* k)
{
    int readFile = fprintf(k);
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
   FILE* givenFile;
   char * mode =  argv[1];
   char * fileName =  argv[2];

   printf("Mode: %s\nFile Name: %s\n", mode, fileName);

   givenFile = openInputFile(fileName);
   


   return 0;
 
}