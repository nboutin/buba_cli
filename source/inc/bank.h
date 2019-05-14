
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

bool bank_list(buba::Budget_Battle& buba, const param_t& params);
bool bank_set_name(buba::Budget_Battle& buba, const param_t& params);
