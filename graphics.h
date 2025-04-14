#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "logic.h"

using namespace std;

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture* background;

    SDL_Texture *_nextFrame, *_guessedWord, *Wordsdonotexist, *Wrongtimes, *Yourguess;
    TTF_Font* font = nullptr;
    SDL_Color color = {0, 0, 0, 0};


    void init() {
        initSDL();
        font = loadFont("assets/8bitoperator.ttf", 18);
        background = loadTexture("assets/bg0.png");
    }

    void render(const Hangman& game) {

        prepareScene(background);

        //SDL_Texture* _nextFrame = renderText(game.nextFrame, font, color);
        //renderTexture(_nextFrame, 200, 200);
        //SDL_Texture* _nextFrame = renderText(game.nextFrame.c_str(), font, color);
        //renderTexture(_nextFrame, 20, 101);
        //SDL_DestroyTexture(tempTexture);

        SDL_Texture* _guessedWord = renderText(game.guessedWord.c_str(), font, color);
        renderTextureMid(_guessedWord, 400, 500);

        SDL_Texture* Wordsdonotexist = renderText(game.wrongGuesses.c_str(), font, color);
        renderTexture(Wordsdonotexist, 500, 566);

        string wrongTimesText = to_string(game.badGuessCount) + "/" + to_string(MAX_BAD_GUESSES);
        SDL_Texture* Wrongtimes = renderText(wrongTimesText.c_str(), font, color);
        renderTexture(Wrongtimes, 162, 566);

        presentScene();
    }

    void logErrorAndExit(const char* msg, const char* error)
    {
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

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
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

    SDL_Texture* renderText(const char* text,
                            TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface =
                TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

        void renderTextureMid(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        dest.x = x - dest.w / 2;
        dest.y = y - dest.h / 2;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void quit() {
        TTF_Quit();
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

};

#endif // _GRAPHICS__H
