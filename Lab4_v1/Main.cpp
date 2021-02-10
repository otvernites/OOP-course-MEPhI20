#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Main_function.h"

using namespace Accs;

void (*dialogs[])(accTable&) = {
        nullptr,
        Dialog_open_account, 
        Dialog_show_account_status,
        Dialog_close_account,
        Dialog_work_with_account,
        Dialog_get_all_accounts 
};

int Get_solution() {
    std::string menu[] = {
        "0. Exit",
        "1. Open account",
        "2. Show account status",
        "3. Close account",
        "4. Work with account",
        "5. Get all account",
    };

    int solve = -1;
    do {
        system("cls");
        for (int i = 0; i < 6; i++) {
            std::cout << menu[i] << std::endl;
        }
        std::cout << "Input number of function" << std::endl;
        getNum(solve);
    } while ((solve < 0) || (solve > 5));

    return solve;
}

int main()
{
    accTable new_table;
    
    int solution = 0;
    while (solution = Get_solution()) {
        system("cls");
        dialogs[solution](new_table);
        system("pause");
    }
}
