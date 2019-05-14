
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

bool project_new(buba::Budget_Battle& buba, const param_t& params);
bool project_open(buba::Budget_Battle& buba, const param_t& params);
bool project_close(buba::Budget_Battle& buba, const param_t& params);
