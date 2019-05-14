
#include "read_input.h"
#include "printer.h"

#include <cstring>
#include <iostream>

using namespace std;

inputs_t read_input(const std::string& tag)
{
    cout << cyan << tag << ">" << reset << flush;

    string input;
    inputs_t inputs;

    getline(std::cin, input);

    if(!input.empty())
    {
        const char* delim = " ";
        char* token       = std::strtok(&input[0], delim);
        while(token != nullptr)
        {
            inputs.push_back(token);
            token = std::strtok(nullptr, delim);
        }
    }

    return inputs;
}
