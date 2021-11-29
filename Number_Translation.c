/*
CS354 - Project 1
Keith Lienert
klienert@wisc.edu

*added the <string.h> header
Websites that I used to help with this assignment:

https://www.rapidtables.com/convert/number/decimal-to-binary.html
https://www.geeksforgeeks.org/program-binary-decimal-conversion/
https://www.sanfoundry.com/c-program-convert-decimal-hex/
*/                   


#include <stdio.h>
#include <string.h>

#define BINARY_STRING_LENGTH 33
#define HEX_STRING_LENGTH 11

void GetBinaryFromUser(char *binary);
void GetHexFromUser(char *hex);
void GetDecimalFromUser(unsigned int *x);

void ConvertBinaryToDecimal(const char *binary, unsigned int *decimal);
void ConvertHexToDecimal(const char *hex, unsigned int *decimal);
void ConvertDecimalToBinary(const unsigned int decimal, char *binary);
void ConvertDecimalToHex(const unsigned int decimal, char *hex);

int main(){
    char binary[BINARY_STRING_LENGTH] = "11011";
    char hex[HEX_STRING_LENGTH] = "0x3F";
        unsigned int decimal = 31;

        enum MENU {binary_to_decimal=1, hex_to_decimal, decimal_to_binary, decimal_to_hex};
        while (1) {
                printf("Which conversion would you like to do?\n");
                printf("  %d. Binary to Decimal\n", binary_to_decimal);
                printf("  %d. Hex to Decimal\n", hex_to_decimal);
                printf("  %d. Decimal to Binary\n", decimal_to_binary);
                printf("  %d. Decimal to Hex\n", decimal_to_hex);
                printf("  q to Quit\n");
                int choice;
                if (!scanf("%d", &choice)) return 0;  // exits if user enters something other than a digit                                                                        

                switch (choice) {
                        case binary_to_decimal: {
                                GetBinaryFromUser(binary);
                                ConvertBinaryToDecimal(binary, &decimal);
                                printf("Binary: %s\nDecimal: %u\n\n", binary, decimal);
                        } break;
                        case hex_to_decimal: {
                                GetHexFromUser(hex);
                                ConvertHexToDecimal(hex, &decimal);
                                printf("Hex: %s\nDecimal: %u\n\n", hex, decimal);
                        } break;
                        case decimal_to_binary: {
                                GetDecimalFromUser(&decimal);
                                ConvertDecimalToBinary(decimal, binary);
                                printf("Decimal: %u\nbinary: %s\n\n", decimal, binary);
                        } break;
                        case decimal_to_hex: {
                                GetDecimalFromUser(&decimal);
                                ConvertDecimalToHex(decimal, hex);
                                printf("Decimal: %u\nHex: %s\n\n", decimal, hex);
                        } break;
                        default: return 0; // exit if user enters an invalid number                                                                                               
                }
        }
        return 0;
}

void GetBinaryFromUser(char * binary) {
  // write your code here to complete this function                                                                                                                               
  printf("Please enter binary string here: ");
  scanf("%s", binary);
  return;

}

void GetHexFromUser(char * hex) {
  // this function has been written for you                                                                                                                                       
  printf("Please enter hex string here (do include the 0x prefix): ");
  scanf("%s", hex);
  for (char *p = hex; *p; p++)
    if(*p>='a')
      *p-='a'-'A';  // to upper case                                                                                                                                              
  return;
}

void GetDecimalFromUser(unsigned int *x) {
    // write your code here to complete this function                                                                                                                             
  printf("Please enter decimal number here: ");
  scanf("%d", x);
  return;
}

void ConvertBinaryToDecimal(const char * binary, unsigned int *decimal) {
  // write your code here to complete this function                                                                                                                               

  int i = 0;
  int len = 0;

  // string length                                                                                                                                                                
  for (i = 0; binary[i] != '\0'; ++i) {
    len++;
  }

  int dec_val = 0; // decimal value                                                                                                                                               
  int base = 1; // base power for each bit                                                                                                                                        
  int temp = 0;

  /* loop to read in reverse order -- increment dec_val with the number of temp * base                                                                                            
     increase the base power by 2 for each char                                                                                                                                   
  */

  for (i = len-1; i >= 0; i--) {
    temp = binary[i]-48; // conversion from char * to int (ASCII difference of 48)                                                                                                
    if (temp == 1) {
      dec_val += temp * base;
    }
    base *= 2;
  }
  // assign dec_val to *decimal                                                                                                                                                   
  *decimal = dec_val;

  // *decimal = 32; // This hardcoded answer will be incorrect for all but one input. Change this line!                                                                           
  return;
}

void ConvertHexToDecimal(const char *hex, unsigned int *decimal) {
  /* write your code here to complete this function                                                                                                                               
   *decimal = 32;                                                                                                                                                                 
   This hardcoded answer will be incorrect for all but one input. Change this line!                                                                                               
  */

  int i;
  int len = 0;

  // string length                                                                                                                                                                
  for (i = 0; hex[i] != '\0'; ++i) {
    len++;
  }

  char temp = 0;
  unsigned int dec_val = 0;
  int base = 1;
  //read hexadecimal string backwards, breaking the loop at 'x' or 'X'                                                                                                            
  for (i = len-1; i >= 0; i--) {
    temp = hex[i];
    // check for 'x' or 'X'                                                                                                                                                       
    if (temp == 'x' || temp == 'X') {
      break;
    }
    // conditional for integers 0 - 9                                                                                                                                             
    if ( temp > 47 && temp < 58) {
      temp = temp - 48;
      dec_val += temp * base;
    } else if ( temp > 64 && temp < 71) { // A - F                                                                                                                                
      temp = temp - 55; // account for ASCII encoding                                                                                                                             
      dec_val += temp * base;
    }
    base = base * 16; // increment base^16 ('Base 16')                                                                                                                            
  }

  *decimal = dec_val;
  return;
}

void ConvertDecimalToBinary(const unsigned int decimal, char *binary) {
  /* write your code here to complete this function  do not include leading zeros                                                                                                 
     in the answer if the input is 0 then the output should be just 0                                                                                                             
  */

  unsigned int num = decimal; // copy of const decimal                                                                                                                            
  char arr[BINARY_STRING_LENGTH]; // blank char array                                                                                                                             
  int i, j, k;
  i = 0;

  // cite where this comes from                                                                                                                                                   
  // computes each element of the array to a 1 or 0                                                                                                                               
  while (num > 0) {
    arr[i] = (num % 2) + 48; // add 48 to change the ASCII                                                                                                                        
    num = num / 2;
    i++;
  }

  // reverse array and copy to binary                                                                                                                                             
  k = 0;
  for (j = i - 1; j >= 0; j--) {
    binary[k] = arr[j]; // j goes backward; k will move forward                                                                                                                   
    k++;
  }
  binary[k] = '\0';

  //  printf("\n%s\n", binary);                                                                                                                                                   

  /*  binary = "11101"; // This hardcoded answer will be incorrect for all but one input. Change this line! */
    return;
}

void ConvertDecimalToHex(const unsigned int decimal, char *hex) {
  /* write your code here to complete this function do not include leading zeros in the answer                                                                                                     
  // do include the prefix 0x if the input is 0 then the output should be 0x0                                                                                                                      
  */
  unsigned int n = decimal;
  int i = 0;
  char arr[HEX_STRING_LENGTH];

  /* // print test 1 */
  /* printf("\nTesting1...\n"); */
  /* for (int b = 0; b < HEX_STRING_LENGTH; b++) { */
  /*   printf("Element #%d is %c,\n", b, hex[b]); */
  /* } */

  while (n != 0) {
    int temp = 0;
    temp = n % 16;

    if (temp < 10) {
      arr[i] = temp + 48;
      i++;
    } else {
      arr[i] = temp + 55;
      i++;
    }
    n = n / 16;
  }
  arr[i] = '\0';

  // reverse array and copy to binary                                                                                                                                                              
  int j = 0;
  int k = 0;

  for (j = i - 1; j >= 0; j--) {
    hex[k] = arr[j]; // j goes backward; k will move forward                                                                                                                                       
    k++;
  }
  hex[k] = '\0';

  // declare prefix and concatenate into string                                                                                                                                                    
  char prefix[] = "0X";
  strcat(prefix, hex);

    /* // Testing print out of the string 'hex' */
  /* printf("TESTING hex\n"); */
  /* printf("%s\n", hex); */
  /* printf("Testing Prefix -- should include the hexadecimal\n"); */
  /* printf("%s\n", prefix); */

  // copy prefix to hex --> strcpy()                                                                                                                                                               
  strcpy(hex, prefix);

  /* // 2nd Testing print out of the string 'hex' */
  /* printf("TESTING #2 hex\n"); */
  /* printf("%s\n", hex); */

  return;
}
