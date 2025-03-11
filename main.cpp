#include <bits/stdc++.h>
#include <windows.h>

#include "Box.h"
#include "Button.h"

#define STATE_PADDING 20
#define BLOCK_MULTIPLIER 0.8
#define BUTTON_MARGIN 2
#define ButtonRows vector<vector<Button>>

using namespace std;

int SizeToInt(const unsigned long long &size) {
    return static_cast<int>(size);
}

unsigned int ZeroSafe(int num) {
    if (num < 0) num = 0;
    return num;
}

pair<int, int> GetTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer);
    int columns = buffer.srWindow.Right - buffer.srWindow.Left + 1;
    int rows = buffer.srWindow.Bottom - buffer.srWindow.Top + 1;
    return {columns, rows};
}

string CenteredLine(const string &text) {
    int halfSize = SizeToInt(text.size()) / 2;
    int halfTerminalWidth = GetTerminalSize().first / 2;

    string out(
        ZeroSafe(halfTerminalWidth - halfSize),
        ' '
    );

    out += text;
    return out;
}

int CoutCenteredTextWithFixedWidth(const string& text, const unsigned int maxWidth) {
    vector<string> words;
    string word;
    for (auto &c : text) {
        if (c == ' ' || c == '\n') {
            words.push_back(word);
            word.clear();
            continue;
        }

        word += c;
    }
    words.push_back(word);
    word.clear();

    vector<string> lines;
    string line;
    for (int i = 0; i < words.size(); i++) {
        line += words[i] + " ";

        if (line.size() + words[i + 1].size() > maxWidth && !line.empty()) {
            lines.push_back(line);
            line.clear();
        }
    }
    lines.push_back(line);
    line.clear();

    for (auto &l : lines) {
        cout << CenteredLine(l) << endl;
    }

    return SizeToInt(lines.size());
}

int GetBlockWidth() {
    int consoleWidth = GetTerminalSize().first;
    int blockWidth;
    if (consoleWidth < 100) blockWidth = consoleWidth;
    else blockWidth = consoleWidth * BLOCK_MULTIPLIER;

    return blockWidth;
}

void RenderButtons(ButtonRows buttons) {
    int spaceWidth = GetBlockWidth() - STATE_PADDING;

    for (int k = 0; k < buttons.size(); k++) {
        auto row = buttons[k];

        int buttonsCount = SizeToInt(row.size());
        int buttonWidth = spaceWidth / buttonsCount;

        if (buttonsCount > 1) {
            buttonWidth -= BUTTON_MARGIN * (buttonsCount - 1) / buttonsCount;
        }

        string buttonsTop;
        string buttonsMiddle;
        string buttonsBottom;
        Button lastButton = row[buttonsCount - 1];

        for (int i = 0; i < buttonsCount; i++) {
            string text = row[i].text;
            char interaction = row[i].interaction;

            string buttonTop(buttonWidth - 2, Box::HLINE);
            buttonTop = Box::TLCORNER + buttonTop + Box::TRCORNER;
            buttonTop[4] = Box::PADTOP;
            buttonsTop += buttonTop;

            string buttonMiddle(1, Box::VLINE);
            buttonMiddle += ' ';
            buttonMiddle += interaction;
            buttonMiddle += ' ';
            buttonMiddle += Box::VLINE;
            buttonMiddle += ' ';
            buttonMiddle += text;
            buttonMiddle += string(buttonWidth - 7 - text.size(), ' ');
            buttonMiddle += Box::VLINE;
            buttonsMiddle += buttonMiddle;

            string buttonBottom(buttonWidth - 2, Box::HLINE);
            buttonBottom = Box::BLCORNER + buttonBottom + Box::BRCORNER;
            buttonBottom[4] = Box::PADBOTTOM;
            buttonsBottom += buttonBottom;

            if (i != buttonsCount - 1) {
                buttonsTop += string(BUTTON_MARGIN, ' ');
                buttonsMiddle += string(BUTTON_MARGIN, ' ');
                buttonsBottom += string(BUTTON_MARGIN, ' ');
            }
        }

        cout << CenteredLine(buttonsTop) << endl;
        cout << CenteredLine(buttonsMiddle) << endl;
        cout << CenteredLine(buttonsBottom) << endl;

        // if (k != buttons.size() - 1) {
        //     cout << endl;
        //     lines++;
        // }
    }
}

int DetermineButtonLinesQuantity(const ButtonRows &buttons) {
    return buttons.size() * 3;
}

void RenderState(const string &txt, const ButtonRows &buttons) {
    system("cls");

    int blockWidth = GetBlockWidth();
    int terminalHeight = GetTerminalSize().second;

    string Separator(blockWidth - 2, Box::HLINE);
    string BottomSeparator = Box::BLCORNER + Separator + Box::BRCORNER;
    string TopSeparator = Box::TLCORNER + Separator + Box::TRCORNER;

    // top separator
    cout << CenteredLine(TopSeparator) << endl;
    cout << endl;

    // output text
    int textLines = CoutCenteredTextWithFixedWidth(txt, blockWidth - STATE_PADDING);

    // go to terminal bottom
    int buttonLines = DetermineButtonLinesQuantity(buttons);
    for (int i = 0;  i < terminalHeight - textLines - buttonLines - 3; i++) cout << endl;

    // output buttons
    RenderButtons(buttons);

    // bottom separator
    cout << CenteredLine(BottomSeparator);

    // wait for user input
    // cin.get();
}

[[noreturn]] int main() {

    string txt = "Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of ... (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance.";
    ButtonRows buttons {
        {
            Button('x', "Выход"),
            Button('y', "Тоже выход"),
        },
    };

    RenderState(txt, buttons);

    int rows = GetTerminalSize().second;
    int cols = GetTerminalSize().first;
    while (true) {
        if (GetTerminalSize().first != cols || GetTerminalSize().second != rows) {
            RenderState(txt, buttons);
            rows = GetTerminalSize().second;
            cols = GetTerminalSize().first;
        }
    }
}