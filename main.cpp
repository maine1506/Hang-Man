#include <iostream>
#include <ctime>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "logic.h"
#include "defs.h"

using namespace std;

bool checkButtonClick(int mouseX, int mouseY, SDL_Rect buttonRect) {
    return (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);
}

void processClick(int mouseX, int mouseY, Keyboard& keyboard, Hangman& game) {
    for (auto& btn : keyboard.keys) {
        if (!btn.clicked && checkButtonClick(mouseX, mouseY, btn.rect)) {
            btn.clicked = true;
            game.nextImage(btn);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Keyboard keyboard;
    keyboard.init();

    Hangman game;
    game.init();

    graphics.render(game, keyboard);

    int i = 0;
    bool quit = false;
    SDL_Event event;
    SDL_Rect playAgain = graphics.clickButtonRect(graphics.playAgain);
    SDL_Rect playNext = graphics.clickButtonRect(graphics.playNext);

    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (game.gameOver()) {
                if (game.lost()
                && checkButtonClick(x, y, playAgain)) {
                    game.init();
                    keyboard.reset();
                    graphics.render(game, keyboard);
                    i = 0;
                }
                else if (game.won()
                && checkButtonClick(x, y, playNext)) {
                    game.init();
                    keyboard.reset();
                    graphics.render(game, keyboard);
                    i = 0;
                }
            } else {
                processClick(x, y, keyboard, game);
                if (!game.gameOver()) graphics.render(game, keyboard);
            }
            break;
        default:
            if (game.gameOver()) {
                graphics.renderFinalDisplay(game, i);
                SDL_Delay(140);
            }
        }
        if (!game.gameOver()) SDL_Delay(50);
    }

    graphics.quit();
    return 0;
}



