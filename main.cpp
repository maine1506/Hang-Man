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

enum GameState {
    HOME,
    PLAYING,
    WIN,
    LOSE
};

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

    GameState gameState = HOME;

    int i = 0;
    bool flag = false;
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (gameState == HOME) {
                if (checkButtonClick(x, y, graphics.playButton)) {
                    game.init();
                    keyboard.reset();
                    gameState = PLAYING;
                    graphics.render(game, keyboard);
                }
            }
            else if (gameState == PLAYING) {
                flag = false;
                if (checkButtonClick(x, y, graphics.hintButton)) {
                    game.showHint(keyboard);
                }
                processClick(x, y, keyboard, game);
                if (!game.gameOver()) {
                    graphics.render(game, keyboard);
                } else {
                    gameState = (game.won() ? WIN : LOSE);
                }
            }
            else if (gameState == WIN) {
                if (checkButtonClick(x, y, graphics.playNextButton)) {
                    game.level++;
                    game.init();
                    keyboard.reset();
                    gameState = PLAYING;
                    graphics.render(game, keyboard);
                }
                else if (checkButtonClick(x, y, graphics.homeButton)) {
                    gameState = HOME;
                }
            }
            else if (gameState == LOSE) {
                if (checkButtonClick(x, y, graphics.playAgainButton)) {
                    game.level = 1;
                    game.init();
                    keyboard.reset();
                    gameState = PLAYING;
                    graphics.render(game, keyboard);
                }
                else if (checkButtonClick(x, y, graphics.homeButton)) {
                    gameState = HOME;
                }
            }
            break;
        }

        if (gameState == HOME) {
            game.level = 1;
            game.init();
            keyboard.reset();
            graphics.renderHomeScreen();
        }
        else if (gameState == WIN || gameState == LOSE) {
            if (gameState == WIN && !flag) {
                game.score += 5;
                flag = true;
            }
            graphics.renderFinalDisplay(game, i);
            SDL_Delay(140);
        }

        if (gameState == PLAYING && !game.gameOver()) {
            SDL_Delay(50);
        }
    }

    graphics.quit();
    return 0;
}



