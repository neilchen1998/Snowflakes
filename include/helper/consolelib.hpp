#ifndef INCLUDE_HELPER_CONSOLELIB_H_
#define INCLUDE_HELPER_CONSOLELIB_H_

#include <iostream>
#include <string>   // std::stod
#include <string_view>  // std::string_view

#define MAX_ERR_CNT 5

// template specialization
template<typename T>
struct Prompt
{
    static std::string_view Get()
    {
        return "Enter a value between: ";
    }
};

template<>
struct Prompt<int>
{
    static std::string_view Get()
    {
        return "Enter an integer between: ";
    }
};

// works for both of type double and float (requires C++20)
template<typename T>
requires std::is_same_v<T, double> || std::is_same_v<T, float>
struct Prompt<T>
{
    static std::string_view Get()
    {
        return "Enter a decimal between: ";
    }
};

/// @brief Get the user's input from the console and store it to the given variable (type integer only)
/// @param val the variable
/// @param varName the name of the variable
/// @param low the lower bound (inclusive)
/// @param high the uppder bound (inclusive)
/// @return if the variable is successfully set
template<typename T>
bool GetUserInput(T& val, const std::string_view& varName, const T low, const T high)
{
    std::string buffer;

    // asks the user to input within the given number of tries
    unsigned char errCnt = 0;
    while(errCnt < MAX_ERR_CNT)
    {
        std::cout << Prompt<T>::Get() << low << " and " << high << " for " << varName << ": ";
        if (std::getline(std::cin, buffer) && !buffer.empty())
        {
            // try to convert the input string to of type int
            try
            {
                // converts the input string to an integer
                std::size_t pos{};
                val = static_cast<T>(std::stod(buffer, &pos));

                // checks if the value is within bound
                if (val >= low && val <= high)
                {
                    std::cout << varName << "is set to: " << val << "\n";
                    return true;
                }
                else
                {
                    // displays error message and clear the buffer so it is ready for the next try
                    std::cerr << Prompt<T>::Get() << low << " and " << high << " (inclusive)\n";
                    buffer.clear();
                }
            }
            // if the input cannot be converted to of type integer
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << " (no conversion)\n";
            }
            // other errors
            catch (...)
            {
                std::cerr << "Error: Caught unknown exception\n";
            }
        }

        ++errCnt;
    }
    
    return false;
}

#endif  // INCLUDE_HELPER_CONSOLELIB_H_