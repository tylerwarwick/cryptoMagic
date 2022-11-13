#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("Enter it gangy: ");

    char emptyArray[30];
    fgets(emptyArray, 30, stdin);

    const char* space = " ";
    char* token = strtok(emptyArray, space);

    while(token != NULL ) {
      printf( " %s\n", token );
    
      token = strtok(NULL, emptyArray);
   }
    printf("\n%s", emptyArray);
}

