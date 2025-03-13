#include <windows.h>
#include <cstdio>
#include "states/helpers.cpp"
#include "states/states.cpp"
#include "states/buttons.cpp"
#include "utils/color.cpp"

using namespace std;

[[noreturn]] int main() {
    SetConsoleOutputCP(866);
    set_col(color::white, color::black);
    cout << "\u001B[32m";
    buttons();

    RenderState(state1);


    // int rows = GetTerminalSize().second;
    // int cols = GetTerminalSize().first;
    // while (true) {
    //     if (GetTerminalSize().first != cols || GetTerminalSize().second != rows) {
    //         RenderState(txt, buttons);
    //         rows = GetTerminalSize().second;
    //         cols = GetTerminalSize().first;
    //     }
    // }
}