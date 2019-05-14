
#include "import.h"
#include "printer.h"

#include <buba.h>

#include <iostream>

using namespace std;

bool command_import(buba::Budget_Battle& buba, const param_t& params)
{
    const auto param = params.at(0);

    if(!buba.import_ofx(param))
        cerr << red << "[Error] cannot import OFX file:" << param << reset << endl;
    else
        cout << green << "[OK] OFX file imported:" << param << reset << endl;

    return true;
}
