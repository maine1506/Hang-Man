#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "keyboard.h"
#include "logic.h"

using namespace std;

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture* background, *correct, *wrong, *playAgain, *playNext;
    vector<SDL_Texture*> stage;
    vector<SDL_Texture*> lose;
    vector<SDL_Texture*> win;
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color blue = {58,135,190, 0};

    void init() {
        initSDL();
        loadTextures();
    }

    void loadTextures() {
        background = loadTexture("assets/background.png");
        correct = loadTexture("assets/correct.png");
        wrong = loadTexture("assets/wrong.png");
        playAgain = loadTexture("assets/playagain.png");
        playNext = loadTexture("assets/playnext.png");
        for (int i = 0; i < MAX_BAD_GUESSES; ++i) {
            string path = "assets/st" + to_string(i) + ".png";
            stage.push_back(loadTexture(path.c_str()));
        }
        lose.push_back(loadTexture("assets/cry0.png"));
        lose.push_back(loadTexture("assets/cry1.png"));
        win.push_back(loadTexture("assets/yeah0.png"));
        win.push_back(loadTexture("assets/yeah1.png"));
    }

    SDL_Rect clickButtonRect(SDL_Texture *texture) {
        SDL_Rect rect;
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        rect.x = 130;
        rect.y = 220;
        return rect;
    }

    void drawTextBox(const string& text, int centerX, int centerY, SDL_Color textColor, SDL_Color borderColor) {
        int thickness = 2;
        SDL_Texture* texture = renderText(text.c_str(), "assets/sarifa.ttf", 19, textColor);

        int textW, textH;
        SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

        int paddingX = 20;
        int paddingY = 4;
        SDL_Rect boxRect = {
            centerX - (textW + paddingX * 2) / 2,
            centerY - (textH + paddingY * 2) / 2,
            textW + paddingX * 2,
            textH + paddingY * 2
        };

        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        for (int i = 0; i < thickness; i++) {
            SDL_RenderDrawRect(renderer, &boxRect);
            boxRect.x += 1;
            boxRect.y += 1;
            boxRect.w -= 2;
            boxRect.h -= 2;
        }

        SDL_Rect textRect = {
            boxRect.x + paddingX - thickness,
            boxRect.y + paddingY - thickness,
            textW,
            textH
        };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_DestroyTexture(texture);
    }

    void render(const Hangman& game, Keyboard& keyboard) {
        prepareScene(background);

        renderTexture(stage[game.badGuessCount], 0, 0);

        string spaced = "";
        for (char c : game.guessedWord) {
            spaced += c;
            spaced += ' ';
        }

        SDL_Texture* guessedWord = renderText(spaced.c_str(), "assets/sarifa.ttf", 26, black);

        drawTextBox(game.currentEntry.category, 170, 100, blue, black);

        renderTextureMid(guessedWord, 170, 150);

        renderKeyboard(keyboard);

        presentScene();
    }

    void renderFinalDisplay(const Hangman& game, int& i) {
        prepareScene(background);

        string spaced = "";
        for (char c : game.secretWord) {
            spaced += c;
            spaced += ' ';
        }
        SDL_Texture* guessedWord = renderText(spaced.c_str(), "assets/sarifa.ttf", 26, black);
        SDL_Texture* msg;

        if (game.lost()) {
            renderTexture(lose[i % lose.size()], 0, 0);
            i++;
            msg = renderText("You lost!", "assets/sarifa.ttf", 20, black);
            renderTexture(playAgain, 130, 220);
        } else if (game.won()) {
            renderTexture(win[0], 0, 0);
            i++;
            msg = renderText("You won!", "assets/sarifa.ttf", 20, black);
            renderTexture(playNext, 130, 220);
        }

        drawTextBox(game.currentEntry.category, 170, 100, blue, black);
        renderTextureMid(guessedWord, 170, 150);
        renderTextureMid(msg, 170, 190);
        presentScene();
    }

    void renderKeyboard(const Keyboard& keyboard) {
        for (const auto& btn : keyboard.keys) {
            SDL_Texture* texture = renderText(string(1, btn.letter).c_str(), "assets/sarifa.ttf", 26, blue);

            int textW, textH;
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect textRect = {
                btn.rect.x + (btn.rect.w - textW) / 2,
                btn.rect.y + (btn.rect.h - textH) / 2,
                textW, textH
            };
            SDL_RenderCopy(renderer, texture, NULL, &textRect);

            SDL_DestroyTexture(texture);

            if (btn.clicked) {
                SDL_Rect iconRect = {
                    btn.rect.x + (btn.rect.w - 26) / 2,
                    btn.rect.y + (btn.rect.h - 26) / 2,
                    26, 26
                };

                if (btn.correct) {
                    SDL_RenderCopy(renderer, correct, NULL, &iconRect);
                } else {
                    SDL_RenderCopy(renderer, wrong, NULL, &iconRect);
                }
            }
        }
    }

    void logErrorAndExit(const char* msg, const char* error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
    }

    void prepareScene(SDL_Texture * background) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene() {
        SDL_RenderPresent(renderer);
    }

    TTF_Font* loadFont(const char* path, int size) {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
        return gFont;
    }


    SDL_Texture* renderText(const char* text, const char* path,
                            int size, SDL_Color textColor)
    {
        TTF_Font* font = loadFont(path, size);

        SDL_Surface* textSurface =
                TTF_RenderText_Blended(font, text, textColor);
        if(textSurface == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            TTF_CloseFont(font);
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);

        return texture;
    }

    SDL_Texture *loadTexture(const char *filename) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderTextureMid(SDL_Texture *texture, int x, int y) {
        SDL_Rect dest;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x - dest.w / 2;
        dest.y = y - dest.h / 2;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }


    void quit() {
        TTF_Quit();
        IMG_Quit();
        for (auto tex : stage) SDL_DestroyTexture(tex);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(correct);
        SDL_DestroyTexture(wrong);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

};

#endif // _GRAPHICS__H
