#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Opens and stores text file
FILE* openInputFile(char* n);

//Opens file for us to write to
FILE* openNewFile(char* n);

int hexStringToInt(char c);

//Converts hex to ASCII values
int hexStringToDecimal(char c1, char c2);

//Encrypts and decrypts files
FILE* encryptFile(FILE* inputFile, FILE* outputFile);
FILE* decryptFile(FILE* inputFile, FILE* outputFile);


int main(void)
{
    FILE* x = openInputFile("postEncryption2.crp");
    FILE* y = openNewFile("wordtest2.txt");

    FILE* c = decryptFile(x, y);

    fclose(x);
    fclose(y);
}

//Opens file for us to write to
FILE* openNewFile(char* n)
{       
    FILE * writingFile = fopen(n, "w");
    if (writingFile == NULL) 
    {
        printf("Output file couldn't be opened\n");
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

int hexStringToInt(char c)
    {
    if (c >= 97) c = c - 32;

    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
    
    }

int hexStringToDecimal(char c1, char c2)
{
    int newc1 = hexStringToInt(c1) * 16;
    int newc2 = hexStringToInt(c2);
    int result = newc1 + newc2;
    return result;
}


FILE* encryptFile(FILE* inputFile, FILE* outputFile)
{
    char lineContents[121];
    char* newLine= "\n";

    //Get a line from the file until end of file
    while (fgets(lineContents, 120, inputFile) != NULL)
    {   
        //Parse over every character of line 
        for (int i = 0; lineContents[i] != '\0'; i++) 
        {
            int outChar;
            char c = lineContents[i];
            char* tab = "TT";

            //Special cases for tab and carriage return
            if (c == 6 || c == 9 || c == 10 || c == 13)
            {

            //If input is tab then write TT
                if (c == 9)
                {
                    fprintf(outputFile, "%s", tab);
                }

            /*
            Ignore acknowledgement, line feed and carriage return
            Since we are processing line by line we don't need to use these as indicators
            We will just print a newline character after processing each line
            */
                else if (c == 6 || c == 10 || c == 13)
                {
                    continue;
                }
            }

            //Otherwise apply encryption key
           else
            {
                outChar = (c - 16);

                if (outChar < 32)
                {
                    outChar = (outChar - 32) + 144;
                }

                fprintf(outputFile, "%X", outChar);
            }
        }

        fprintf(outputFile, "%s", newLine);
    }
    
    return outputFile;
}

FILE* decryptFile(FILE* inputFile, FILE* outputFile)
{   
    char* tab = "\t";
    char lineContents[256];
    char* newLine= "\n";

    //Get a line from the file until end of file
    while (fgets(lineContents, 120, inputFile) != NULL)
    {   
        //Parse over every character of line 
        for (int i = 0; lineContents[i] != '\0'; i += 2) 
        {
            if (lineContents[i] == 'T' && lineContents[i + 1] == 'T') 
            {
                fprintf(outputFile, "%s", tab);
            }

            else
            {
                int outChar;
                outChar = hexStringToDecimal(lineContents[i], lineContents[i + 1]);
                outChar += 16;

                if (outChar > 127)
                {
                    outChar = (outChar - 144) + 32;
                }

                fprintf(outputFile, "%c", outChar);
            
            }
        }
        fprintf(outputFile, "%s", newLine);
    }   
    return outputFile;
}
