
#include "label.h"
#include "printer.h"
#include "read_input.h"

#include <buba.h>

#include <iostream>

using namespace std;

bool label_list(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    std::vector<line_t> table{{"Name", "Category"}};

    auto labels = buba.get_labels();
    for(auto l : labels)
        table.push_back({l.name, l.category_name});

    print_table(table);
    return true;
}

bool label_add(buba::Budget_Battle& buba, const param_t& params)
{
    const auto name = params.at(0);

    if(!buba.add_label(name))
        cerr << red << "[Error] cannot add label:" << name << reset << endl;
    else
        cout << green << "[OK] label added:" << name << reset << endl;

    return true;
}

bool label_add_interactive(buba::Budget_Battle& buba, const param_t& params)
{
    const auto label_name = params.at(0);

    while(1)
    {
        auto inputs = read_input("add label [" + label_name + "] (y,n)");

        if(inputs.size() < 1)
            continue;

        const auto cmd = inputs.at(0);

        if(cmd == "y")
        {
            if(!buba.add_label(label_name))
            {
                cerr << red << "[Error] cannot add label " << label_name << reset << endl;
                continue;
            }
            else
            {
                cout << green << "[OK] label added" << reset << endl;
                return true;
            }
        }
        else if(cmd == "n")
        {
            cout << green << "[OK] label not added" << reset << endl;
            return true;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
            continue;
        }
    }
    return true;
}

bool label_set_category(buba::Budget_Battle& buba, const param_t& params)
{
    auto label    = params.at(0);
    auto category = params.at(1);

    if(!buba.set_label_category(label, category))
        cerr << red << "[Error] cannot set label category:" << label << "," << category << reset
             << endl;
    else
        cout << green << "[OK] label category set:" << label << "," << category << reset << endl;

    return true;
}
