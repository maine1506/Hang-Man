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

void processClick(int mouseX, int mouseY, Keyboard& keyboard, Hangman& game) {
    for (auto& btn : keyboard.keys) {
        if (!btn.clicked &&
            mouseX >= btn.rect.x && mouseX <= btn.rect.x + btn.rect.w &&
            mouseY >= btn.rect.y && mouseY <= btn.rect.y + btn.rect.h) {

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

    bool quit = false;
    SDL_Event event;
    while (!quit && !game.gameOver()) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            processClick(x, y, keyboard, game);
            graphics.render(game, keyboard);
            break;
        }
        SDL_Delay(30);
    }

    graphics.quit();
    return 0;
}



