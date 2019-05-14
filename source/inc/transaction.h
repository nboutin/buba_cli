
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

bool transaction_list(buba::Budget_Battle& buba, const param_t& params);
bool transaction_set_label(buba::Budget_Battle& buba, const param_t& params);
bool transaction_set_label_interactive(buba::Budget_Battle& buba, const param_t& params);
