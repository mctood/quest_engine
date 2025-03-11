#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using namespace std;

class Button {
public:
    string text;
    char interaction;

    Button(const char interaction, const string& text) {
        this->interaction = interaction;
        this->text = text;
    }

    // void onInteract() ...

    bool operator==(const Button &b) const {
        return this == &b;
    }
    bool operator!=(const Button &b) const {
        return this != &b;
    }
};



#endif //BUTTON_H
