#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Opens and stores text file
FILE* openInputFile(char* n);

//Opens file for us to write to
FILE* openOutputFile(char* n);

//Converts char characters from hex values into integers
//Does not convert integer values from hex values
int hexStringToInt(char c);

//Converts hex to ASCII values
int hexStringToDecimal(char c1, char c2);

//Encrypts and decrypts files
FILE* encryptFile(FILE* inputFile, FILE* outputFile);
FILE* decryptFile(FILE* inputFile, FILE* outputFile);

//Gets base file name and returns index to append file extension at
//Appends file type extension
//Mode: 1 = Encrypt, 2 = Decrypt
void createOutputFileName(char* fullFileName, char* emptyArray, int mode);

int main(void) 
{   
    //Explains how to use program
    printf("Please enter your choice for either encrypt or decrypt as well as the filename of your choosing\n");
    printf("Encrypt Example format: -E sampleFileName.txt\n");
    printf("Decrypt Example format: -D sampleFileName.crp\n");
    printf("If no mode is chosen, encryption is assumed\n\n");

    //Gets user input and stores as an array of strings
    //Similar to argc and argv
    char input[1024];
    char *inputStrings[256];            
                                
    char delimit[]=" \t\r\n\v\f"; 
    int argumentCounter = 0;

    if(fgets(input, sizeof input, stdin))                             
        {                                        
            inputStrings[argumentCounter] = strtok(input, delimit);    
            while(inputStrings[argumentCounter] != NULL)                    
            {
                argumentCounter++;
                inputStrings[argumentCounter]=strtok(NULL,delimit);
            }
        }


    //Only initialize these values if we have an argument from main function
    //Stops segmentation faults 
    if (argumentCounter > 0 && argumentCounter < 3)
    {
        //Initialize both files first
        FILE* inputFile;
        FILE* outputFile;

        char* inputFileName;
        char outputFileName[30];
        int extensionMode;


        //User only inputs a file name, encryption is assumed
        if (argumentCounter == 1)
        {
            //Get input file name
            inputFileName = inputStrings[0];

            //Get extension type for output file
            extensionMode = 1;
        }
      
        //User inputs mode and filename
        else if (argumentCounter == 2)
        {
            //Get input file name
            inputFileName = inputStrings[1];
            char* mode = inputStrings[0];
      
            //Get extension type for output file
            if (mode[1] == 'E' || mode[1] == 'e')
            {
                extensionMode = 1;
            }
         
            else if (mode[1] == 'D' || mode[1] == 'd')
            {
                extensionMode = 2;
            }
        }

      
        //Get the base file name to name our output file
        //Appends file type extension
        //Mode: 1 = Encrypt, 2 = Decrypt
        createOutputFileName(inputFileName, outputFileName, extensionMode);
      
        //Open the input file
        //Open output file with proper name and extension
        inputFile = openInputFile(inputFileName);
        outputFile = openOutputFile(outputFileName);
      
        if (extensionMode == 1)
        {
            encryptFile(inputFile, outputFile);
            printf("Encrypted %s, resulting in %s\n", inputFileName, outputFileName);
        }
      
        else if (extensionMode == 2)
        {
            decryptFile(inputFile, outputFile);
            printf("Decrypted %s, resulting in %s\n", inputFileName, outputFileName);
        }


        fclose(inputFile);
        fclose(outputFile);
    }  

   

   return 0;
 

}


void createOutputFileName(char fullFileName[], char emptyArray[30], int mode)
{

   int appendHere;
   int length = strlen(fullFileName);
   for (int i = 0; i < length; i++)
   {  
        //If we run into a period or inputStrings terminator we stop
        //we now can append the file extension to the basefilename
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
    

   //Appends proper file extenstion
   if (mode == 1)
   {
      strcat(emptyArray, ".crp");
   }

   else if (mode == 2)
   {
      strcat(emptyArray, ".txt");
   }
}


//Opens file for us to write to
FILE* openOutputFile(char* n)
{       
    FILE * writingFile = fopen(n, "w");
    if (writingFile == NULL) 
    {
        printf("Output file couldn't be opened\n");
        exit(1);
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
        exit(1);
    }

    return readingFile;
    
}   

//Converts char characters from hex values into integers
//Does not convert integer values from hex values
int hexStringToInt(char c)
    {
    if (c >= 97) c -= 32;

    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
    
    }

//Uses hexStringToInt to convert hex values to decimal format
int hexStringToDecimal(char c1, char c2)
{
    int newc1 = hexStringToInt(c1);
    newc1 *= 16;
    int newc2 = hexStringToInt(c2);
    int result = newc1 + newc2;
    return result;
}

//Encrypts text files
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

//Decrypts crp files
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

            else if (lineContents[i] == 6 || lineContents[i] == 10 || lineContents[i] == 13 || lineContents[i] > 127 || lineContents[i] < 10)
            {
                continue;
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