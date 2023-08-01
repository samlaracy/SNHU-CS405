// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
  
    // Throws standard exception
    throw std::exception("Standard exception");

    return true;
}

class my_exception : public std::exception {
public:
    const char* what() const throw() {
        return "Custom exception thrown.";
    }
};

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // Wraps the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
   

    // Throws a custom exception derived from std::exception
    //  and catch it explictly in main
    throw my_exception();

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // Throws an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::exception("Cannot divide by zero.");
    }
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    //  Creates an exception handler to capture ONLY the exception thrown
    //  by divide.
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Division Exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // Creates exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const my_exception& my_e) {
        std::cout << "Custom Exception: " << my_e.what() << std::endl;
    }
    catch (const std::exception& std_e) {
        std::cout << "Standard Exception: " << std_e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Uncaught Exception Found" << std::endl;
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
