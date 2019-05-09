
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
void command_import(Budget_Battle& buba, const inputs_t& inputs);
void command_bank(Budget_Battle& buba, const inputs_t& inputs);
void command_account(Budget_Battle& buba, const inputs_t& inputs);
void command_transaction(Budget_Battle& buba, const inputs_t& inputs);
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
    else if(command == "bank" || command == "b")
    {
        command_bank(buba, inputs);
    }
    else if(command == "account" || command == "a")
    {
        command_account(buba, inputs);
    }
    else if(command == "transaction" || command == "t")
    {
        command_transaction(buba, inputs);
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
    if(inputs.size() < 2)
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

void command_bank(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        cout << "+---id---+---name---+" << endl;
        auto banks = buba.get_banks();
        for(auto b : banks)
        {
            cout << "|" << b.id << "|" << b.name << "|" << endl;
        }
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << "error: missing arguments" << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "name" || cmd3 == "n")
        {
            if(inputs.size() < 5)
            {
                cerr << "error: missing arguments" << endl;
                return;
            }
            const int id    = std::stoi(inputs.at(3));
            const auto name = inputs.at(4);

            buba.set_bank_name(id, name);
        }
    }
}

void command_account(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        cout << "+---number---+---name---+---bank id ---+" << endl;
        auto accounts = buba.get_accounts();
        for(auto a : accounts)
        {
            cout << "|" << a.number << "|" << a.name << "|" << a.bank_id << "|" << endl;
        }
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << "error: missing arguments" << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "name" || cmd3 == "n")
        {
            if(inputs.size() < 5)
            {
                cerr << "error: missing arguments" << endl;
                return;
            }
            const auto number = inputs.at(3);
            const auto name   = inputs.at(4);

            buba.set_account_name(number, name);
        }
    }
}

void command_transaction(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto subcmd = inputs.at(1);

    if(subcmd == "list" || subcmd == "l")
    {
        cout
            << "+---FITID---+---Date---+-----Description-----+---Amount---+---Account---+---Label---+"
            << endl;

        auto transactions = buba.get_transactions();
        for(auto o : transactions)
        {
            cout << "[" << o.fitid << "|" << o.date << "|" << o.description << "|" << o.amount
                 << "|" << o.account_number << "|" << o.label << "]" << endl;
        }
    }
}

void command_help()
{
    cout << "\nHelp" << endl;
    cout << "  p, project" << endl;
    cout << "    n, new [pathname]" << endl;
    cout << "    o, open [pathname]" << endl;
    cout << "    c, close" << endl;
    cout << "  i, import [pathname]" << endl;
    cout << "  b, bank" << endl;
    cout << "    l, list" << endl;
    cout << "    s, set" << endl;
    cout << "      n, name [id, name]" << endl;
    cout << "  a, account" << endl;
    cout << "    l, list" << endl;
    cout << "    s, set" << endl;
    cout << "      n, name [id, name]" << endl;
    cout << "  t, transaction" << endl;
    cout << "    l, list" << endl;
    cout << "  h, help" << endl;
    cout << "  q, quit" << endl;
}
