
#include "command.h"
#include "printer.h"
#include "read_input.h"

#include <algorithm>
#include <iostream>

using namespace buba;
using namespace std;

bool process_command(const std::vector<command_t>& commands, Budget_Battle& buba)
{
    const auto inputs = read_input("buba_cli");

    if(inputs.size() == 0)
        return true;

    auto r = std::find_if(commands.begin(), commands.end(), [&inputs](const command_t& c) {
        if(inputs.size() < c.cmds.size())
            return false;

        return std::equal(c.cmds.begin(), c.cmds.end(), inputs.begin());
    });

    // Command found
    if(r != std::end(commands))
    {
        param_t param(inputs.begin() + r->cmds.size(), inputs.end());

        return r->cmd_cb(buba, param);
    }
    else
    {
        cerr << red << "[Error] unknown command" << reset << endl;
        return true;
    }
}
