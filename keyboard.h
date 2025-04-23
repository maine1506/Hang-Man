#ifndef _KEYBOARD__H
#define _KEYBOARD__H

#include <vector>

#define startX 20
#define startY 220
#define buttonW 25
#define buttonH 25
#define spacing 7


using namespace std;

struct Keyboard {
    char letter;
    SDL_Rect rect;
    bool clicked;
    bool correct;
    vector<Keyboard> keyboard;
    vector<string> rows = {
            "QWERTYUIOP",
            "ASDFGHJKL",
            "ZXCVBNM"
        };

    void init() {
        for (int row = 0; row < rows.size(); ++row) {
            int x = startX + row * 25;
            int y = startY + row * (buttonH + spacing);

            for (int i = 0; i < rows[row].size(); ++i) {
                Keyboard btn;
                btn.letter = rows[row][i];
                btn.rect = { x + i * (buttonW + spacing), y, buttonW, buttonH };
                btn.clicked = false;
                btn.correct = false;
                keyboard.push_back(btn);
            }
        }
    }

};
#endif // _KEYBOARD__H


