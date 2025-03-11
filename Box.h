#ifndef BOX_H
#define BOX_H

using namespace std;

class Box {
public:
    static char TLCORNER;
    static char TRCORNER;
    static char BLCORNER;
    static char BRCORNER;
    static char HLINE;
    static char PADTOP;
    static char PADBOTTOM;
    static char VLINE;
};
char Box::HLINE = '\xC4';
char Box::TLCORNER = '\xDA';
char Box::TRCORNER = '\xBF';
char Box::BLCORNER = '\xC0';
char Box::BRCORNER = '\xD9';
char Box::PADTOP = '\xC2';
char Box::PADBOTTOM = '\xC1';
char Box::VLINE = '\xB3';

#endif //BOX_H
