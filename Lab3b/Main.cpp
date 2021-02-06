#include "../3b/Menu_fun.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace Lab3a;

void (*dialogs[])(Hex&) = {
        nullptr,
        Dialog_input,
        Dialog_output,
        Dialog_add,
        Dialog_subtract,
        Dialog_parity,
        Dialog_compare,
        Dialog_move_left,
        Dialog_move_right
};

int Get_solution() {
    const char* menu[] = {
        "0. Exit",
        "1. Input new number",
        "2. Output number",
        "3. Add number",
        "4. Subtract number",
        "5. Check parity",
        "6. Compare operands",
        "7. Move to the left",
        "8. Move to the right",
    };

    int solve = -1;
    do {
        system("cls");
        for (int i = 0; i < 9; i++) {
            std::cout << menu[i] << std::endl;
        }
        std::cout << "Input number of function" << std::endl;
        getNum(solve);
    } while ((solve < 0) || (solve > 8));

    return solve;
}

int main()
{
    Hex first;
    std::cout << "Enter the first decimal number: ";
    try {
        std::cin >> first;
    }
    catch (std::length_error& ex) {
        std::cout << ex.what() << std::endl;
        system("pause");
    }
    catch (std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
        system("pause");
    }

    int solution = 0;
    while (solution = Get_solution()) {
        system("cls");
        dialogs[solution](first);
        system("pause");
    }
}

