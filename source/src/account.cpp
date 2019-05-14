
#include "import.h"
#include "printer.h"

#include <buba.h>

#include <iostream>

using namespace std;

bool account_list(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    vector<line_t> table{{"Number", "Name", "Balance", "Bank Id"}};

    auto accounts = buba.get_accounts();
    for(auto a : accounts)
    {
        char balance[64];
        std::sprintf(balance, "%.2f", a.balance);

        table.push_back({a.number, a.name, balance, std::to_string(a.bank_id)});
    }

    print_table(table);
    return true;
}

bool account_set_name(buba::Budget_Battle& buba, const param_t& params)
{
    const auto number = params.at(0);
    const auto name   = params.at(1);

    if(!buba.set_account_name(number, name))
        cerr << red << "[Error] cannot set account name:" << number << "," << name << reset << endl;
    else
        cout << green << "[OK] account name set:" << number << "," << name << reset << endl;

    return true;
}
