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

void waitUntilKeyPressed();
void processClick(int mouseX, int mouseY, Keyboard& keyboard, Hangman& game);

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Keyboard keyboard;
    keyboard.init();

    Hangman game;
    game.init();

    graphics.render(game, keyboard);
    //graphics.renderKeyboard(keyboard);

    int x, y;
    bool quit = false;
    SDL_Event event;
    while (!quit && !game.endGame()) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
             SDL_GetMouseState(&x, &y);
             processClick(x, y, keyboard, game);
             graphics.render(game, keyboard);
             graphics.renderKeyboard(keyboard);
             break;
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int mouseX, int mouseY, Keyboard& keyboard, Hangman& game) {
    for (auto& btn : keyboard.keyboard) {
        if (!btn.clicked &&
            mouseX >= btn.rect.x && mouseX <= btn.rect.x + btn.rect.w &&
            mouseY >= btn.rect.y && mouseY <= btn.rect.y + btn.rect.h) {

            btn.clicked = true;

            game.nextImage(btn);

            break;
        }
    }
}

