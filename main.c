#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include "DynamicStack.h"
#define SIZE 1024


int main(int argc, const char *argv[])
{
    char inputData[SIZE] = "stdin";      // store the -i "name" in this array
    char outputData[SIZE] = "stdout";    // store the -o "name" in this array
    int bValue = 10;                    // default -b value

    int fd;     // file descriptor for input file
    int fd2;    // file descriptor for output file

    /* if there is more than 1 argument */
    if (argc > 1)
    {
        for (int i=1; i<(argc-1); i++)
        {
            if (!(strcmp("-i", argv[i])))
            {
                strcpy(inputData, argv[i+1]);
                fd = open(argv[i+1], O_RDONLY, 0644);               // open input file

                /* if could not open input file */
                if (fd<1)
                {
                    printf("ERROR: Could not open input file!\n");
                    exit(0);
                }

                /* else if opened input file successfully */
                else
                {
                    printf("Opened Input File Successfully!\n");
                    i++;
                }
            }
            else if (!(strcmp("-o", argv[i])))
            {
                strcpy(outputData, argv[i+1]);
                fd2 = open(argv[i+1], O_RDWR | O_CREAT | O_TRUNC, 0644);      // open output file

                /* if could not open output file */
                if (fd2<1)
                {
                    printf("ERROR: Could not open output file!\n");

                    //exit(0);
                }

                /* else if opened output file successfully */
                else
                {
                    printf("Opened Output File Successfully!\n");
                    i++;
                }
            }
            else if (!(strcmp("-b", argv[i])))
            {
                bValue = atoi(argv[i+1]);
                i++;
            }
        } // for loop
    } // argc>1

    /* else if only one argument entered, then use default setups */
    else if (argc == 1)
    {
        printf("\nInvalid input data -> Using default data! \n\n");
        strcpy(inputData, "stdin");
        strcpy(outputData, "stdout");
        bValue = 10;
    }

/********************************************************************************************************************************/

    char inputStr[SIZE];    // if using "stdin"
    int length;             // length of the input string
    int xTime;              // the number of blocks in the string need to be reversed
    int remainder;          // the number of characters in the last block
    int index;

    index = bValue;         // the max index in the current block


    /* if using stdin */
    if (!(strcmp(inputData, "stdin")))
    {
        printf("Enter a desired string: ");
        scanf("%s", inputStr);

        length = strlen(inputStr);          // determine the length of the input string
        xTime = length / bValue;            // calculate the number of blocks in size bValue
        remainder = length % bValue;        // if the last block's number of character is less than bValue

        /* if using stdout */
        if (!(strcmp(outputData, "stdout")))
        {
            /* if the length of input string is greater than or equal to bValue */
            if (length >= bValue)
            {
                for (int i=0; i<xTime; i++)
                {
                    for (int j=0; j<bValue; j++)
                    {
                        printf("%c", inputStr[index-1-j]);      // print character to the screen
                    }
                    /* if this is last b-sized block, then apply remainder */
                    if ((i+1) == xTime)
                    { index = index + remainder; }
                    /*else, continue using bValue */
                    else
                    { index = index + bValue; }
                } // for loop

                if (remainder > 0)
                {
                    for (int j=0; j<remainder; j++)
                    {
                    printf("%c",inputStr[index-1-j]);       // print character to the screen
                    }
                }
            } // if (length >= bValue)

            /* else if the length of input string is less than bValue */
            else if (length < bValue)
            {
                for (int j=0; j<length; j++)
                {
                    printf("%c",inputStr[length-1-j]);      // print character to the screen
                }
            }
        } //if (!(strcmp(outputData, "stdout")))


        /* else, using output file */
        else
        {
            /* if the length of input string is greater than or equal to bValue */
            if (length >= bValue)
            {
                for (int i=0; i<xTime; i++)
                {
                    for (int j=0; j<bValue; j++)
                    {
                        write(fd2, &inputStr[index-1-j],1); // write a character to output file
                    }
                    /* if this is last b-sized block, then apply remainder */
                    if ((i+1) == xTime)
                    { index = index + remainder; }
                    /*else, continue using bValue */
                    else
                    { index = index + bValue; }
                } // for loop

                if (remainder > 0)
                {
                    for (int j=0; j<remainder; j++)
                    {
                        write(fd2, &inputStr[index-1-j],1); // write a character to output file
                    }
                }
            } //if (length >= bValue)

            /* else if the length of input string is less than bValue */
            else if (length < bValue)
            {
                for (int j=0; j<length; j++)
                {
                    write(fd2, &inputStr[length-1-j],1);    // write a character to output file
                }
            }

            if (strcmp(outputData, "stdout") != 0)
            {
                printf("\nWrote to Output File Successfully!\n");
            }

        }

    } // if (!(strcmp(inputData, "stdin")))

/********************************************************************************************************************************/

    /* else, using input file */
    else
    {
        char tempChar;              // temporary variable for a character
        struct Stack *S;            // creating a stack S
        S = createStack(bValue);
        int valid;                  // 1 = valid, else not valid

        /* reading a byte from input file and store in tempChar, making sure this character is not the end of the file */
        while((read(fd, &tempChar, 1)) > 0)
        {
            int num = 0;            //keep track of the number of characters being read
            do{
                num++;              // increment num every time it performs a read operation
                push(S, tempChar);  // push character to the stack
                /* num less than bValue, continue reading a byte */
                if (num < bValue)
                {
                    valid = read(fd, &tempChar, 1);
                }
            }while (valid>0 && num<bValue); // while num still less than bValue and not at the end of the file yet

            /* either print or write a character according to the value of num */
            for (int a=0; a<num; a++)
            {
                tempChar = pop(S);                      // pop the stack
                /* if using stdout */
                if (!(strcmp(outputData, "stdout")))
                {
                    printf("%c", tempChar);             // print the character to the screen
                }
                /* else, using an output file */
                else
                {
                    write(fd2, &tempChar,1);            // write the character to output file
                }
            } // for loop
        }
        if (strcmp(outputData, "stdout") != 0)
        {
            printf("\nWrote to Output File Successfully!\n");
        }
    }

    return 0;
}
