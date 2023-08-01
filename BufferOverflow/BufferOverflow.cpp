// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  const std::string account_number = "CharlieBrown42";
  char user_input[20];
  // declares buffer_input variable
  char buffer_input[50];
  
  std::cout << "Enter a value: ";

  // reads in the first 50 lines from the user and stores it in buffer_input
  std::cin.getline(buffer_input, 50);
  // if the buffer input is greater than or equal to 20 (equal to because of the null terminator when copying the buffer_input into the user_input)
  if (strlen(buffer_input) >= 20) {
	  std::cout << "You entered: " << buffer_input << std::endl;
	  // displays that a potential buffer overflow has occurred
	  std::cout << "Potential Buffer Overflow Detected" << std::endl;
  }
  else {
	  // copies the buffer_input into the user_input
	  strncpy_s(user_input, buffer_input, strlen(buffer_input));
	  std::cout << "You entered: " << user_input << std::endl;
	  std::cout << "Account Number = " << account_number << std::endl;
  }
  
  
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
