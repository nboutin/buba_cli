
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using line_t = std::vector<std::string>;

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

    //    for(auto m : maxs)
    //        cout << m << ",";
    //    cout << "\n";

    auto sep = sep_title;
    //    for(auto line : table)
    for(auto line = 0u; line < table.size(); ++line)
    {
        static auto title_line = true;
        if(title_line)
        {
            title_line = false;
            sep        = sep_title;
        }
        else
        {
            sep = sep_value;
        }

//        for(auto element : line)
        for(auto cell = 0u; cell < table[line].size(); ++cell)
        {
            cout << sep << table[line][cell] ;
        }
        cout << sep << "\n";
    }
    cout << flush;
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

int main()
{
    using namespace std;

    vector<line_t> table{{"Title", "TitleLong11", "T"},
                         {"valueLongLong15", "value", "ccc4"},
                         {"val", "value22", "cc"}};

    print_table(table);

    return 0;
}
