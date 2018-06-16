#pragma once
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Taken from Sebastien's source
#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#ifdef _WIN64
#define PATH_SEPARATOR '\\'
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define PATH_SEPARATOR '/'
#elif TARGET_OS_IPHONE
#define PATH_SEPARATOR '/'
#elif TARGET_OS_MAC
#define PATH_SEPARATOR '/'
#else
#define PATH_SEPARATOR '/'
#endif
#elif __linux__
#define PATH_SEPARATOR '/'
#elif __unix__ // all unices not caught above
#define PATH_SEPARATOR '/'
#elif defined(_POSIX_VERSION)
#define PATH_SEPARATOR '/'
#endif


// Defining boolean TRUE
#ifndef TRUE
#define TRUE 0
#endif


// Defining boolean FALSE
#ifndef FALSE
#define FALSE 1
#endif

// Defining new type boolean
typedef int BOOL;

// Max file path, restricted by windows
#ifndef MAX_FILE_PATH
#define MAX_FILE_PATH 256
#endif

// Error codes
#ifndef ERR_NOTHING_TO_TEST
#define ERR_NOTHING_TO_TEST -1
#endif

#ifndef ERR_FILE_PATH
#define ERR_FILE_PATH -2
#endif

#ifndef ERR_INCORRECT_CLI_ARGS
#define ERR_INCORRECT_CLI_ARGS -3
#endif


// Defining max string 
#define MAX_STR_SIZE 256



/*
Palindrome stack structure definition
I decied to build a complex struct for palindrome in order to put all necessary informations
*/
typedef struct
{
	char** pPalindromeValue; // pointer on array of characters
	char** pPalindromeExpectedPattern;  // pointer on array of characters
	char** pPalindromeCheckResult;  // pointer on array of characters
	BOOL* pPalindromeExpectedPatternInBool; // pointer on boolean value of result check palindrome
	int stackSize; // interger value
} palindromeStack;



// Palindrome pop values structure definition
typedef struct {
	char** pPalindromeValue; // pointer on array of characters
	char** pPalindromeExpectedPattern; // pointer on array of characters
	char** pPalindromeCheckResult; // pointer on array of characters
	BOOL* pPalindromeExpectedPatternInBool; // pointer on boolean value of result check palindrome
	BOOL success; // boolean value
} popPalindromeValues;



//Functions and processes signatures
void initPalindromeStack_p(palindromeStack* pPalindromeStack);
void destroyPalindromeStack(palindromeStack* pPalindromeStack);
BOOL isPalindromeStackEmpty(palindromeStack* pPalindromeStack);
BOOL push_palindromeValues(palindromeStack* pPalindromeStack, char* pPalindromeValue, char* pPalindromeExpectedPattern, char* pPalindromeCheckResult, BOOL* pPalindromeExpectedPatternInBool);
popPalindromeValues pop_palindromeValues(palindromeStack* pPalindromeStack);
void display_palindromeStack(const palindromeStack* pPalindromeStack);
BOOL palindrome(char* pPalindromeValue);



// From Sebastien's source, copy/paste as it is
// Function to generate CSV file with test results
int outputTestsToCSV(BOOL(*yourPalindromeFunction)(const char*),
	const char* strOutputDirectoryPath,
	const char** pPalindromesArray,
	const BOOL* pExpectedArray,
	int numberOfTests);

// From Sebastien's source, copy/paste as it is
// Function to build clean path from the one given by user
void buildCleanFilePath(char* aRawFilePath);