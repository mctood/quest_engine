#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using namespace std;

class Button {
public:
    string text;
    char interaction;
    function<void()> onclick = []{};

    Button(const char interaction, const string &text, const function<void()> &onclick) {
        this->text = text;
        this->interaction = interaction;
        this->onclick = onclick;
    }
};

#endif //BUTTON_H
