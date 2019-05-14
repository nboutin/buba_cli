
#include "account.h"
#include "bank.h"
#include "category.h"
#include "command.h"
#include "import.h"
#include "label.h"
#include "printer.h"
#include "project.h"
#include "read_input.h"
#include "transaction.h"

#include <buba.h>

#include <iostream>
#include <vector>

using namespace buba;
using namespace std;

bool command_help(buba::Budget_Battle&, const param_t& params);
bool command_quit(buba::Budget_Battle&, const param_t& params);

// clang-format off
const std::vector<command_t> commands = {
    {{"project", "new"}, {"p", "n"}, 1, &project_new},
    {{"project", "open"}, {"p", "o"}, 1, &project_open},
    {{"project", "close"}, {"p", "c"}, 0, &project_close},
    {{"import"}, {"i"}, 1, &command_import},
    {{"bank", "list"}, {"b", "l"}, 0, &bank_list},
    {{"bank", "set", "name"}, {"b", "s", "n"}, 2, &bank_set_name},
    {{"account", "list"}, {"a", "l"}, 0, &account_list},
    {{"account", "set", "name"}, {"a", "s", "n"}, 2, &account_set_name},
    {{"transaction", "list"}, {"t", "l"}, 0, &transaction_list},
    {{"transaction", "set", "label", "interactive"}, {"t", "s", "l", "i"}, 0, &transaction_set_label_interactive},
    {{"transaction", "set", "label"}, {"t", "s", "l"}, 2, &transaction_set_label},
    {{"label", "list"}, {"l", "l"}, 0, &label_list},
    {{"label", "add"}, {"l", "a"}, 1, &label_add},
    {{"label", "set", "category"}, {"l", "s", "c"}, 1, &label_set_category},
    {{"category", "list"}, {"c", "l"}, 0, &category_list},
	{{"help"}, {"h"}, 0, &command_help},
    {{"quit"}, {"q"}, 0, &command_quit},
};
// clang-format on

int main()
{
    Budget_Battle buba;

    while(process_command(commands, buba))
    {
    }
}

bool command_help(buba::Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;

    cout << "\nHelp" << endl;
    cout << "    project (p)" << endl;
    cout << "        new   (n) [pathname]" << endl;
    cout << "        open  (o) [pathname]" << endl;
    cout << "        close (c)" << endl;
    cout << "    import (i) [pathname]" << endl;
    cout << "    bank (b)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            name (n) <id> <name>" << endl;
    cout << "    account (a)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            name (n) <id> <name>" << endl;
    cout << "    transaction (t)" << endl;
    cout << "        list (l)" << endl;
    cout << "        set  (s)" << endl;
    cout << "            label (l) <fitid> <label_name>" << endl;
    cout << "    label (l)" << endl;
    cout << "        list (l)" << endl;
    cout << "        add  (a) <name>" << endl;
    cout << "        set  (s)" << endl;
    cout << "            category (c) <label_name> <category_name>" << endl;
    cout << "    category (c)" << endl;
    cout << "        list (l)" << endl;
    cout << "    help (h)" << endl;
    cout << "    quit (q)" << endl;

    return true;
}

bool command_quit(buba::Budget_Battle& buba, const param_t& params)
{
    (void) buba;
    (void) params;
    return false;
}
