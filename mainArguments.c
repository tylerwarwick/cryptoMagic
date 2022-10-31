#include <stdio.h>

/*
FILE processInputFile(char n)
{       
    FILE * uf;

    uf = fopen(&n, "r+");
}


void encrypt(void)
{

}

void decrypt(void)
{

}
*/

int main( int argc, char *argv[] ) 
{
   char* mode = argv[1];
   char* fileName = argv[2];

   printf("Mode: %s\nFile Name: %s\n", mode, fileName);
 
}