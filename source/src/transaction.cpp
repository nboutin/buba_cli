
#include "transaction.h"
#include "label.h"
#include "printer.h"
#include "read_input.h"

#include <iostream>
#include <vector>

using namespace std;

void set_transaction_label_interactive(buba::Budget_Battle& buba)
{
    auto transactions = buba.get_transactions_without_label();

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
        auto inputs = read_input("interactive[set <label>, pass, quit]");

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

                add_label_interactive(buba, label_name);
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
        else if(cmd == "quit" || cmd == "q")
        {
            cout << green << "[OK] quit" << reset << endl;
            return;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
            --i;
            continue;
        }
    }
}
