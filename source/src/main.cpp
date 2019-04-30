
#include <buba.h>

#include <iostream>
#include <string>

using namespace buba;
using namespace std;

int main()
{
    cout << "\nBudget Battle CLI\n" << endl;
    cout << "Main Menu:\n[1]Create Project\n[2]Open project" << endl;

    string input;
    int input_value;
    getline(std::cin, input);
    if(!input.empty())
    {
        input_value = std::stoi(input);
    }

    Budget_Battle buba;
    switch(input_value)
    {
    case 1:
        std::system("rm project_test");
        buba.create_project("./project_test");
        break;
    case 2: break;
    }
}
