
#include "printer.h"
#include "read_input.h"
#include "transaction.h"

#include <buba.h>

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace buba;
using namespace std;

bool main_menu(Budget_Battle& buba);
void command_project(Budget_Battle& buba, const inputs_t& inputs);
void command_import(Budget_Battle& buba, const inputs_t& inputs);
void command_bank(Budget_Battle& buba, const inputs_t& inputs);
void command_account(Budget_Battle& buba, const inputs_t& inputs);
void command_transaction(Budget_Battle& buba, const inputs_t& inputs);
void command_label(Budget_Battle& buba, const inputs_t& inputs);
void command_category(Budget_Battle& buba, const inputs_t& inputs);
void command_help();

using param_t = std::vector<std::string>;

struct command_t
{
    std::vector<std::string> cmds;
    int n_params;
    void (*cmd_cb)(Budget_Battle&, const param_t& params);
};

void project_create(Budget_Battle& buba, const param_t& params);

const std::vector<command_t> commands = {{{"project", "create"}, 1, &project_create}};

void project_create(Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;
}

bool process_command();

int main()
{
    Budget_Battle buba;

    //    while(main_menu(buba))
    while(process_command())
    {
    }
}

bool process_command()
{
    const auto inputs = read_input("buba_cli");

    if(inputs.size() == 0)
        return true;

    //    const & cmd = inputs.at(0);

    auto r = std::find_if(commands.begin(), commands.end(), [&inputs](const command_t& c) {
        if(inputs.size() < c.cmds.size())
            return false;

        return std::equal(c.cmds.begin(), c.cmds.end(), inputs.begin());
    });

    if(r != std::end(commands))
    {
        cout << "command found" << endl;
    }
    else
    {
        cout << "command not found" << endl;
    }
    return true;
}
bool main_menu(Budget_Battle& buba)
{
    const auto inputs = read_input("buba_cli");

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
        cerr << red << "[Error] missing arguments" << reset << endl;
        return;
    }

    const auto subcmd = inputs.at(1);

    const auto project_test = "./test.bubap";
    const auto param        = (inputs.size() >= 3) ? inputs.at(2) : project_test;

    if(subcmd == "new" || subcmd == "n")
    {
        if(param == project_test)
            std::system(std::string("rm "s + project_test).c_str());

        if(!buba.project_create(param))
            cerr << red << "[Error] cannot create project:" << param << reset << endl;
        else
            cout << green << "[OK] project created" << reset << endl;
    }
    else if(subcmd == "open" || subcmd == "o")
    {
        if(!buba.project_open(param))
            cerr << red << "[Error] cannot open project:" << param << reset << endl;
        else
            cout << green << "[OK] project opened:" << param << reset << endl;
    }
    else if(subcmd == "close" || subcmd == "c")
    {
        buba.project_close();
        cout << green << "[OK] project closed" << reset << endl;
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_import(Budget_Battle& buba, const inputs_t& inputs)
{
    const auto import_test = "test/res/test3.ofx";
    const auto param       = (inputs.size() < 2) ? import_test : inputs.at(1);

    if(!buba.import_ofx(param))
        cerr << red << "[Error] cannot import OFX file:" << param << reset << endl;
    else
        cout << green << "[OK] OFX file imported:" << param << reset << endl;
}

void command_bank(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << red << "[Error] missing arguments" << reset << endl;
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
            cerr << red << "[Error] missing arguments" << reset << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "name" || cmd3 == "n")
        {
            if(inputs.size() < 5)
            {
                cerr << red << "[Error] missing arguments" << reset << endl;
                return;
            }
            const int id    = std::stoi(inputs.at(3));
            const auto name = inputs.at(4);

            if(!buba.set_bank_name(id, name))
                cerr << red << "[Error] cannot set bank name:" << id << "," << name << reset
                     << endl;
            else
                cout << green << "[OK] bank name set:" << id << "," << name << reset << endl;
        }
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_account(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << red << "[Error] missing arguments" << reset << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        vector<line_t> table{{"Number", "Name", "Balance", "Bank Id"}};

        auto accounts = buba.get_accounts();
        for(auto a : accounts)
        {
            char balance[64];
            std::sprintf(balance, "%.2f", a.balance);

            table.push_back({a.number, a.name, balance, std::to_string(a.bank_id)});
        }

        print_table(table);
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << red << "[Error] missing arguments" << reset << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "name" || cmd3 == "n")
        {
            if(inputs.size() < 5)
            {
                cerr << red << "[Error] missing arguments" << reset << endl;
                return;
            }
            const auto number = inputs.at(3);
            const auto name   = inputs.at(4);

            if(!buba.set_account_name(number, name))
                cerr << red << "[Error] cannot set account name:" << number << "," << name << reset
                     << endl;
            else
                cout << green << "[OK] account name set:" << number << "," << name << reset << endl;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
        }
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_transaction(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << red << "[Error] missing arguments" << reset << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        vector<line_t> table{{"FITID", "Date", "Description", "Amount", "Account", "Label"}};

        auto transactions = buba.get_transactions();
        for(auto t : transactions)
        {
            char amount[64];
            std::sprintf(amount, "%.2f", t.amount);

            table.push_back({t.fitid, t.date, t.description, amount, t.account_number, t.label});
        }
        print_table(table);
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << red << "[Error] missing arguments" << reset << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);
        if(cmd3 == "label" || cmd3 == "l")
        {
            if(inputs.size() < 4)
            {
                cerr << red << "[Error] missing arguments" << reset << endl;
                return;
            }

            const auto cmd4 = inputs.at(3);
            if(cmd4 == "interactive" || cmd4 == "i")
            {
                set_transaction_label_interactive(buba);
            }
            else
            {
                if(inputs.size() < 5)
                {
                    cerr << red << "[Error] missing arguments" << reset << endl;
                    return;
                }

                auto fitid      = inputs.at(3);
                auto label_name = inputs.at(4);

                if(!buba.set_transaction_label(fitid, label_name))
                    cerr << red << "[Error] cannot set transaction label:" << fitid << ","
                         << label_name << reset << endl;
                else
                    cout << green << "[OK] transaction label set:" << fitid << "," << label_name
                         << reset << endl;
            }
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
        }
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_label(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << red << "[Error] missing arguments" << reset << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        std::vector<line_t> table{{"Name", "Category"}};

        auto labels = buba.get_labels();
        for(auto l : labels)
            table.push_back({l.name, l.category_name});

        print_table(table);
    }
    else if(cmd2 == "add" || cmd2 == "a")
    {
        if(inputs.size() < 3)
        {
            cerr << red << "[Error] missing arguments" << reset << endl;
            return;
        }

        const auto name = inputs.at(2);

        if(!buba.add_label(name))
            cerr << red << "[Error] cannot add label:" << name << reset << endl;
        else
            cout << green << "[OK] label added:" << name << reset << endl;
    }
    else if(cmd2 == "set" || cmd2 == "s")
    {
        if(inputs.size() < 3)
        {
            cerr << red << "[Error] missing arguments" << reset << endl;
            return;
        }

        const auto cmd3 = inputs.at(2);

        if(cmd3 == "category" || cmd3 == "c")
        {
            if(inputs.size() < 5)
            {
                cerr << red << "[Error] missing arguments" << reset << endl;
                return;
            }

            auto label    = inputs.at(3);
            auto category = inputs.at(4);

            if(!buba.set_label_category(label, category))
                cerr << red << "[Error] cannot set label category:" << label << "," << category
                     << reset << endl;
            else
                cout << green << "[OK] label category set:" << label << "," << category << reset
                     << endl;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
        }
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_category(Budget_Battle& buba, const inputs_t& inputs)
{
    if(inputs.size() < 2)
    {
        cerr << red << "[Error] missing arguments" << reset << endl;
        return;
    }

    const auto cmd2 = inputs.at(1);

    if(cmd2 == "list" || cmd2 == "l")
    {
        std::vector<line_t> table{{"Name"}};
        auto categories = buba.get_categories();

        for(auto c : categories)
            table.push_back({c.name});

        print_table(table);
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
    }
}

void command_help()
{
    cout << "\nHelp" << endl;
    cout << "    project (p)" << endl;
    cout << "        new   (n) [pathname]" << endl;
    cout << "        open  (o) [pathname]" << endl;
    cout << "        close (c)" << endl;
    cout << "    import (i) [pathname]" << endl;
    cout << "    bank (b)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            name (n) <id> <name>" << endl;
    cout << "    account (a)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            name (n) <id> <name>" << endl;
    cout << "    transaction (t)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            label (l) <fitid> <label_name>" << endl;
    cout << "    label (l)" << endl;
    cout << "        list (l)" << endl;
    cout << "        add  (a) <name>" << endl;
    cout << "        set  (s)" << endl;
    cout << "            category (c) <label_name> <category_name>" << endl;
    cout << "            interactive (i)" << endl;
    cout << "    category (c)" << endl;
    cout << "        list (l)" << endl;
    cout << "    help (h)" << endl;
    cout << "    quit (q)" << endl;
}
