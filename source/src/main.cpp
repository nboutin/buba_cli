
#include <buba.h>

#include <iostream>
#include <string>

using namespace buba;
using namespace std;

int read_menu_input();
void main_menu(Budget_Battle& buba);
void action_menu(Budget_Battle& buba);

int main()
{
    cout << "\nBudget Battle CLI\n" << endl;
    Budget_Battle buba;

    main_menu(buba);
    action_menu(buba);
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

void main_menu(Budget_Battle& buba)
{
    cout << "Main Menu:\n[1]Create Project\n[2]Open project" << endl;

    switch(read_menu_input())
    {
    case 1:
        std::system("rm project_test");
        buba.create_project("./project_test");
        break;
    case 2: break;
    }
}

void action_menu(Budget_Battle& buba)
{
    cout << "Action Menu:\n[1]Import OFX" << endl;

    switch(read_menu_input())
    {
    case 1: buba.import_ofx("../buba_engine/doc/res/comptes.ofx"); break;
    }
}
