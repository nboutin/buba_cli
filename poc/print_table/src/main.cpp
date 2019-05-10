
#include <iostream>
#include <string>
#include <vector>

/*

+--Title1--+--Title2--+
|value     |value     +


*/

using line_t = std::vector<std::string>;

void print_table(const std::vector<line_t> table)
{
    using namespace std;

    //    const auto sep_title = '+';
    const auto sep_value = '|';

    for(auto line : table)
    {
        for(auto element : line)
        {
            cout << sep_value << element;
        }
        cout << sep_value << "\n";
    }
    cout << flush;
}

int main()
{
    using namespace std;

    vector<line_t> table{{"Title1", "Title2"}, {"value11", "value12"}, {"value21", "value22"}};

    print_table(table);

    return 0;
}
