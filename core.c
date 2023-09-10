/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Christine Ang
Student ID#: 121559223
Email      : cang4@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

#include "clinic.h"

#include <string.h>

#include <ctype.h>

#define CHAR_SIZE 1000


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//Display an array of 10-character digits as a formatted phone number 
void displayFormattedPhone(const char phoneNum[])
{

    int i, numCount;

    numCount = 0;

    if (phoneNum != NULL)
    {
        for (i = 0; phoneNum[i] != '\0'; i++)
        {
            if (isdigit(phoneNum[i]))
            {
                numCount++;
            }
        }

    }

    if (numCount != PHONE_LEN || phoneNum == NULL)
    {
        printf("(___)___-____");
    }

    else
    {
        printf("(");
        printf("%3.3s", phoneNum);
        printf(")");
        printf("%.3s", &phoneNum[3]);
        printf("-");
        printf("%s", &phoneNum[6]);
    }

}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Get user input for a valid integer
int inputInt(void)
{
    int intResult;
    char newLine;

    intResult = 0;
    newLine = '\0';

    do {

        scanf("%d%c", &intResult, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();

            printf("Error! Input a whole number: ");

        }

    } while (newLine != '\n');

    return intResult;

}


//Get user input for an integer > 0
int inputIntPositive(void)
{
    int intPos;

    intPos = 0;

    do
    {
        intPos = inputInt();

        if (intPos < 0)
        {
            printf("ERROR! Value must be > 0: ");
        }

    } while (intPos < 0);

    return intPos;
}

//Get user input for an integer between the permitted range specified by the 1st and 2nd argument
int inputIntRange(int min, int max)
{
    int intResult;

    intResult = 0;

    do
    {
        intResult = inputInt();

        if (intResult < min || intResult > max)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }

    } while (intResult < min || intResult > max);

    return intResult;
}

/*Get user input for a char and validate if it matches any of the characters in
the received argument, return matching char */
char inputCharOption(const char validCharArr[])
{

    int validChar;
    char newLine, charResult;

    char* match = NULL;

    newLine = '\0';
    charResult = '\0';
    validChar = 0;

    do {

        do {

            scanf("%c%c", &charResult, &newLine);

            if (newLine != '\n')
            {
                clearInputBuffer();

                printf("ERROR: Character must be one of [%s]: ", validCharArr);

            }

        } while (newLine != '\n');

        match = strchr(validCharArr, charResult);

        if (match != NULL)
        {
            validChar = 1;
        }

        else
        {
            printf("ERROR: Character must be one of [%s", validCharArr);
            printf("]: ");
            validChar = 0;
        }

    } while (!validChar);

    return charResult;

}

/*Get user input for a C string value with a length within the range specified by the
2nd and 3rd argument */
void inputCString(char validString[], int min, int max)
{

    int charCount, validValue;
    charCount = 0;
    validValue = 0;

    char tmpCharArr[CHAR_SIZE + 1] = { '\0' };

    do {

        scanf("%1000[^\n]", tmpCharArr);

        clearInputBuffer();

        charCount = strlen(tmpCharArr);

        if (min == max && charCount != max)
        {
            printf("Invalid %d-digit number! Number: ", max);
            validValue = 0;
        }

        else if (charCount > max)
        {
            printf("ERROR: String length must be no more than %d chars: ", max);
            validValue = 0;
        }

        else if (charCount < min)
        {
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
            validValue = 0;
        }

        else
        {
            strcpy(validString, tmpCharArr);
            validValue = 1;
        }

    } while (!validValue);



}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

/*Get user input for an integer representing 'day', validates whether that day exists within the
 calendar year. Returns an int value after validation */
int validateDay(int year, int month)
{

    int validDay;

    if (month == 2)
    {
        if (year % 4)
        {
            printf("Day (%d-%d)  : ", 1, DAY_MAX - 3);
            validDay = inputIntRange(1, DAY_MAX - 3);
        }

        else
        {
            printf("Day (%d-%d)  : ", 1, DAY_MAX - 2);
            validDay = inputIntRange(1, DAY_MAX - 2);
        }
    }

    else if (!(month % 4))
    {
        printf("Day(%d-%d)  : ", 1, DAY_MAX - 1);
        validDay = inputIntRange(1, DAY_MAX - 1);
    }

    else
    {
        printf("Day (%d-%d)  : ", 1, DAY_MAX);
        validDay = inputIntRange(1, DAY_MAX);
    }

    return validDay;
}