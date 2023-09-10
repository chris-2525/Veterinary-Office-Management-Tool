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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//Display an array of 10-character digits as a formatted phone number 
void displayFormattedPhone(const char phoneNum[]);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Get user input for a valid integer
int inputInt(void);

//Get user input for an integer > 0
int inputIntPositive(void);

//Get user input for an integer between the permitted range specified by the 1st and 2nd argument
int inputIntRange(int min, int max);

/*Get user input for a char and validate if it matches any of the characters in
the received argument, return matching char */
char inputCharOption(const char validCharArr[]);

/*Get user input for a C string value with a length within the range specified by the
2nd and 3rd argument */
void inputCString(char validString[], int min, int max);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

/*Get user input for an integer representing 'day', validates whether that day exists within the
 calendar year. Returns an int value after validation */
int validateDay(int year, int month);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
