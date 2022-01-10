/********************************************************************
*    The Hill cipher is a polygraphic substitution cipher based on linear algebra.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H
#define MATRIXSIZE 2
#define ALPHABET_SIZE 94
#define LOWEST_CHAR_VALUE 32
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Selene Clark"; }
   virtual std::string getCipherName()  { return "Hill Cypher"; }
   virtual std::string getEncryptAuth() { return "Selene Clark"; }
   virtual std::string getDecryptAuth() { return "Selene Clark"; }
   
   
   
   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
	  std::string s;
	  s += "Hill, Lester S. “Cryptography in an Algebraic Alphabet.”\n";
	  s += "    The American Mathematical Monthly, vol. 36, no. 6,\n";
	  s += "    Mathematical Association of America, 1929, pp. 306–12,\n";
	  s += "    https://doi.org/10.2307/2298294.";
	  return std::string(s);
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
	  std::string str;
	  // The encrypt pseudocode
	  str =  "encrypt(plainText, password)\n";
	  str += "   key <- getMatrixKey(password)\n";
	  str += "   cipherText <- matrixMultiply(key, plainText)\n";
	  str += "   RETURN cipherText\n\n";

	  // The decrypt pseudocode
	  str += "decrypt(cipherText, password)\n";
	  str += "   key <- getMatrixKey(password)\n";
	  str += "   decryptKey <- getInverseMatrix(key)\n";
	  str += "   plainText  <- matrixMultiply(decryptKey, cipherText)\n";
	  str += "   RETURN plainText\n\n";

	  return str;
   }

   /**********************************************************
   * INDEX
   * gets the index for a 2D array to be used with a pointer
   **********************************************************/
   int index(int i, int j)
   {
	  return i * MATRIXSIZE + j;
   }

   void copyKey(int k[2][2])
   {
	  for (int i = 0; i < MATRIXSIZE; i++)
	  {
		 for (int j = 0; j < MATRIXSIZE; j++)
		 {
			key[i][j] = k[i][j];
		 }
	  }
   }
   
   /**********************************************************
   * GETMATRIXKEY
   * Use password to create the matrix key
   **********************************************************/
   void getMatrixKey(const std::string & password)
   {
	  int pass = 0;
	  for (int i = 0; i < password.length(); i++)
	  {
		 pass += (int)password[i];
	  }
	  pass = pass % 3;
	  int key0[2][2] = {{2,3}, {5,7}};
	  int key1[2][2] = {{4,3}, {5,4}};
	  int key2[2][2] = {{4,3}, {3,2}};
	  switch (pass)
	  {
		 case 0:
			copyKey(key0);
			break;
		 case 1:
			copyKey(key1);
			break;
		 default:
			copyKey(key2);
	  }
   }

   /**********************************************************
   * MATRIXMULTIPLY
   * Multiply the key matrix against the plainText to get the cipherMatrix
   **********************************************************/
   void matrixMultiply( const std::string & text)
   {
	  int messageVector[MATRIXSIZE];
	  for (int i = 0; i < MATRIXSIZE; i++)
	  {
		 messageVector[i] = (int)text[i] - LOWEST_CHAR_VALUE;
	  }
	  for (int i = 0; i < MATRIXSIZE; i++)
	  {
		 matrix[i] = 0;

		 for (int j = 0; j < MATRIXSIZE; j++)
		 {
			   matrix[i] += key[i][j] * messageVector[j];
		 }
		 matrix[i] = matrix[i] % ALPHABET_SIZE;
	  }
   }
   
   /**********************************************************
   * MATRIXTOSTRING
   * Convert the matrix to a string
   **********************************************************/
   string matrixToString(int matrix[])
   {
	 string text;
	 for (int i = 0; i < MATRIXSIZE; i++)
	 {
		if (matrix[i] < 0)
		{
		   matrix[i] = matrix[i] + ALPHABET_SIZE;
		}
		text += static_cast<char>(matrix[i] + LOWEST_CHAR_VALUE);

	 }
	 return text;
   }
   

   /**********************************************************
   * INVERSE
   * Get the inverse matrix
   **********************************************************/
   bool getInverse(const std::string & password)
   {
	  int pass = 0;
	  for (int i = 0; i < password.length(); i++)
	  {
		 pass += (int)password[i];
	  }
	  pass = pass % 3;
	  int key0[2][2] = {{-7,3}, {5,-2}};
	  int key1[2][2] = {{4,-3}, {-5,4}};
	  int key2[2][2] = {{-2,3}, {3,-4}};
	  switch (pass)
	  {
		 case 0:
			copyKey(key0);
			break;
		 case 1:
			copyKey(key1);
			break;
		 default:
			copyKey(key2);
	  }
	  return true;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual string encrypt(const std::string & plainText,
                               const std::string & password)
   {
	  getMatrixKey(password);
	  string cipherText = "";
	  char messageLength[5];
	  sprintf(messageLength, "%04ld", (long)plainText.length());
	  string plainTextAndLength = string(messageLength);
	  plainTextAndLength += plainText;
	  for (long i = 0; i < plainTextAndLength.length(); i = i + 2)
	  {
		 matrixMultiply(plainTextAndLength.substr(i, 2));
		 cipherText += matrixToString(matrix);
	  }
	  return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText, 
                               const std::string & password)
   {
	  string plainTextAndLength= "";
	  getInverse(password);
	  for (int i = 0; i < cipherText.length(); i = i + 2)
	  {
		 matrixMultiply(cipherText.substr(i, 2));
		 plainTextAndLength += matrixToString(matrix);
	  }
	  int plainTextLength = atoi(plainTextAndLength.substr(0,4).c_str());
	  string plainText = plainTextAndLength.substr(4,plainTextLength);
      return plainText;
   }
   
   
private:
   int key[2][2];
   int matrix[];
};

#endif // CIPHER01_H
