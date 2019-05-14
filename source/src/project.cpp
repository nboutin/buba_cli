
#include "project.h"
#include "printer.h"

#include <buba.h>

#include <iostream>

using namespace std;

bool project_create(buba::Budget_Battle& buba, const param_t& params)
{
    const auto project_test = "./test.bubap";
    const auto param        = (params.at(0) == "test") ? project_test : params.at(0);

    if(param == project_test)
        std::system(std::string("rm "s + project_test).c_str());

    if(!buba.project_create(param))
        cerr << red << "[Error] cannot create project:" << param << reset << endl;
    else
        cout << green << "[OK] project created" << reset << endl;

    return true;
}

bool project_open(buba::Budget_Battle& buba, const param_t& params)
{
    const auto param = params.at(0);

    if(!buba.project_open(param))
        cerr << red << "[Error] cannot open project:" << param << reset << endl;
    else
        cout << green << "[OK] project opened:" << param << reset << endl;

    return true;
}

bool project_close(buba::Budget_Battle& buba, const param_t& params)
{
    (void) params;

    buba.project_close();
    cout << green << "[OK] project closed" << reset << endl;

    return true;
}
