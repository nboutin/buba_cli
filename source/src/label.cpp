
#include "label.h"
#include "read_input.h"

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
                continue;
            else
                return;
        }
        else if(cmd == "n")
            return;
        else
            continue;
    }
}
