#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
	   output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/************************************************
 * CONVERT TO HEX
 * Convert the data from the memory location
 * to a hex.  This helps to see the address segments
 ***********************************************/
void toHex(char * hex, long * address)
{
   sprintf(hex, "0x%lx", *(address) );
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}



/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * address = NULL;
   char * pChar = NULL;

   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
		<< setw(15) << "address"
		<< setw(20) << "hexadecimal"
		<< setw(20) << "decimal"
		<< setw(18) << "characters"
		<< endl;
   cout << "----+"
		<< "---------------+"
		<< "-------------------+"
		<< "-------------------+"
		<< "-----------------+\n";
   char hexadecimal[20];
   long long decimal;
   string characters;
   for (long i = 35; i >= -4; i--)   // You may need to change 24 to another number
   {
	  address = &bow + i;
	  toHex(hexadecimal, address);
	  decimal = *(address);
	  characters = displayCharArray((char *)(address));
	  	  
	  cout 	<< '[' << setw(2) << i << ']'
			<< setw(15) << address
			<< setw(20) << hexadecimal
			<< setw(20) << decimal
			<< setw(20) << characters
			<< "\n";
   }

   // change text in main() to "*main**"
   pChar = (char * ) & bow;
   while (string(pChar++) != "*MAIN**");
   pChar[0] = 'm';
   pChar[1] = 'a';
   pChar[2] = 'i';
   pChar[3] = 'n';

   // change number in main() to 654321
   address = (long * ) & bow;
   while ( * address != 123456)
   {
	 address++; //count pLong
   }
   * address = 654321;

   // change pointerFunction in main() to point to pass
   address = (long * ) & bow;
   while ( * address != (long long) fail)
   {
	 address++;
   }
   * address = (long long) pass;

   // change message in main() to point to passMessage
   address = (long * ) & bow;
   while ( * address != (long long) failMessage)
   {
	 address++;
   }
   pChar = (char * ) * address;
   * address = (long long) passMessage;
   pChar = (char * ) * address;
   
}
