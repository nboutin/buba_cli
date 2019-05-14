
#include "bank.h"
#include "printer.h"

#include <buba.h>

#include <iostream>
#include <vector>

using namespace std;

bool bank_list(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    vector<line_t> table{{"id", "name"}};

    auto banks = buba.get_banks();
    for(auto b : banks)
        table.push_back({std::to_string(b.id), b.name});

    print_table(table);
    return true;
}

bool bank_set_name(buba::Budget_Battle& buba, const param_t& params)
{
    const int id    = std::stoi(params.at(0));
    const auto name = params.at(1);

    if(!buba.set_bank_name(id, name))
        cerr << red << "[Error] cannot set bank name:" << id << "," << name << reset << endl;
    else
        cout << green << "[OK] bank name set:" << id << "," << name << reset << endl;

    return true;
}
