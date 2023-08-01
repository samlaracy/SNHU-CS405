// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // if the result is greater than the max numeric limit minus the increment, the sum of the result and increment will be
        // greater than the max numeric limit and an overflow will occur
        if (result > (std::numeric_limits<T>::max() - increment)) {
            // throws an overflow exception
            throw std::overflow_error("Overflow has occurred");
        }
        // else no overflow will occur
        else {
            result += increment;
        }
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        
        // if the result is less than the minimum value plus the decrement, the difference between the result and decrement will
        // be less than the minimum value and an underflow will occur
        if (result < (std::numeric_limits<T>::min() + decrement)) {
            // throws an underflow exception 
            throw std::underflow_error("Underflow has occurred");
        }
        // else no underflow will occur
        else {
            result -= decrement;
        }
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE
    
    // declare result variable
    T result;

    // tests to see if overflow occurs (in this case, it shouldn't)
    try {
        std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
        result = add_numbers<T>(start, increment, steps);
        std::cout << +result << std::endl;
    }
    catch (std::overflow_error error) { // catches the overflow
        std::cout << "ERROR: numeric overflow has occurred" << std::endl;
    }
    // tests to see if overflow occurs  (in this case, it should)
    try {
        std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
        result = add_numbers<T>(start, increment, steps + 1);
        std::cout << +result << std::endl;
    }
    catch (std::overflow_error error) { // catches the overflow
        std::cout << "ERROR: numeric overflow has occurred" << std::endl;
    }
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // declares new starting point for variable types below zero
    const T zero_start = 0;
    // declares new starting point for variable types that use decimals
    const T decimal_start = std::numeric_limits<T>::min() * 6;
    // declares new decrement for variable types of that use decimals
    const T decimal_decrement = std::numeric_limits<T>::min();
    // declares result variable
    T result;

    // if the minimum numeric limit is less than 0, a new starting point is needed for underflow to occur
    if (std::numeric_limits<T>::min() < 0) {

        // tests to see if underflow occurs (in this case, it shouldn't)
        try {
            std::cout << "\tSubtracting Numbers Without Underflow (" << +zero_start << ", " << +decrement << ", " << steps << ") = ";
            result = subtract_numbers<T>(zero_start, decrement, steps);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }

        // tests to see if underflow occurs (in this case, it should)
        try {
            std::cout << "\tSubtracting Numbers With Underflow (" << +zero_start << ", " << +decrement << ", " << (steps + 1) << ") = ";
            result = subtract_numbers<T>(zero_start, decrement, steps + 1);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }
    }
    else if (std::numeric_limits<T>::min() == 0){ // else if the minimum numeric limit is 0
        // tests to see if underflow occurs (in this case, it shouldn't)
        try {
            std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
            result = subtract_numbers<T>(start, decrement, steps);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }
        // tests to see if underflow occurs (in this case, it should)
        try {
            std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
            result = subtract_numbers<T>(start, decrement, steps + 1);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }
    }
    else { // the minimum value is greater than 0 (reserved for numbers with decimal values)
        try {
            std::cout << "\tSubtracting Numbers Without Underflow (" << +decimal_start << ", " << +decimal_decrement << ", " << steps << ") = ";
            result = subtract_numbers<T>(decimal_start, decimal_decrement, steps);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }

        try {
            std::cout << "\tSubtracting Numbers Without Underflow (" << +decimal_start << ", " << +decimal_decrement << ", " << steps + 1 << ") = ";
            result = subtract_numbers<T>(decimal_start, decimal_decrement, steps + 1);
            std::cout << +result << std::endl;
        }
        catch (std::underflow_error error) { // catches the underflow
            std::cout << "ERROR: numeric underflow has occurred" << std::endl;
        }
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu