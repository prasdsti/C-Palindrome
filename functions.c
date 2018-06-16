#include "functions.h"

/*
Process to initialize palindrome stack parameters
Using Pointer
*/
void initPalindromeStack_p(palindromeStack* pPalindromeStack)
{
	pPalindromeStack->stackSize = 0;
	pPalindromeStack->pPalindromeValue = NULL;
	pPalindromeStack->pPalindromeExpectedPattern = NULL;
	pPalindromeStack->pPalindromeCheckResult = NULL;
	pPalindromeStack->pPalindromeExpectedPatternInBool = NULL;
}


/*
Function to initialize palindrome stack parameters
Using struc access
*/
palindromeStack initPalindromeStack_f()
{
	palindromeStack theStack;

	theStack.stackSize = 0;
	theStack.pPalindromeValue = NULL;
	theStack.pPalindromeExpectedPattern = NULL;
	theStack.pPalindromeCheckResult = NULL;
	theStack.pPalindromeExpectedPatternInBool = NULL;

	return theStack;
}


/*
Process to release allocated memories to build the stack
*/
void destroyPalindromeStack(palindromeStack* pPalindromeStack)
{
	if (pPalindromeStack->pPalindromeValue != NULL)
	{
		free(pPalindromeStack->pPalindromeValue);
		pPalindromeStack->pPalindromeValue = NULL;
		free(pPalindromeStack->pPalindromeExpectedPattern);
		pPalindromeStack->pPalindromeExpectedPattern = NULL;
		free(pPalindromeStack->pPalindromeCheckResult);
		pPalindromeStack->pPalindromeCheckResult = NULL;
		free(pPalindromeStack->pPalindromeExpectedPatternInBool);
		pPalindromeStack->pPalindromeExpectedPatternInBool = NULL;
	}

	//an empty stack means no elements in the stack
	pPalindromeStack->stackSize = 0;

}


/*
Function to check if the stack is empty and return a boolean
*/
BOOL isPalindromeStackEmpty(palindromeStack* pPalindromeStack)
{
	BOOL result = FALSE;

	if (pPalindromeStack->stackSize == 0
		&& pPalindromeStack->pPalindromeValue == NULL
		&& pPalindromeStack->pPalindromeExpectedPattern == NULL
		&& pPalindromeStack->pPalindromeCheckResult == NULL
		&& pPalindromeStack->pPalindromeExpectedPatternInBool == NULL)
	{
		result = TRUE;
	}

	return result;
}


/*
Function to push all necessary elements in the palindrome stack 
palindromeStack* pPalindromeStack => stack to fill
char* pPalindromeValue => string pointer to check if this is a palindrome or not
char* pPalindromeExpectedPattern => string pointer on given pattern by user (OK or NOK)
char* pPalindromeCheckResult => string pointer on result of check palindrome
BOOL* pPalindromeExpectedPatternInBool => boolean pointer on result of check palindrome
*/
BOOL push_palindromeValues(palindromeStack* pPalindromeStack, char* pPalindromeValue, char* pPalindromeExpectedPattern, char* pPalindromeCheckResult, BOOL* pPalindromeExpectedPatternInBool)
{
	// Initializing succes at TRUE, will be dfined at FALSE if something going wrong
	BOOL succes = TRUE;

	// Getting string lengths for different string given as inputs
	int strLenPalindromeValue, strLenPalindromeExpectedPattern, strLenPalindromeCheckResult;
	strLenPalindromeValue = strlen(pPalindromeValue);
	strLenPalindromeExpectedPattern = strlen(pPalindromeExpectedPattern);
	strLenPalindromeCheckResult = strlen(pPalindromeCheckResult);

	// Allocating memories for all necessary dynamic pointers and copying given values in local values
	char* pLocalPalindromeValue = (char*)malloc(sizeof(char) * strLenPalindromeValue + 1);
	strcpy(pLocalPalindromeValue, pPalindromeValue);
	char* pLocalPalindromeExpectedPattern = (char*)malloc(sizeof(char) * strLenPalindromeExpectedPattern + 1);
	strcpy(pLocalPalindromeExpectedPattern, pPalindromeExpectedPattern);
	char* pLocalPalindromeCheckResult = (char*)malloc(sizeof(char) * strLenPalindromeCheckResult + 1);
	strcpy(pLocalPalindromeCheckResult, pPalindromeCheckResult);
	BOOL* pLocalPalindromeCheckResultInBool = (BOOL*)malloc(sizeof(BOOL));
	pLocalPalindromeCheckResultInBool = pPalindromeExpectedPatternInBool;

	// Checking if the stack is empty
	if (isPalindromeStackEmpty(pPalindromeStack) == TRUE)
	{
		// Allocating memories for different pointers in the stack, only element because we will process string by string
		pPalindromeStack->pPalindromeValue = (char**)malloc(sizeof(char*));
		pPalindromeStack->pPalindromeExpectedPattern = (char**)malloc(sizeof(char*));
		pPalindromeStack->pPalindromeCheckResult = (char**)malloc(sizeof(char*));
		pPalindromeStack->pPalindromeExpectedPatternInBool = (BOOL*)malloc(sizeof(BOOL));

		// Checking if memories are correctly allocated
		if ((pPalindromeStack->pPalindromeValue == NULL)
			&& (pPalindromeStack->pPalindromeExpectedPattern == NULL)
			&& (pPalindromeStack->pPalindromeCheckResult == NULL)
			&& (pPalindromeStack->pPalindromeExpectedPatternInBool == NULL))
		{
			succes = FALSE;
		}
		else
		{
			// Allocating memories for all strings with necessary number of elements, using previously calculated string lengths 
			pPalindromeStack->pPalindromeValue[pPalindromeStack->stackSize] = (char*)malloc(sizeof(char) * strLenPalindromeValue + 1);
			pPalindromeStack->pPalindromeValue[pPalindromeStack->stackSize] = pLocalPalindromeValue;
			pPalindromeStack->pPalindromeExpectedPattern[pPalindromeStack->stackSize] = (char*)malloc(sizeof(char) * strLenPalindromeExpectedPattern + 1);
			pPalindromeStack->pPalindromeExpectedPattern[pPalindromeStack->stackSize] = pLocalPalindromeExpectedPattern;
			pPalindromeStack->pPalindromeCheckResult[pPalindromeStack->stackSize] = (char*)malloc(sizeof(char) * strLenPalindromeCheckResult + 1);
			pPalindromeStack->pPalindromeCheckResult[pPalindromeStack->stackSize] = pLocalPalindromeCheckResult;
			pPalindromeStack->pPalindromeExpectedPatternInBool[pPalindromeStack->stackSize] = pLocalPalindromeCheckResultInBool;
			pPalindromeStack->stackSize = pPalindromeStack->stackSize + 1;
		}
	}
	// Case stack is not empty
	else 
	{
		// Creating new pointers pointing on current value of the stack
		char** pCurrentPalindromeValue = pPalindromeStack->pPalindromeValue;
		char** pCurrentPalindromeExpectedPattern = pPalindromeStack->pPalindromeExpectedPattern;
		char** pCurrentPalindromeCheckResult = pPalindromeStack->pPalindromeCheckResult;
		BOOL* pCurrentPalindromeCheckResultInBool = pPalindromeStack->pPalindromeExpectedPatternInBool;

		// Defining new dynamic pointers necessary to add new elements in the stack
		char** pNewPalindromeValue = NULL;
		char** pNewPalindromeExpectedPattern = NULL;
		char** pNewPalindromeCheckResult = NULL;
		BOOL* pNewPalindromeCheckResultInBool = NULL;

		// Allocating necessary memories for all previously created pointers
		pNewPalindromeValue = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize + 1));
		pNewPalindromeExpectedPattern = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize + 1));
		pNewPalindromeCheckResult = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize + 1));
		pNewPalindromeCheckResultInBool = (BOOL*)malloc(sizeof(BOOL) * (pPalindromeStack->stackSize + 1));

		// Checking if all pointers have been correctly allocated with memories
		if ((pNewPalindromeValue != NULL)
			&& (pNewPalindromeExpectedPattern != NULL)
			&& (pNewPalindromeCheckResult != NULL)
			&& (pNewPalindromeCheckResultInBool != NULL))
		{
			// Looping on existing elements
			int loop;
			for (loop = 0; loop < pPalindromeStack->stackSize; loop++)
			{
				pNewPalindromeValue[loop] = pCurrentPalindromeValue[loop];
				pNewPalindromeExpectedPattern[loop] = pCurrentPalindromeExpectedPattern[loop];
				pNewPalindromeCheckResult[loop] = pCurrentPalindromeCheckResult[loop];
				pNewPalindromeCheckResultInBool[loop] = pCurrentPalindromeCheckResultInBool[loop];
			}

			// Allocating memories for adding the new elements
			pNewPalindromeValue[loop] = (char*)malloc(sizeof(char) * strLenPalindromeValue + 1);
			pNewPalindromeValue[loop] = pLocalPalindromeValue;
			pNewPalindromeExpectedPattern[loop] = (char*)malloc(sizeof(char) * strLenPalindromeExpectedPattern + 1);
			pNewPalindromeExpectedPattern[loop] = pLocalPalindromeExpectedPattern;
			pNewPalindromeCheckResult[loop] = (char*)malloc(sizeof(char) * strLenPalindromeCheckResult + 1);
			pNewPalindromeCheckResult[loop] = pLocalPalindromeCheckResult;
			pNewPalindromeCheckResultInBool[loop] = (BOOL*)malloc(sizeof(BOOL));
			pNewPalindromeCheckResultInBool[loop] = pLocalPalindromeCheckResultInBool;

			// Affecting new elements in the stack
			pPalindromeStack->pPalindromeValue = pNewPalindromeValue;
			pPalindromeStack->pPalindromeExpectedPattern = pNewPalindromeExpectedPattern;
			pPalindromeStack->pPalindromeCheckResult = pNewPalindromeCheckResult;
			pPalindromeStack->pPalindromeExpectedPatternInBool = pNewPalindromeCheckResultInBool;
			pPalindromeStack->stackSize = pPalindromeStack->stackSize + 1;

			// Releasing temporary used pointers
			free(pCurrentPalindromeValue);
			pCurrentPalindromeValue = NULL;
			free(pCurrentPalindromeExpectedPattern);
			pCurrentPalindromeExpectedPattern = NULL;
			free(pCurrentPalindromeCheckResult);
			pCurrentPalindromeCheckResult = NULL;
			free(pCurrentPalindromeCheckResultInBool);
			pCurrentPalindromeCheckResultInBool = NULL;
		}
		else
		{
			succes = FALSE;
		}
	}

	return succes;
}


/*
Function to get last element given in the stack and removing it from the stack
*/
popPalindromeValues pop_palindromeValues(palindromeStack* pPalindromeStack)
{
	// Defining a new struc to put removing from the stack element in this struc
	popPalindromeValues result;

	// Checking if the stack is empty
	if (isPalindromeStackEmpty(pPalindromeStack) == TRUE)
	{
		result.success = FALSE;
		result.pPalindromeValue = NULL;
		result.pPalindromeExpectedPattern = NULL;
		result.pPalindromeCheckResult = NULL;
		result.pPalindromeExpectedPatternInBool = NULL;
	}
	// Stack is not empty
	else
	{
		// Getting all parameters of last element in the stack
		result.success = TRUE;
		result.pPalindromeValue = pPalindromeStack->pPalindromeValue[pPalindromeStack->stackSize - 1];
		result.pPalindromeExpectedPattern = pPalindromeStack->pPalindromeExpectedPattern[pPalindromeStack->stackSize - 1];
		result.pPalindromeCheckResult = pPalindromeStack->pPalindromeCheckResult[pPalindromeStack->stackSize - 1];
		result.pPalindromeExpectedPatternInBool = pPalindromeStack->pPalindromeExpectedPatternInBool[pPalindromeStack->stackSize - 1];

		// Creating a temporary pointers to get last element parameters
		char** pCurrentPalindromeValue = pPalindromeStack->pPalindromeValue;
		char** pCurrentPalindromeExpectedPattern = pPalindromeStack->pPalindromeExpectedPattern;
		char** pCurrentPalindromeCheckResult = pPalindromeStack->pPalindromeCheckResult;
		BOOL* pCurrentPalindromeExpectedPatternInBool = pPalindromeStack->pPalindromeExpectedPatternInBool;

		// Calulating string lengths for all parameters in last element of the stack
		int strLenPalindromeValue, strLenPalindromeExpectedPattern, strLenPalindromeCheckResult;
		strLenPalindromeValue = strlen(pCurrentPalindromeValue);
		strLenPalindromeExpectedPattern = strlen(pCurrentPalindromeExpectedPattern);
		strLenPalindromeCheckResult = strlen(pCurrentPalindromeCheckResult);

		// Creating new dynamic pointers in order to put last element parameters in them
		char** pNewPalindromeValue = NULL;
		char** pNewPalindromeExpectedPattern = NULL;
		char** pNewPalindromeCheckResult = NULL;
		BOOL* pNewPalindromeExpectedPatternInBool = NULL;

		// Allocating necessary memories for previously defined pointers
		pNewPalindromeValue = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize - 1));
		pNewPalindromeExpectedPattern = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize - 1));
		pNewPalindromeCheckResult = (char**)malloc(sizeof(char*) * (pPalindromeStack->stackSize - 1));
		pNewPalindromeExpectedPatternInBool = (BOOL*)malloc(sizeof(BOOL));

		// Checking if memory allocations have been correctly done for all previously defined pointers
		if ((pNewPalindromeValue != NULL) && (pNewPalindromeExpectedPattern != NULL) && (pNewPalindromeCheckResult != NULL) && (pNewPalindromeExpectedPatternInBool != NULL))
		{
			// Looping on existing elements
			int loop;
			for (loop = 0; loop < pPalindromeStack->stackSize - 1; loop++)
			{
				// Allocating memories for array of caracters
				pNewPalindromeValue[loop] = (char*)malloc(sizeof(char) * strLenPalindromeValue + 1);
				pNewPalindromeValue[loop] = pCurrentPalindromeValue[loop];
				pNewPalindromeExpectedPattern[loop] = (char*)malloc(sizeof(char) * strLenPalindromeExpectedPattern + 1);
				pNewPalindromeExpectedPattern[loop] = pCurrentPalindromeExpectedPattern[loop];
				pNewPalindromeCheckResult[loop] = (char*)malloc(sizeof(char) * strLenPalindromeCheckResult + 1);
				pNewPalindromeCheckResult[loop] = pCurrentPalindromeCheckResult[loop];
			}

			// Afecting new pointers to elements in stack
			pPalindromeStack->pPalindromeValue = pNewPalindromeValue;
			pPalindromeStack->pPalindromeExpectedPattern = pNewPalindromeExpectedPattern;
			pPalindromeStack->pPalindromeCheckResult = pNewPalindromeCheckResult;
			pPalindromeStack->pPalindromeExpectedPatternInBool = pNewPalindromeExpectedPatternInBool;

			pPalindromeStack->stackSize = pPalindromeStack->stackSize - 1;

			// Releasing memory 
			free(pCurrentPalindromeValue);
			pCurrentPalindromeValue = NULL;
			free(pCurrentPalindromeExpectedPattern);
			pCurrentPalindromeExpectedPattern = NULL;
			free(pCurrentPalindromeCheckResult);
			pCurrentPalindromeCheckResult = NULL;
			free(pCurrentPalindromeExpectedPatternInBool);
			pCurrentPalindromeExpectedPatternInBool = NULL;
		}
		else
		{
			result.success = FALSE;
			result.pPalindromeValue = NULL;
			result.pPalindromeExpectedPattern = NULL;
			result.pPalindromeCheckResult = NULL;
			result.pPalindromeExpectedPatternInBool = NULL;
		}


	}

	return result;
}


/*
Function to display all elements and parameters in the built stack
*/
void display_palindromeStack(const palindromeStack* pPalindromeStack)
{

	int loop;
	// Stack is empty
	if (isPalindromeStackEmpty(pPalindromeStack) == TRUE)
	{
		printf("The stack is empty\n");
	}
	// Printing all elements one by one and their parameters
	else
	{
		for (loop = pPalindromeStack->stackSize - 1; loop >= 0; loop--)
		{
			printf("------------ Index %d -----------------\n", loop);
			printf("Palindrome Value at index %d is %s\n", loop, pPalindromeStack->pPalindromeValue[loop]);
			printf("PalindromeExpectedPattern Value at index %d is %s\n", loop, pPalindromeStack->pPalindromeExpectedPattern[loop]);
			printf("PalindromeCheckResult Value at index %d is %s\n", loop, pPalindromeStack->pPalindromeCheckResult[loop]);
			printf("PalindromeCheckResult Value in boolean at index %d is %d\n", loop, pPalindromeStack->pPalindromeExpectedPatternInBool[loop]);
			printf("----------------------------------------\n\n");
		}
	}


}



/*
Funtion to check if a string of characters is palindrome and then return a BOOLEAN
I decided to not take in account the difference between string of ODD or EVEN nomber of caracters because I don't see for the moment any benefit with that
I just have some additional line of codes
I will try to understand the role of PIVOT letter later
*/
BOOL palindrome(char* pPalindromeValue)
{

	// Defining default value at FALSE, will be setted at TRUE if this is a palindrome
	BOOL isPalindrome = FALSE;

	// In case of empty string, this is considered as a palindrome
	if (strlen(pPalindromeValue) == 0)
	{
		isPalindrome = TRUE;
	}
	// In case of one element, this is also considered as a palindrome
	else if (strlen(pPalindromeValue) == 1)
	{
		isPalindrome = TRUE;
	}
	// In any other case we are going to look letter by letter, first vs last and so on ...
	else
	{
		int indexLeft, indexRight;
		indexLeft = 0; // First letter
		indexRight = strlen(pPalindromeValue) - 1; // Last letter

		// Condition to exiy while loop
		BOOL LoopStop = FALSE;
		//indexLeft must remain stricly smaller than indexRight
		while (indexLeft < indexRight && LoopStop == FALSE)
		{
			// Comparing letter vs letter
			if (pPalindromeValue[indexLeft] != pPalindromeValue[indexRight])
			{
				LoopStop = TRUE;
			}
			indexLeft++;
			indexRight--;
		}
		if (LoopStop == FALSE)
		{
			isPalindrome = TRUE;
		}
	}

	return isPalindrome;

}



/*
Sebastien's source, taken as it is, copy/paste
Test function
*/
int outputTestsToCSV(BOOL(*yourPalindromeFunction)(const char*),
	const char* strOutputDirectoryPath,
	const char** pPalindromesArray,
	const BOOL* pExpectedArray,
	int numberOfTests)
{

	int returnCode = 0;

	FILE* pResultFile;
	char strResultFilePath[MAX_FILE_PATH];


	if (pPalindromesArray != NULL && pExpectedArray != NULL)
	{
		strcpy(strResultFilePath, strOutputDirectoryPath);

		buildCleanFilePath(strResultFilePath);

		strcat(strResultFilePath, "palindromes_results.csv");
		pResultFile = fopen(strResultFilePath, "w+");


		if (pResultFile != NULL)
		{

			fprintf(pResultFile, "%s\n", "WORD,OUTCOME,EXPECTED");
			int nLoop;
			for (nLoop = 0; nLoop < numberOfTests; nLoop++)
			{
				char* strResultLine = NULL;
				int strResultLineSize;
				char strTestResultOutcome[3];
				char strTestResultExpected[3];

				strResultLineSize = strlen(pPalindromesArray[nLoop]);
				strResultLineSize += 1; // ','
				strResultLineSize += 2; // "OK" or "KO" outcome
				strResultLineSize += 1; // ','
				strResultLineSize += 2; // "OK" or "KO" expected
				strResultLineSize += 1; // '\0'

				strResultLine = (char*)malloc((sizeof(char)* strResultLineSize));


				BOOL testResultOutcome = yourPalindromeFunction(pPalindromesArray[nLoop]);

				switch (testResultOutcome)
				{
				case TRUE:
					strcpy(strTestResultOutcome, "OK");
					break;

				case FALSE:
					strcpy(strTestResultOutcome, "KO");
					break;
				}


				switch (pExpectedArray[nLoop])
				{
				case TRUE:
					strcpy(strTestResultExpected, "OK");
					break;

				case FALSE:
					strcpy(strTestResultExpected, "KO");
					break;
				}

				sprintf(strResultLine, "%s,%s,%s", pPalindromesArray[nLoop], strTestResultOutcome, strTestResultExpected);

				fprintf(pResultFile, "%s\n", strResultLine);

				free(strResultLine);
				strResultLine = NULL;

			}
			fclose(pResultFile);
		}
		else
		{
			returnCode = ERR_FILE_PATH;
		}
	}
	else
	{
		returnCode = ERR_NOTHING_TO_TEST;
	}

	return returnCode;

}


/*
Sebastien's source, taken as it is, copy/paste
*/
void buildCleanFilePath(char* aRawFilePath)
{
	char strOSPathSeparator[2];
	strOSPathSeparator[0] = PATH_SEPARATOR;
	strOSPathSeparator[1] = '\0';

	if (strlen(aRawFilePath) >= 1)
	{
		if (strlen(aRawFilePath) == 1)
		{
			if (strcmp(aRawFilePath, strOSPathSeparator) != 0)
			{
				strcat(aRawFilePath, strOSPathSeparator);
			}
		}
		else
		{
			if (aRawFilePath[strlen(aRawFilePath) - 1] != PATH_SEPARATOR)
				strcat(aRawFilePath, strOSPathSeparator);
		}
	}
}

