
#include <buba.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace buba;
using namespace std;

using inputs_t = std::vector<std::string>;

inputs_t read_menu_input();
bool main_menu(Budget_Battle& buba);
void command_project(Budget_Battle& buba, const inputs_t& inputs);
void command_list(Budget_Battle& buba, const inputs_t& inputs);
void command_import(Budget_Battle& buba, const inputs_t& inputs);
void command_help();

int main()
{
    Budget_Battle buba;

    while(main_menu(buba))
    {
    }
}

inputs_t read_menu_input()
{
    cout << "buba_cli>" << flush;

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

bool main_menu(Budget_Battle& buba)
{
    const auto inputs = read_menu_input();

    if(inputs.size() == 0)
        return true;

    const auto command = inputs.at(0);

    if(command == "project" || command == "p")
    {
        command_project(buba, inputs);
    }
    else if(command == "import" || command == "i")
    {
        command_import(buba, inputs);
    }
    else if(command == "list" || command == "l")
    {
        command_list(buba, inputs);
    }
    else if(command == "help" || command == "h")
    {
        command_help();
    }
    else if(command == "quit" || command == "q")
    {
        return false;
    }
    return true;
}

void command_project(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() <= 1)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto subcmd = inputs.at(1);
    const auto param  = (inputs.size() >= 3) ? inputs.at(2) : "./test.bubap";

    if(subcmd == "new" || subcmd == "n")
    {
        std::system("rm test.bubap");
        if(!buba.create_project(param))
            cerr << "error: cannot create project" << endl;
        else
            cout << "ok" << endl;
    }
    else if(subcmd == "open" || subcmd == "o")
    {
        if(!buba.open_project(param))
            cerr << "error: cannot open project" << endl;
        else
            cout << "ok" << endl;
    }
    else if(subcmd == "close" || subcmd == "c")
    {
        cerr << "error: cannot close project" << endl;
    }
}

void command_import(Budget_Battle& buba, const inputs_t& inputs)
{
    const auto param = (inputs.size() >= 2) ? inputs.at(2) : "test/res/test3.ofx";

    if(!buba.import_ofx(param))
        cerr << "error: cannot import ofx" << endl;
    else
        cout << "ok" << endl;
}

void command_list(Budget_Battle& buba, const inputs_t& inputs)
{
    (void) inputs;

    cout << "+---FITID---+---Date---+-----Description-----+---Amount---+" << endl;

    auto transactions = buba.get_transactions_all();
    for(auto o : transactions)
    {
        cout << "[" << o.fitid << "," << o.date << "," << o.description << "," << o.amount << "]"
             << endl;
    }
}

void command_help()
{
    cout << "\nBuba_cli\n" << endl;
    cout << "\tproject" << endl;
    cout << "\t\tnew [pathname]" << endl;
    cout << "\t\topen [pathname]" << endl;
    cout << "\t\tclose" << endl;
    cout << "\timport [pathname]" << endl;
    cout << "\tlist" << endl;
    cout << "\thelp" << endl;
    cout << "\tquit" << endl;
}
