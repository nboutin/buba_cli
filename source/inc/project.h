
#pragma once

#include "command.h"

namespace buba
{
class Budget_Battle;
}

void project_create(buba::Budget_Battle& buba, const param_t& params);
void project_open(buba::Budget_Battle& buba, const param_t& params);
void project_close(buba::Budget_Battle& buba, const param_t& params);
