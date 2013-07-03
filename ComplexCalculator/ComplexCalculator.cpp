/*********************************************************************************
*						---ComplexCalculator---									 *
*	A program to add, subtract, multiply and divide two complex numbers			 *
*																				 *
*	@Version 1.1B																 *
*	@Author N.Ballmann, M.Blunck, D.Burken, A.Hützen							 *
**********************************************************************************/

// header
#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <Windows.h>

//Preprocessor:
#define AE (unsigned char)142 
#define ae (unsigned char)132 
#define OE (unsigned char)153 
#define oe (unsigned char)148 
#define UE (unsigned char)154 
#define ue (unsigned char)129 
#define ss (unsigned char)225 

#define ADDITION 1
#define SUBTRACTION 2
#define MULTIPLICATION 3
#define DIVISION 4

#define MAXFLOATINGPOINT 3

/**
* Definition of a complex number
* with a real and an imaginary part
* defined as two doubles
*/
typedef struct
{
	double real, imag;
} complexNumber;


/**
*				---complexAdd---
*
* Addition of two complex numebrs
* 
* @param a, b	complex numbers for mathematical operation
*
*/
inline complexNumber complexAdd(complexNumber a, complexNumber b)
{
	complexNumber result;
	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return result;
}

/**
*				---complexSub---
*
* Subtraction of two complex numbers
* 
* @param a, b	complex numbers for mathematical operation	
*
*/
inline complexNumber complexSub(complexNumber a, complexNumber b)
{
	complexNumber result;
	result.real = a.real - b.real;
	result.imag = a.imag - b.imag;
	return result;
}

/**
*				---complexMul---
*
* Multiplication of two complex numbers
* 
* @param a, b	complex numbers for mathematical operation
*
*/
inline complexNumber complexMul(complexNumber a, complexNumber b)
{
	complexNumber result;
	result.real = a.real * b.real - a.imag * b.imag;
	result.imag = a.real * b.imag + a.imag * b.real;
	return result;
}

/**
*				---complexDiv---
*
* Division of two complex Numbers
* 
* @param a, b	complex numbers for mathematical operation
*
* b.real and b.imag can not be zero 
* -> division through zero exception
*/
inline complexNumber complexDiv(complexNumber a, complexNumber b)
{
	complexNumber result = { -1,-1 };

	if(b.real != 0 && b.imag != 0)
	{
		
		result.real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
		result.imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);	
	}
	else
	{
		printf_s("\nReal- und Imagin%crteil der zweiten komplexen Zahl ist 0! Division durch 0 nicht erlaubt!", ae);
		Sleep(2000);
	}
	
	//assert(result.imag != NULL);

	//printf_s("%lf / %lf", result.real, result.imag);
	//Sleep(3500);
	return result;
}

// globals
complexNumber cnum1;
complexNumber cnum2;

/*
*			---truncateString---
*
* truncates the given parameter *str(char[]) 
* by n digits(tz) on the rhs of the floating
* point separator '.' and gets rid of the 
* trailing zeroes, if any.
*
* @param *str	char[] to truncate
* @param tz		maximum length of trailing 
*				floating point numbers
*/
void truncateString(char *str, int n)
{
	int count;
	char *p;
	
	p = strchr(str, '.');	// searches the given char[] for first
							// occurence of '.'

	if(p != NULL) // if a '.' was found
	{
		count = n;	// count of maximum rhs digits

		while(n >= 0)
		{
			count--;
			if(*p == '\0') // if eos is reached before count = 0 set p to eos
				break;
			p++; // position of pointer +1 to rhs
		}

		*p-- = '\0'; // pointer position = eos & p position 1 digit to the left

		while(*p == '0') // while *p equals 0
			*p-- = '\0'; // set *p to eos and decrement position

		if(*p == '.') // if '.' is reached (every floating point digit was 0)
			*p = '\0'; // delete '.' (eos)
	}
}

/*
*				---showResult---
*
* prints the complex number result in the form: 
*			result.real + result.imag(*)i 
* to the command line
* results are truncated to a maximum of 3 rhs
* digits
*
* @param result	the result of a mathematical operation
*/
void showResult(complexNumber result)
{
	char r_str[30];
	char i_str[30];
	
	_snprintf_s(r_str, 30, "%lf", result.real);
	_snprintf_s(i_str, 30, "%lf", result.imag);

	truncateString(r_str, MAXFLOATINGPOINT);
	truncateString(i_str, MAXFLOATINGPOINT);

	printf_s("%s + %si", r_str, i_str);
	//printf_s("\n\n%.4g + %.4gi", result.real, result.imag);
}

/**
*					---showMenu---
*
* Gives the user the choice of the mathematical operation 
* to be executed
*
* 1: ADDITION | 2: SUBTRACTION | 3: MULTIPLICATION | 4: DIVISION
*
* recursive exception-handling for wrong user input
*/
void showMenu()
{
	system("CLS");
	printf_s("Welche Rechnenoperation m%cchten Sie durchf%chren?", oe, ue); 
	printf_s("\n1: Addition\n2: Subtraktion\n3: Multiplikation\n4: Division\n");

	int userInput;
	complexNumber divResult;

	fflush(stdin);
	scanf_s("%d", &userInput); fflush(stdin);

	switch (userInput)
	{
	case ADDITION:
		printf_s("\nDas Ergebnis der Operation Zahl1 + Zahl2 lautet: ");
		showResult(complexAdd(cnum1, cnum2));
		break;

	case SUBTRACTION:
		printf_s("\nDas Ergebnis der Operation Zahl1 - Zahl2 lautet: ");	
		showResult(complexSub(cnum1, cnum2));
		break;

	case MULTIPLICATION:
		printf_s("\nDas Ergebnis der Operation Zahl1 * Zahl2 lautet: ");
		showResult(complexMul(cnum1, cnum2));
		break;

	case DIVISION:
		divResult = complexDiv(cnum1, cnum2);
		if(divResult.real != -1 && divResult.imag != -1)
		{
			printf_s("\nDas Ergebnis der Operation Zahl1 / Zahl2 lautet: ");
			showResult(divResult);
			break;
		} else 
			break;

	default: 
		printf_s("\n%d, ist keine g%cltige Eingabe...\nBitte wiederholen:\n", userInput, ue);
		Sleep(2000);
		showMenu();
	}
}

/*
*				---nextStep()---
*
* asks the user for the next step to be taken
*
* 1: another operation on the existing complex numbers
* 2: get two new complex numbers
* any other char: exit the program
*/
char nextStep()
{
	printf_s("\n\nWas m%cchten Sie als n%cchstes tun?", oe, ae);
	printf_s("\n1: Eine weitere Rechenoperation durchf%chren", ue);
	printf_s("\n2: Zwei neue komplexe Zahlen eingeben\n");
	printf_s("\nBeliebige Taste: Das Programm beenden\n");
	
	char c = fgetc(stdin); fflush(stdin);
	return c;
	//return fgetc(stdin); NOT POSSIBLE! CANT FFLUSH AFTER RETURN STATEMENT!
}

/**
*	  ---getInputAsDouble()---
*
* Validates user input and converts
* the given char array to double
*/
double getInputAsDouble()
{
	char input[30];
	double number;
	

	if(fgets(input, sizeof input, stdin))
	{
		assert((sizeof input) <= 30);
		//assert(input != NULL);
		//printf_s("%s", input);
		//truncateString(input, MAXFLOATINGPOINT);

		if(sscanf_s(input, "%lf", &number) != 1)
		{
			printf_s("Keine g%cltige Eingabe, bitte wiederholen!\n", ue);
			fflush(stdin);
			number = getInputAsDouble();
		}	
	}
	//printf_s("%.4g", number);
	//assert(number != NULL);

	return number;
}

/*
*			---getComplexNumbers---
*
* Getter for two complex numbers
*
* typesafe char[] to double conversion
* through implementation of the local
* function getInputAsDouble()
*/
void getComplexNumbers()
{
	printf_s("\nBitte zwei Komplexe Zahlen eingeben.\nRealteil Zahl 1: ");
	cnum1.real = getInputAsDouble(); fflush(stdin);
	printf_s("\nImagin%crteil Zahl 1: ", ae);
	cnum1.imag = getInputAsDouble(); fflush(stdin);
	printf_s("\nRealteil Zahl 2: ");
	cnum2.real = getInputAsDouble(); fflush(stdin);
	printf_s("\nImagin%crteil Zahl 2: ", ae);
	cnum2.imag = getInputAsDouble(); fflush(stdin);
}


void TestMathematicalOperationsOfTwoComplexNumbers();
void TestTruncationOfComplexResultString();
void TestCBuildInTruncation();

/*
*				---Main---
*
* using goto statements for fun and profit
*/
int main(void)
{
	// Start TestCode execution
	TestMathematicalOperationsOfTwoComplexNumbers();
	TestTruncationOfComplexResultString();
	TestCBuildInTruncation();
	// End TestCode execution

	printf_s("Willkommen zum lustigen rechnen mit komplexen Zahlen!\n");  // start of the calculator -> welcome the user

	NewComplex:				// goto case 2
	getComplexNumbers();	// ask for user input of two complex numbers

	NextOperation:			// goto case 1
	showMenu();				// ask the user for the mathematical operation to be used on the complex numbers
				
	switch(nextStep())		// ask the user what has to be done afterwards
	{
	case '1':
		goto NextOperation;
	case '2':
		goto NewComplex;
	default: 
		goto Exit;
	}

	Exit:					// goto case 3
	printf_s("\n\nAuf Wiedersehen!");
	Sleep(2500);
	system(EXIT_SUCCESS);	// close the console
	return 0;				// exit the program
}


/*******************************************************************
*						---Testcases---							   *
*******************************************************************/

void TestMathematicalOperationsOfTwoComplexNumbers()
{
	cnum1.real = 1;
	cnum1.imag = 2;
	cnum2.real = 3;
	cnum2.imag = 4;

	complexNumber result;

	result = complexAdd(cnum1, cnum2);
	assert(result.real == 4);
	assert(result.imag == 6);

	result = complexSub(cnum1, cnum2);
	assert(result.real = -2);
	assert(result.imag = -2);

	result = complexMul(cnum1, cnum2);
	assert(result.real = -5);
	assert(result.imag = 10);

	result = complexDiv(cnum1, cnum2);
	assert(result.real = .44);
	assert(result.imag = .08);
}

void TestTruncationOfComplexResultString()
{
	double testTruncate = 6.4502000;
	char str[15];

	sprintf(str, "%lf", testTruncate);
	assert(str[4] = '0');
	truncateString(str, 3);
	//printf_s("%s\n", str);
	
	/*for(int i = 0; i < 15; i++)
		printf_s("%c", str[i]);*/

	//printf_s("%d", str[4]);
	assert(str[5] = '0');
}

/*
* Conclusion: Build-In capabilities aren't
* sufficient for truncation to 3 rhs-digits
* AND eliminating trailing zeroes!
*/
void TestCBuildInTruncation()
{
	printf_s("%.4g\n", 4.0308);
	printf_s("%.4g\n", 0.9308);
	printf_s("%.4g\n", 4.9);
	printf_s("%.4g\n", 7814.555555);
	printf_s("%.4g\n", 4.0);
	printf_s("%.4g\n", 14.0001);
	Sleep(2500);
	system("CLS");
}

