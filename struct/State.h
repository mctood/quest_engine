//
// Created by rogatka on 13.03.2025.
//

#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include "Button.h"

using namespace std;

class State {
public:
    string text;
    vector<vector<Button>> buttons;

    explicit State(const string &text) {
        this->text = text;
    };

    void defineButtons(const vector<vector<Button>> &buttons) {
        this->buttons = buttons;
    }
};

#endif //STATE_H
