
#include "label.h"
#include "printer.h"
#include "read_input.h"

#include <iostream>

using namespace std;

void add_label_interactive(buba::Budget_Battle& buba, const std::string& label_name)
{
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
                return;
            }
        }
        else if(cmd == "n")
        {
            cout << green << "[OK] label not added" << reset << endl;
            return;
        }
        else
        {
            cerr << red << "[Error] unknown command" << reset << endl;
            continue;
        }
    }
}
