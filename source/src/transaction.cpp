
#include "transaction.h"
#include "label.h"
#include "printer.h"
#include "read_input.h"

#include <buba.h>

#include <iostream>
#include <vector>

using namespace std;

bool transaction_list(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    vector<line_t> table{{"FITID", "Date", "Description", "Amount", "Account", "Label"}};

    auto transactions = buba.get_transactions();
    for(auto t : transactions)
    {
        char amount[64];
        std::sprintf(amount, "%.2f", t.amount);

        table.push_back({t.fitid, t.date, t.description, amount, t.account_number, t.label});
    }
    print_table(table);

    return true;
}

bool transaction_set_label(buba::Budget_Battle& buba, const param_t& params)
{
    auto fitid      = params.at(0);
    auto label_name = params.at(1);

    if(!buba.set_transaction_label(fitid, label_name))
        cerr << red << "[Error] cannot set transaction label:" << fitid << "," << label_name
             << reset << endl;
    else
        cout << green << "[OK] transaction label set:" << fitid << "," << label_name << reset
             << endl;

    return true;
}

bool transaction_set_label_interactive(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    auto transactions = buba.get_transactions_without_label();

    if(transactions.size() == 0)
    {
        cout << green << "[OK] transaction list is empty" << reset << endl;
        return true;
    }

    for(auto i = 0u; i < transactions.size(); ++i)
    {
        auto t = transactions[i];

        // Show current transactions
        vector<line_t> table{{"FITID", "Date", "Description", "Amount", "Account", "Label"}};

        char amount[64];
        std::sprintf(amount, "%.2f", t.amount);

        table.push_back({t.fitid, t.date, t.description, amount, t.account_number, t.label});
        print_table(table);

        // Ask user input
        auto inputs = read_input("interactive[set(s) <label>, pass(p), list (l), quit(q)]");

        if(inputs.size() < 1)
        {
            cerr << red << "[Error] missing command" << reset << endl;
            i--;
            continue;
        }

        const auto cmd = inputs.at(0);

        if(cmd == "set" || cmd == "s")
        {
            if(inputs.size() < 2)
            {
                cerr << red << "[Error] missing label name" << reset << endl;
                i--;
                continue;
            }

            const auto label_name = inputs.at(1);

            if(!buba.set_transaction_label(t.fitid, label_name))
            {
                cerr << red << "[Error] cannot set transaction label:" << t.fitid << ","
                     << label_name << reset << endl;

                label_add_interactive(buba, {label_name});
                --i;
                continue;
            }
            else
            {
                cout << green << "[OK] label set" << reset << endl;
            }
        }
        else if(cmd == "pass" || cmd == "p")
        {
            cout << green << "[OK] pass" << reset << endl;
            continue;
        }
        else if(cmd == "list" || cmd == "l")
        {
            label_list(buba, {});
            --i;
            continue;
        }
        else if(cmd == "quit" || cmd == "q")
        {
            cout << green << "[OK] quit" << reset << endl;
            return true;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
            --i;
            continue;
        }
    }
    return true;
}
