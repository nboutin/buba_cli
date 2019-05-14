
#pragma once

#include <string>
#include <vector>

namespace buba
{
class Budget_Battle;
}

using param_t = std::vector<std::string>;

struct command_t
{
    std::vector<std::string> cmds;
    int n_params;
    bool (*cmd_cb)(buba::Budget_Battle&, const param_t& params);
};

bool process_command(const std::vector<command_t>& commands, buba::Budget_Battle& buba);
