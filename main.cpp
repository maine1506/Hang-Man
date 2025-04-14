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

vector<string> loadWords(const string& filename);
vector<string> getImage(const string& filename);
void waitUntilKeyPressed();
void processPressAt(char guess, Hangman& game);

int main(int argc, char *argv[])
{
    srand(time(0));

    Graphics graphics;
    graphics.init();

    Hangman game;
    game.init();

    graphics.render(game);

    bool quit = false;
    SDL_Event event;
    while (!quit && !game.endGame()) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            SDL_Keycode keyPressed = event.key.keysym.sym;

            if (keyPressed >= SDLK_a && keyPressed <= SDLK_z) {
                char guess = (char)keyPressed;
                processPressAt(guess, game);

                graphics.render(game);
                break;
            }
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

void processPressAt(char guess, Hangman& game) {
    game.guess = guess;
    game.nextImage(guess);
}
