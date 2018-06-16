#include "functions.h"

/*
Version:	vbeta1.0
Autor:		Prasanth PUSHPARASAH
Function:	The main purpose of this tool is to check if given string of characters is a palindrome or not
Code Specification:
	1/ Loop will occur until user explicitly exit the program with tapping "."
	2/ During the loop 2 questions will be asked to user:
		a/ Enter string to check if this is palindrome or not
		b/ Enter expected pattern, OK or NOK
	3/ For each string of characters entered by user, check will be performed and the return in the prompt the result if the check
	4/ Used loop is "do ... while", meaning undefined iteration until user explicitly exit the program
	5/ At the end a summary of all entered words will be printed in the prompt
	6/ And finally a CSV file will be genarated with the summary
	7/ Dynamic pointers with memory allocations in the heap will be used
*/


int main(int argc, const char * argv[])
{
	// Defining buffers to get user inputs
	char bufferPalindromeValue[MAX_STR_SIZE];
	char bufferPalindromeExpectedValue[MAX_STR_SIZE];
	
	// Other necessary variables
	BOOL palindromeExpectedPatternInBool;
	BOOL isPalindrome;
	BOOL success;
	int OS_error_code = 0;

	// Defining the palindrome stack to store informations
	palindromeStack myPalindromeStack;

	// Deining dynamic pointer on this stack and allocating necessary memories in the heap
	palindromeStack* pDynPalindromeStack;
	pDynPalindromeStack = (palindromeStack*)malloc(sizeof(palindromeStack));

	// Initializing palindrome stack
	initPalindromeStack_p(&myPalindromeStack);
	initPalindromeStack_p(pDynPalindromeStack);

	// Checking if we have necessary number of arguments to execute the program 
	if (argc != 2)
	{
		fprintf(stderr, "ERROR %d: Incorrect number of arguments.\n", ERR_INCORRECT_CLI_ARGS);
		OS_error_code = -1;
	}
	else {
		//do...while loop to check undefined number of words
		do
		{
			// Asking a word to user and getting his input 
			printf("Enter your palindrome to check or enter \".\" to leave:\n");
			scanf("%s", &bufferPalindromeValue);

			// Checking if user want to exit to program
			if (strcmp(bufferPalindromeValue, ".") != 0)
			{
				// Performing palindrome check on given word
				isPalindrome = palindrome(&bufferPalindromeValue);

				// Asking expexted pattern to user and getting his input
				printf("Enter your expected pattern for your given palindrome \"%s\" (OK or NOK):\n", bufferPalindromeValue);
				scanf("%s", &bufferPalindromeExpectedValue);

				// Defining boolean values for user's given input
				if (strcmp(bufferPalindromeExpectedValue, "OK") == 0)
				{
					palindromeExpectedPatternInBool = TRUE;
				}
				else if (strcmp(bufferPalindromeExpectedValue, "NOK") == 0) {
					palindromeExpectedPatternInBool = FALSE;
				}
				else {
					if (strcmp(bufferPalindromeExpectedValue, "OK") != 0)
					{
						do {
							printf("Your pattern %s doesn't correspond to one of the expected one, please choose between (OK or NOK): ", bufferPalindromeExpectedValue);
							scanf("%s", bufferPalindromeExpectedValue);
						} while (strcmp(bufferPalindromeValue, "OK") != 0);
					}
					
					if (strcmp(bufferPalindromeExpectedValue, "NOK") != 0)
					{
						do {
							printf("Your pattern %s doesn't correspond to one of the expected one, please choose between (OK or NOK): ", bufferPalindromeExpectedValue);
							scanf("%s", bufferPalindromeExpectedValue);
						} while (strcmp(bufferPalindromeValue, "NOK") != 0);
					}
					
				}


				if (isPalindrome == TRUE)
				{
					printf("Entered word \"%s\" IS a palindrome!\n", bufferPalindromeValue);
					char palindromeResult[] = "OK";
					char* pTestpalindromeResult = &palindromeResult;
					push_palindromeValues(&myPalindromeStack, &bufferPalindromeValue, &bufferPalindromeExpectedValue, &palindromeResult, palindromeExpectedPatternInBool);
				}
				else
				{
					printf("Entered word \"%s\" IS NOT a palindrome!\n", bufferPalindromeValue);
					char palindromeResult[] = "NOK";
					char* pTestpalindromeResult = &palindromeResult;
					push_palindromeValues(&myPalindromeStack, &bufferPalindromeValue, &bufferPalindromeExpectedValue, &palindromeResult, palindromeExpectedPatternInBool);
				}


			}

		} while (strcmp(bufferPalindromeValue, ".") != 0);
	}

	/*
	Some trials to debug
	printf("Before str pop\n");
	display_palindromeStack(&myPalindromeStack);

	popPalindromeValues result = pop_palindromeValues(&myPalindromeStack);
	printf("Poping palindrome value is %s\n", result.pPalindromeValue);
	printf("Poping palindrome expected pattern is %s\n", result.pPalindromeExpectedPattern);
	printf("Poping palindrome check result is %s\n", result.pPalindromeCheckResult);

	printf("After str pop\n");
	display_palindromeStack(&myPalindromeStack);
	*/



	// Defining necessay inputs based on previous step to give them in test function
	char** pDynPalindromeValueArray;
	pDynPalindromeValueArray = (char**)malloc(sizeof(char*) * pDynPalindromeStack->stackSize);

	int myPalindromeStackSize = myPalindromeStack.stackSize;

	BOOL* pPalindromeExpectedPatternInBool = (BOOL*)malloc((sizeof(BOOL*) * myPalindromeStackSize));


	int loop;
	for (loop = 0; loop<myPalindromeStackSize; loop++)
	{
		int palindromeStrSize = strlen(myPalindromeStack.pPalindromeValue[loop]);
		pDynPalindromeValueArray[loop] = (char*)malloc((sizeof(char*) * myPalindromeStackSize + 1));
		strcpy(pDynPalindromeValueArray[loop], myPalindromeStack.pPalindromeValue[loop]);

		pPalindromeExpectedPatternInBool[loop] = myPalindromeStack.pPalindromeExpectedPatternInBool[loop];

	}

	// Displaying the whole stack
	display_palindromeStack(&myPalindromeStack);



	OS_error_code = outputTestsToCSV(palindrome, argv[1],
		pDynPalindromeValueArray, pPalindromeExpectedPatternInBool, myPalindromeStackSize);

	switch (OS_error_code)
	{
	case 0:
		printf("Done, output file in %s (may be a relative path)\n", argv[1]);
		break;

	case ERR_NOTHING_TO_TEST:
		fprintf(stderr, "ERROR %d: Nothing to test\n", ERR_NOTHING_TO_TEST);
		break;

	case ERR_FILE_PATH:
		fprintf(stderr, "ERROR %d: Bad file path: %s \n", ERR_FILE_PATH, argv[1]);
		break;
	}

	// Releasing memory 
	destroyPalindromeStack(&myPalindromeStack);
	destroyPalindromeStack(pDynPalindromeStack);
	free(pDynPalindromeStack);

	system("pause");

	return 0;

}



