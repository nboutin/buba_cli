
#include "category.h"
#include "printer.h"
#include "read_input.h"

#include <buba.h>

#include <iostream>

using namespace std;

bool category_list(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    std::vector<line_t> table{{"Name"}};
    auto categories = buba.get_categories();

    for(auto c : categories)
        table.push_back({c.name});

    print_table(table);

    return true;
}
