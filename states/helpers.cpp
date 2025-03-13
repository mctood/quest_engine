#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "../struct/State.h"
#include "../struct/Button.h"
#include "../struct/Box.h"

#define ButtonRows vector<vector<Button>>
#define STATE_PADDING 20
#define BLOCK_MULTIPLIER 0.8
#define BUTTON_MARGIN 2

using namespace std;

int SizeToInt(const unsigned long long &size) {
    return static_cast<int>(size);
}
char IntToChar(const int &ch) {
    return static_cast<char>(ch);
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

unsigned int PadToCenter(const unsigned int width) {
    int halfSize = SizeToInt(width) / 2;
    int halfTerminalWidth = GetTerminalSize().first / 2;

    return ZeroSafe(halfTerminalWidth - halfSize);
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
        string cl = CenteredLine(l);
        for (char &c : cl) {
            if (c == ' ') cout << c;
            else {
                cout << c;
                Sleep(30);
            }
        }
        cout << endl;
    }

    return SizeToInt(lines.size());
}

int GetBlockWidth() {
    int consoleWidth = GetTerminalSize().first;
    int blockWidth;
    if (consoleWidth < 100) blockWidth = consoleWidth;
    else blockWidth = floor(consoleWidth * BLOCK_MULTIPLIER);

    return blockWidth;
}

int DetermineButtonLinesQuantity(const ButtonRows &buttons) {
    return SizeToInt(buttons.size()) * 3;
}

void RenderButtons(const ButtonRows &buttons) {
    int spaceWidth = GetBlockWidth() - STATE_PADDING;

    for (const vector<Button> &row : buttons) {

        int buttonsCount = SizeToInt(row.size());
        int buttonWidth = spaceWidth / buttonsCount;

        if (buttonsCount > 1) {
            buttonWidth -= BUTTON_MARGIN * (buttonsCount - 1) / buttonsCount;
        }

        auto padCenter = string(PadToCenter(buttonWidth * buttonsCount + BUTTON_MARGIN * (buttonsCount - 1)), ' ');

        // print buttons top
        cout << padCenter;
        for (int i = 0; i < buttonsCount; i++) {
            string buttonTop(buttonWidth - 2, Box::HLINE);
            buttonTop[3] = Box::PADTOP;
            cout << Box::TLCORNER << buttonTop << Box::TRCORNER;

            if (i != buttonsCount - 1) {
                cout << string(BUTTON_MARGIN, ' ');
            }
        }
        cout << endl;

        // print buttons mid
        cout << padCenter;
        for (int i = 0; i < buttonsCount; i++) {
            cout << Box::VLINE << ' ' << row[i].interaction << ' ' << Box::VLINE << ' ';

            SetConsoleOutputCP(1251);
            cout << row[i].text;
            SetConsoleOutputCP(866);

            cout << string(buttonWidth - 7 - row[i].text.size(), ' ') << Box::VLINE;

            if (i != buttonsCount - 1) {
                cout << string(BUTTON_MARGIN, ' ');
            }
        }
        cout << endl;

        // print buttons bottom
        cout << padCenter;
        for (int i = 0; i < buttonsCount; i++) {
            string buttonBottom(buttonWidth - 2, Box::HLINE);
            buttonBottom[3] = Box::PADBOTTOM;
            cout << Box::BLCORNER << buttonBottom << Box::BRCORNER;

            if (i != buttonsCount - 1) {
                cout << string(BUTTON_MARGIN, ' ');
            }
        }
        cout << endl;
    }
}


[[noreturn]] void RenderState(const State& state) {
    const string &txt = state.text;
    const ButtonRows &buttons = state.buttons;

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
    SetConsoleOutputCP(1251);
    int textLines = CoutCenteredTextWithFixedWidth(txt, blockWidth - STATE_PADDING);
    SetConsoleOutputCP(866);

    // go to terminal bottom
    int buttonLines = DetermineButtonLinesQuantity(buttons);
    for (int i = 0;  i < terminalHeight - textLines - buttonLines - 3; i++) cout << endl;

    // output buttons
    RenderButtons(buttons);

    // bottom separator
    cout << CenteredLine(BottomSeparator);

    // wait for user input

    map<char, function<void()>> buttonActions;
    for (const auto& row : buttons) {
        for (const Button& button : row) {
            buttonActions.insert({button.interaction, button.onclick});
        }
    }

    gt:
        int g = getch();
        if (char key = IntToChar(g); buttonActions[key]) {
            buttonActions[key]();
        }
    goto gt;
}