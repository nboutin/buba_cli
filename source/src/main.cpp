
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
    const auto inputs  = read_menu_input();
    const auto command = inputs.at(0);

    if(command == "project")
    {
        command_project(buba, inputs);
    }
    else if(command == "import")
    {
        command_import(buba, inputs);
    }
    else if(command == "list")
    {
        command_list(buba, inputs);
    }
    else if(command == "help")
    {
        command_help();
    }
    else if(command == "quit")
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

    if(subcmd == "new")
    {
        //    	std::system("rm project_test");
        if(!buba.create_project(param))
            cerr << "error: cannot create project" << endl;
        else
            cout << "ok" << endl;
    }
    else if(subcmd == "open")
    {
        if(!buba.open_project(param))
            cerr << "error: cannot open project" << endl;
        else
            cout << "ok" << endl;
    }
    else if(subcmd == "close")
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

    auto transactions = buba.get_transactions_all();
    for(auto o : transactions)
    {
        cout << "[" << o.fitid << "," << o.date << "," << o.description << "," << o.amount << "]"
             << endl;
    }
}

void command_help()
{
    cout << "Buba_cli" << endl;
    cout << "project" << endl;
    cout << "\tnew [pathname]" << endl;
    cout << "\topen [pathname]" << endl;
    cout << "\tclose" << endl;
    cout << "import [pathname]" << endl;
    cout << "list" << endl;
    cout << "help" << endl;
    cout << "quit" << endl;
}

#if 0
bool action_menu(Budget_Battle& buba)
{
	cout << "\nAction Menu:\n[1]Import OFX\n[2]List transactions\n[3]Back" << endl;

	switch(read_menu_input())
	{
	case 1:
		buba.import_ofx("test/res/test3.ofx");
		cout << "# OFX imported" << endl;
		break;
	case 2:
	{
		auto transactions = buba.get_transactions_all();
		for(auto o : transactions)
		{
			cout << "[" << o.fitid << "," << o.date << "," << o.description << "," << o.amount
				 << "]" << endl;
		}
		cout << "# Done" << endl;
		break;
	}
	case 3: return false;
	}
	return true;
}
#endif
