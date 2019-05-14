
#include "project.h"

#include <iostream>

using namespace std;

void project_create(buba::Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;
    cout << __func__ << endl;

    for(auto p : params)
        cout << p << endl;
}

void project_open(buba::Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;
    cout << __func__ << endl;

    for(auto p : params)
        cout << p << endl;
}

void project_close(buba::Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;
    cout << __func__ << endl;

    for(auto p : params)
        cout << p << endl;
}
