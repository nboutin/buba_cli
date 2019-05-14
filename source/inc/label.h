
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

bool label_list(buba::Budget_Battle& buba, const param_t& params);
bool label_add(buba::Budget_Battle& buba, const param_t& params);
bool label_add_interactive(buba::Budget_Battle& buba, const param_t& params);
bool label_set_category(buba::Budget_Battle& buba, const param_t& params);
