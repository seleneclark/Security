/****************************************************************
*	Program:
*		   W11 Lab: Password Strength
*		   David Wilson, CSE 453
*	Author:
		 Selene Clark
*	Summary:
*		Analyze the strength of a given user password.
*******************************************************************/
#include <iostream>
#include <math.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;

/************************************************************************************************************
*	ISLOWERCASE
*	Determines if lowercase letters are included in the password
***************************************************************************************************************/
bool isLowerCase(string password)
{
   for (int i = 0; i < password.length(); i++)
   {
	  if (islower(password[i]))
	  {
		 return true;
	  }
   }
   return false;
}
/************************************************************************************************************
*	ISUPPERCASE
*	Determines if uppercase letters are included in the password
***************************************************************************************************************/
bool isUpperCase(string password)
{
   for (int i = 0; i < password.length(); i++)
   {
	  if (isupper(password[i]))
	  {
		 return true;
	  }
   }
   return false;
}

/************************************************************************************************************
*	ISANUMBER
*	Determines if numbers are included in the password
***************************************************************************************************************/
bool isANumber(string password)
{
   for (int i = 0; i < password.length(); i++)
   {
	  if (isdigit(password[i]))
	  {
		 return true;
	  }
   }
   return false;
}

/************************************************************************************************************
*	ISPUNCTUATION
*	Determines if punctuation is included in the password
***************************************************************************************************************/
bool isPunctuation(string password)
{
   for (int i = 0; i < password.length(); i++)
   {
	  if (ispunct(password[i]))
	  {
		 return true;
	  }
   }
   return false;
}

/************************************************************************************************************
*	HOWCOMPLEX
*	Calculates how large the set of characters are
***************************************************************************************************************/
int1024_t numberOfCombinations(string password)
{
   int complexity = 0;
   if (isLowerCase (password)) { complexity += 26; }
   if (isUpperCase (password)) { complexity += 26; }
   if (isANumber (password)) { complexity += 10; }
   if (isPunctuation (password)) { complexity += 32; }
   
   int1024_t combinations = pow( (int1024_t) complexity, (int) password.length() );
   return combinations;
}

/************************************************************************************************************
*	NUMBEROFBITS
*	Calculates  the bit equivalence based on the number of combinations.
***************************************************************************************************************/
int numberOfBits(long double combinations)
{
   int bits = 0;
   while ( pow(2, bits) < combinations)
   {
	  bits++;
   }
   bits--;
   return bits;
}
/************************************************************************************************************
*	MAIN
*	Prompt the user for a password. Determine how many combinations of passwords
* 	exist in this set.  Determine the bit equivalence based on the number of combinations.
***************************************************************************************************************/
int main(int argc, const char * argv[])
{
   string password;
   cout << "Please enter the password: ";
   cin >> password;
   int1024_t combinations = numberOfCombinations(password);
   int bits = numberOfBits((long double) combinations);
   cout << "There are " << combinations << " combinations\n";
   cout << "That is equivalent to a key of " << bits << " bits\n";
   
	return 0;
}
