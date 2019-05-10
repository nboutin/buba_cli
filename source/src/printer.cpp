
#include "printer.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

std::vector<line_t> transpose(const std::vector<line_t>& table);

/*
+Title1--+Title2--+
|value   |value   +
*/
void print_table(const std::vector<line_t> table)
{
    using namespace std;

    const auto sep_title = '+';
    const auto sep_value = '|';

    // find max size by column
    auto table_transposed = transpose(table);

    std::vector<int> maxs;
    for(auto l : table_transposed)
    {
        auto max = std::max_element(l.begin(), l.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        maxs.push_back(max->size());
    }

    auto sep = sep_title;
    for(auto line = 0u; line < table.size(); ++line)
    {
        if(line == 0)
            sep = sep_title;
        else
            sep = sep_value;

        for(auto column = 0u; column < table[line].size(); ++column)
        {
            auto value = table[line][column];
            auto width = maxs.at(column) - value.size() + 1;
            cout << sep << " " << value << setw(width) << " ";
        }
        cout << sep << "\n";
    }
    cout << "\n" << flush;
}

std::vector<line_t> transpose(const std::vector<line_t>& table)
{
    std::vector<line_t> transposed(table[0].size(), line_t(table.size()));

    for(auto i = 0u; i < table.size(); ++i)
    {
        for(auto j = 0u; j < table[i].size(); ++j)
        {
            transposed[j][i] = table[i][j];
        }
    }
    return transposed;
}
