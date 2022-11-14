#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("Enter it gangy: ");
    /*
    char emptyArray[30];
    fgets(emptyArray, sizeof emptyArray, stdin);

    int i = 0;
    char* arrayOfWords[30];
    const char* delimit = " ";
    char* token = strtok(emptyArray, delimit);


    arrayOfWords[i] = strtok(emptyArray, delimit);

    while(token != NULL ) 
    {
      printf( " %s\n", token );
      token = strtok(NULL, delimit);
      i++;
      arrayOfWords[i] = strtok(NULL, delimit);
    }

    printf("%d", i);
    */

   
  char input[1024];
  char *string[256];            
                                
  char delimit[]=" \t\r\n\v\f"; 
  int i = 0, j = 0;

    if(fgets(input, sizeof input, stdin))                             
        {                                        
            string[i]=strtok(input,delimit);    
            while(string[i]!=NULL)                    
            {
                printf("string [%d]=%s\n",i,string[i]);
                i++;
                string[i]=strtok(NULL,delimit);
            }
        }

        printf("%d", i);
  return 0;
}


