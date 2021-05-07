//----------------------------------------------------------
// No other headers may be added.  Thus, NO use of C-string
//  library <cstring> functions is allowed.  You will get a
//  0 if you use C-string functions like strlen(), strcpy(),
//  strchr(), etc.
//
// You really should not need these functions, however,
// if you feel you do, you may define your own version of
// these or similar functions, but you will need to write
// them yourself.
//----------------------------------------------------------
#include <iostream>
using namespace std;

// Prototypes...Read documentation below
int count_delims(char* str, char delim);
char** csplit(char* str, char delim, int* size);

// Complete this function to calculate the and return the
// number of occurrences of the character, 'delim', in the
// C-string pointed to by 'str'.
//
//  Example: Given the following call:
//     count_delims("a::b: cde", ':')
//  It should return: 3 since ':' occurs 3 times.
int count_delims(char* str, char delim)
{
    int count = 0;
    int i = 0;
    while(str[i] != '\0')
    {
        if(delim == str[i])
        {
            count++;
        }
        i++;
    }

    return count;
    
}

// Complete this function to split the input C-string at any
// occurrence of the delimiter character (i.e. delim) and
// return an array of pointers to the "substrings"
// (i.e. non-empty strings) starting after an occurrence of 
// a delimiter character.  You will likely need to call the
// count_delims() function you defined above to help perform
// this task correctly.  You will also need to return the
// size of the array of pointers in the value pointed to by
// 'size' (i.e. which is passed by reference).
//
// Supposing the delimiter is ' ', and the input string is
// "hello world bye world", return an array of 4
// character pointers that would point at the start of
// "hello", "world", "bye", "world", respectively, and
// the integer pointed to by size should be set to 4.

char** csplit(char* str, char delim, int* size)
{
    int counter;
    int len = 0;
    counter = count_delims(str, delim);
    *size = counter;
    int i = 0;

    while(str[i] != '\0')
    {
        len++;
        i++;
    }

    char** char_pointers = new char*[*size];
    
    for(int i = 0; i<len; i++)
    {
        char_pointers[i] = new char;
        
    }
    for(int i = 0; i<len; i++)
    {
        for(int j = 0; j<*size; j++)
        { 
            if(str[i] == delim)
            {
                char_pointers[i][j] = str[i-1];
            }    
        }
    }

   return char_pointers;

}



// don't change this -- Ensure main() is bracketed
// by this line and the #endif at the bottom and
// the functions above should stay above (i.e. don't move
// the code around).
#ifndef LIBONLY

int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Please provide 1=comma, 2=space, 3=colon" << endl;
    return 1;
  }
  char line[80];
  cin.getline(line, 80);
  char** substrs;   // Use this for the return value
                    // when you call csplit()
  
  int n;            // Should be used to store the number
                    // of pointers (size of the array)
                    // returned by csplit()
  
  //--------------------------------------------------------
  //  Complete the code below - Do NOT change
  //     code in main() above this point.
  //--------------------------------------------------------
  //  Now split the string that is stored in
  //  'line' using the delimeter specified
  //  by the command line argument code:
  //     1 = ','
  //     2 = ' ' (i.e. space)
  //     3 = ':'
  //
  //  You should declare necessary variables, call the
  //  csplit function with necessary arguments, and store
  //  the return value in the 'substrs' variable declared
  //  above.  Our code will then print out the substrings.
  //  You may then add any additional code you need to
  //  meet other requirements of the program but you may
  //  NOT change the code that prints the substirngs.
  //
  //  No valgrind errors (other than the normal 1 allocation
  //  of around 72000 bytes that Valgrind always reports)
  //  should exist.
  //
  
    if(atoi(argv[1]) == 1)
    {
        substrs = csplit(line, ',', &n);
    }
    
    else if(atoi(argv[1]) == 2)
    {
        substrs = csplit(line, ' ', &n);
    } 
    else if(atoi(argv[1]) == 3)
    {
        substrs = csplit(line, ':', &n);
    }
    

  // You must use this code to print the substrings
  for(int i = 0; i < n; i++){
    cout << substrs[i] << endl;
  }

  // Feel free to add more code below
   for(int i = 0; i<n; i++)
   { 
       delete [] substrs[i];
   }
    delete [] substrs;
    
    

  return 0;
}

// Don't change this
#endif