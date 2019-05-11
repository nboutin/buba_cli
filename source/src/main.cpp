
#include "printer.h"

#include <buba.h>

#include <algorithm>
#include <cstring>
#include <iomanip>
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
void command_label(Budget_Battle& buba, const inputs_t& inputs);
void command_category(Budget_Battle& buba, const inputs_t& inputs);
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
    else if(command == "label" || command == "l")
    {
        command_label(buba, inputs);
    }
    else if(command == "category" || command == "c")
    {
        command_category(buba, inputs);
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
        vector<line_t> table{{"id", "name"}};

        auto banks = buba.get_banks();
        for(auto b : banks)
            table.push_back({std::to_string(b.id), b.name});

        print_table(table);
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
        vector<line_t> table{{"Number", "Name", "Bank Id"}};

        auto accounts = buba.get_accounts();
        for(auto a : accounts)
            table.push_back({a.number, a.name, std::to_string(a.bank_id)});

        print_table(table);
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

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        //        cout
        //            <<
        //            "+---FITID---+---Date---+-----Description-----+---Amount---+---Account---+---Label---+"
        //            << endl;
        //
        //        auto transactions = buba.get_transactions();
        //        for(auto o : transactions)
        //        {
        //            cout << "[" << o.fitid << "|" << o.date << "|" << o.description << "|" <<
        //            o.amount
        //                 << "|" << o.account_number << "|" << o.label << "]" << endl;
        //        }
        vector<line_t> table{{"FITID", "Date", "Description", "Amount", "Account", "Label"}};

        auto transactions = buba.get_transactions();
        for(auto t : transactions)
            table.push_back(
                {t.fitid, t.date, t.description, std::to_string(t.amount), t.account_number, t.label});

        print_table(table);
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << "error: missing arguments" << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "label" || cmd3 == "l")
        {
            if(inputs.size() < 5)
            {
                cerr << "error: missing arguments" << endl;
                return;
            }

            auto fitid      = inputs.at(3);
            auto label_name = inputs.at(4);

            buba.set_transaction_label(fitid, label_name);
        }
    }
}

void command_label(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        cout << "+---Name---+---Category---+" << endl;

        auto labels = buba.get_labels();
        for(auto l : labels)
        {
            cout << "|" << l.name << "|" << l.category_name << "|" << endl;
        }
    }
    else if(cmd2 == "add" || cmd2 == "a")
    {
        if(inputs.size() < 3)
        {
            cerr << "error: missing arguments" << endl;
            return;
        }

        const auto name = inputs.at(2);

        buba.add_label(name);
    }
}

void command_category(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << "error: missing arguments" << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        auto categories = buba.get_categories();

        auto max = std::max_element(
            categories.begin(), categories.end(), [](const Category_t& a, const Category_t& b) {
                return a.name.size() < b.name.size();
            });

        string title = "+---Name";
        cout << title << setfill('-') << setw(max->name.size() - title.size() + 2) << "+" << endl;

        for(auto c : categories)
        {
            cout << "|" << c.name << setfill(' ') << setw(max->name.size() - c.name.size() + 1)
                 << "|" << endl;
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
    cout << "    s, set" << endl;
    cout << "      l, label [fitid, label_name]" << endl;
    cout << "  l, label" << endl;
    cout << "    l, list" << endl;
    cout << "    a, add [name]" << endl;
    cout << "  c, category" << endl;
    cout << "    l, list" << endl;
    cout << "  h, help" << endl;
    cout << "  q, quit" << endl;
}
