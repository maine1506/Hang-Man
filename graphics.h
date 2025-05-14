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
    SDL_Texture* background, *correct, *wrong, * play, *playAgain, *playNext,
               *home, *diamond, *hint;
    vector<SDL_Texture*> stage;
    vector<SDL_Texture*> lose;
    vector<SDL_Texture*> win;
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color blue = {58, 135, 190, 0};
    SDL_Color green = {55, 220, 148, 0};
    SDL_Color red = {255, 0, 0, 0};
    SDL_Rect dest;
    SDL_Rect playAgainButton, playNextButton,
             playButton, homeButton, hintButton;

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
        play = loadTexture("assets/play.png");
        home = loadTexture("assets/home.png");
        diamond = loadTexture("assets/diamond.png");
        hint = loadTexture("assets/hint.png");
        for (int i = 0; i < MAX_BAD_GUESSES; ++i) {
            string path = "assets/st" + to_string(i) + ".png";
            stage.push_back(loadTexture(path.c_str()));
        }
        lose.push_back(loadTexture("assets/cry0.png"));
        lose.push_back(loadTexture("assets/cry1.png"));
        win.push_back(loadTexture("assets/yeah0.png"));
        win.push_back(loadTexture("assets/yeah1.png"));
    }

    void renderHomeScreen() {
        prepareScene(background);
        SDL_Texture* title = renderText("H A N G M A N", "assets/sarifa.ttf", 40, green);
        SDL_Texture* underscore = renderText("_  _  _  _  _  _  _", "assets/sarifa.ttf", 39, green);
        renderTextureMid(title, SCREEN_WIDTH / 2, 55, dest);
        renderTextureMid(underscore, SCREEN_WIDTH / 2, 63, dest);
        renderTextureMid(play, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, playButton);
        SDL_DestroyTexture(title);
        SDL_DestroyTexture(underscore);
        presentScene();
    }

    void drawTextBox(const string& text, int centerX, int centerY, SDL_Color textColor, SDL_Color borderColor) {
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
        int thickness = 2;
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
        SDL_Texture* title = renderText("H A N G M A N", "assets/sarifa.ttf", 33, green);
        SDL_Texture* underscore = renderText("_  _  _  _  _  _  _", "assets/sarifa.ttf", 32, green);
        renderTextureMid(title, SCREEN_WIDTH / 2, 37, dest);
        renderTextureMid(underscore, SCREEN_WIDTH / 2, 42, dest);
        SDL_DestroyTexture(title);
        SDL_DestroyTexture(underscore);

        renderTexture(stage[game.badGuessCount], 0, 0, dest);
        renderTextureScaled(diamond, 13, 13, 0.9f, dest);
        renderTextureScaled(hint, 565, 260, 1.0f, hintButton);

        string spaced = "";
        for (char c : game.guessedWord) {
            spaced += c;
            spaced += ' ';
        }
        SDL_Texture* guessedWord = renderText(spaced.c_str(), "assets/sarifa.ttf", 26, black);
        renderTextureMid(guessedWord, 170, 150, dest);
        SDL_DestroyTexture(guessedWord);

        renderTextureScaled(diamond, 554, 238, 0.6f, dest);
        SDL_Texture* hintScore = renderText("10/hint", "assets/sarifa.ttf", 17, blue);
        renderTextureMid(hintScore, 600, 245, dest);
        SDL_DestroyTexture(hintScore);

        string levelText = "Level " + to_string(game.level);
        SDL_Texture* levelTex = renderText(levelText.c_str(), "assets/sarifa.ttf", 20, blue);
        renderTextureMid(levelTex, 440, 125, dest);
        SDL_DestroyTexture(levelTex);

        SDL_Texture* scoreText = renderText(to_string(game.score).c_str(), "assets/sarifa.ttf", 27, blue);
        renderTexture(scoreText, 47, 7, dest);
        SDL_DestroyTexture(scoreText);

        drawTextBox(game.currentEntry.category, 170, 100, blue, black);

        renderKeyboard(keyboard);

        presentScene();
    }

    void renderFinalDisplay(const Hangman& game, int& i) {
        prepareScene(background);
        SDL_Texture* title = renderText("H A N G M A N", "assets/sarifa.ttf", 33, green);
        SDL_Texture* underscore = renderText("_  _  _  _  _  _  _", "assets/sarifa.ttf", 32, green);
        renderTextureMid(title, SCREEN_WIDTH / 2, 37, dest);
        renderTextureMid(underscore, SCREEN_WIDTH / 2, 42, dest);
        SDL_DestroyTexture(title);
        SDL_DestroyTexture(underscore);

        string spaced = "";
        for (char c : game.secretWord) {
            spaced += c;
            spaced += ' ';
        }
        SDL_Texture* guessedWord = renderText(spaced.c_str(), "assets/sarifa.ttf", 26, black);
        renderTextureMid(guessedWord, 170, 150, dest);
        SDL_DestroyTexture(guessedWord);

        renderTextureScaled(diamond, 140, 215, 1.0f, dest);

        SDL_Texture* msg;
        if (game.lost()) {
            renderTexture(lose[i % lose.size()], 0, 0, dest);
            i++;
            msg = renderText("You lost!!!", "assets/sarifa.ttf", 20, red);
            renderTextureScaled(playAgain, 185, 260, 0.8f, playAgainButton);
            renderTextureScaled(home, 82, 260, 0.8f, homeButton);
        } else if (game.won()) {
            renderTexture(win[0], 0, 0, dest);
            i++;
            msg = renderText("You won!!!", "assets/sarifa.ttf", 20, green);
            renderTextureScaled(playNext, 185, 260, 0.8f, playNextButton);
            renderTextureScaled(home, 82, 260, 0.8f, homeButton);
        }
        renderTextureMid(msg, 170, 190, dest);
        SDL_DestroyTexture(msg);

        string levelText = "Level " + to_string(game.level);
        SDL_Texture* levelTex = renderText(levelText.c_str(), "assets/sarifa.ttf", 20, blue);
        renderTextureMid(levelTex, 440, 125, dest);
        SDL_DestroyTexture(levelTex);

        SDL_Texture* scoreText = renderText(to_string(game.score).c_str(), "assets/sarifa.ttf", 27, blue);
        renderTexture(scoreText, 177, 210, dest);
        SDL_DestroyTexture(scoreText);

        drawTextBox(game.currentEntry.category, 170, 100, blue, black);

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
                int iconRectW, iconRectH;
                SDL_QueryTexture(correct, NULL, NULL, &iconRectW, &iconRectH);

                SDL_Rect iconRect = {
                    btn.rect.x + (btn.rect.w - iconRectW) / 2,
                    btn.rect.y + (btn.rect.h - iconRectH) / 2,
                    iconRectW, iconRectH
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

    void renderTexture(SDL_Texture *texture, int x, int y, SDL_Rect& dest) {
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderTextureMid(SDL_Texture *texture, int x, int y, SDL_Rect& dest) {
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x - dest.w / 2;
        dest.y = y - dest.h / 2;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderTextureScaled(SDL_Texture* texture, int x, int y, float scale, SDL_Rect& dest) {
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.w *= scale;
        dest.h *= scale;
        dest.x = x;
        dest.y = y;
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void quit() {
        TTF_Quit();
        IMG_Quit();
        for (auto tex : stage) SDL_DestroyTexture(tex);
        for (auto tex : lose) SDL_DestroyTexture(tex);
        for (auto tex : win) SDL_DestroyTexture(tex);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(correct);
        SDL_DestroyTexture(wrong);
        SDL_DestroyTexture(playAgain);
        SDL_DestroyTexture(playNext);
        SDL_DestroyTexture(play);
        SDL_DestroyTexture(home);
        SDL_DestroyTexture(diamond);
        SDL_DestroyTexture(hint);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

};

#endif // _GRAPHICS__H
