
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

bool account_list(buba::Budget_Battle& buba, const param_t& params);
bool account_set_name(buba::Budget_Battle& buba, const param_t& params);
