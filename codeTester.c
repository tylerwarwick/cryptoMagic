#include <stdio.h>
#include <string.h>

//WORKS
FILE* openInputFile(char* n)
{       
    FILE * readingFile = fopen(n, "r");
    if (readingFile == NULL) 
    {
        printf("Input file couldn't be opened\n");
    }

    return readingFile;
    
}   

//WORKS
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
//WORKS
void getBaseFileName(char fullFileName[], char emptyArray[30], int mode)
{
   int appendHere;
   int length = strlen(fullFileName);
   for (int i = 0; i < length; i++)
   {
        char currentChar = fullFileName[i];
        if (currentChar == 46 || currentChar == '\0')
        {   
            appendHere = i;
            i = length;
        }

        else
        {
            emptyArray[i] = fullFileName[i];
        }
   }

   if (mode == 1)
   {
      strcat(emptyArray, ".txt");
   }

   else if (mode == 2)
   {
      strcat(emptyArray, ".crp");
   }
}

//Converts char characters from hex values into integers
//Does not convert integer values from hex values
int hexStringToInt(char c)
    {
    if (c >= 97) c = c - 32;

    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
    
    }

//Uses hexStringToInt to convert hex values to decimal format
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



int main(int argc, char *argv[]) 
{
    //Initialize both files first
    FILE* inputFile;
    FILE* outputFile;

    char* inputFileName;
    char outputFileName[30];
    int extensionMode = 2;

    if (argc == 2)
   {
      //Get input file name
      inputFileName = argv[1];
   }
   
   //User inputs mode and filename
   else if (argc == 3)
   {
      //Get input file name
      inputFileName = argv[2];
      char* mode = argv[1];
   }

    getBaseFileName(inputFileName, outputFileName, extensionMode);
    printf("%s\n", outputFileName);


    FILE* k = openInputFile(inputFileName);
    FILE* p = openNewFile(outputFileName);

    encryptFile(k, p);

    return 0;
    
}
