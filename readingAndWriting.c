#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Opens and stores text file
FILE* openInputFile(char* n);

//Opens file for us to write to
FILE* openNewFile(char* n);

//Encrypts file
void encryptFile(FILE* read, FILE* write);

//Decrypts File
void decryptFile(FILE* k);




int main(void)
{
    char* sampleTextFile = ("text.txt");
    char* sampleNewFile = ("posttext4.txt");

    FILE* inputFile = openInputFile(sampleTextFile);
    FILE* newFile = openNewFile(sampleNewFile);

    encryptFile(inputFile, newFile);

    fclose(inputFile);
    fclose(newFile);
}

//Opens file for us to write to
FILE* openNewFile(char* n)
{       
    FILE * writingFile = fopen(n, "w");
    if (writingFile == NULL) 
    {
        printf("New file couldn't be opened\n");
    }

    return writingFile;
    
}   

//Opens and stores text file
FILE* openInputFile(char* n)
{       
    FILE * readingFile = fopen(n, "r");
    if (readingFile == NULL) 
    {
        printf("Input file couldn't be opened\n");
    }

    return readingFile;
    
}   

void encryptFile(FILE* read, FILE* write)
{
    char c;

    while ((c = fgetc(read)) != EOF) 
    {
        int outChar = c; /*= ((int)c - 16);

        if (outChar < 32)
        {
            outChar = ((outChar - 32) + 144);
        }
        */
        
        fputc(outChar, write);

    }
    
}