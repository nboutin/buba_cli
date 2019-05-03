
#include <buba.h>

#include <iostream>
#include <string>

using namespace buba;
using namespace std;

int read_menu_input();
bool main_menu(Budget_Battle& buba);
bool action_menu(Budget_Battle& buba);

int main()
{
    cout << "\nBudget Battle CLI" << endl;
    Budget_Battle buba;

    while(main_menu(buba))
    {
        while(action_menu(buba))
        {
        }
    }
}

int read_menu_input()
{
    string input;
    int input_value = 0;
    getline(std::cin, input);
    if(!input.empty())
    {
        input_value = std::stoi(input);
    }

    return input_value;
}

bool main_menu(Budget_Battle& buba)
{
    cout << "\nMain Menu:\n[1]Create Project\n[2]Open project\n[3]Exit" << endl;

    switch(read_menu_input())
    {
    case 1:
        std::system("rm project_test");
        buba.create_project("./project_test");
        cout << "# project created" << endl;
        break;
    case 2: break; ;
    case 3: return false;
    }

    return true;
}

bool action_menu(Budget_Battle& buba)
{
    cout << "\nAction Menu:\n[1]Import OFX\n[2]List operations\n[3]Back" << endl;

    switch(read_menu_input())
    {
    case 1:
        buba.import_ofx("test/res/test2.ofx");
        cout << "# OFX imported" << endl;
        break;
    case 2:
    {
        auto operations = buba.get_operations_all();
        for(auto o : operations)
        {
            cout << "[" << o.date << "," << o.description << "," << o.amount << "]" << endl;
        }
        cout << "# Done" << endl;
        break;
    }
    case 3: return false;
    }
    return true;
}
