/* 
 * File:   main.cpp
 * Author: walle
 *
 * Created on August 20, 2009, 5:40 PM
 */

#include <iostream>

#include "SDL/SDL.h"

#include "sMineField.h"

#include "FileConfig.h"
#include "MineController.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    srand(time(0));
    SDL_Surface* screen;
    SDL_Surface* fieldSurface;
    SDL_Surface* ctrlSurface;
    SDL_Rect fieldRect;
    SDL_Rect ctrlRect;
    SDL_Event event;
    bool done = false;

    libConf::FileConfig* conf = new libConf::FileConfig("sdlMine.conf");

    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1))
    {
        std::cerr << "Could not initialize SDL: %s." <<  SDL_GetError() << std::endl;
        exit(1);
    }

    atexit(SDL_Quit);

    conf->load();

    int numW = conf->readInt("width");
    int numH = conf->readInt("height");
    int numM = conf->readInt("mines");
    int cellW = conf->readInt("cellwidth");
    int seed = conf->readInt("seed");
    if (seed == 0) { seed = rand(); }

    int yOffset = 40;

    int width = numW * cellW;
    int height = numH * cellW + yOffset;

    fieldRect.x = 0;
    fieldRect.y = yOffset;
    fieldRect.w = width;
    fieldRect.h = numH * cellW;

    ctrlRect.x = 0;
    ctrlRect.y = 0;
    ctrlRect.w = width;
    ctrlRect.h = yOffset;

    screen = SDL_SetVideoMode(width, height, 32, SDL_HWACCEL|SDL_HWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        std::cerr << "Could not initialize SDL video" << SDL_GetError() << std::endl;
    }

    SDL_WM_SetCaption("SDL Mine", "");

    fieldSurface = SDL_CreateRGBSurface(SDL_HWACCEL|SDL_HWSURFACE|SDL_ANYFORMAT, width, numH * cellW, 32, 0, 0, 0, 0);
    ctrlSurface = SDL_CreateRGBSurface(SDL_HWACCEL|SDL_HWSURFACE|SDL_ANYFORMAT, width, yOffset, 32, 0, 0, 0, 0);

    sdlMine::MineField* field = new sdlMine::MineField(numW, numH, numM, seed);
    field->setSurface(fieldSurface);
    field->setCellSize(cellW);

    sdlMine::MineController* ctrl = new sdlMine::MineController(ctrlSurface, numM);

    while(!done)
    {
        SDL_FillRect(screen, NULL, 0x000000);

        ctrl->render();
        field->render();

        SDL_BlitSurface(ctrlSurface, NULL, screen, &ctrlRect);
        SDL_BlitSurface(fieldSurface, NULL, screen, &fieldRect);
        
        SDL_Flip(screen);

        ctrl->update();

        SDL_WaitEvent(&event);

        // TODO: Check for win or loose and stop all updating then

        switch (event.type)
        {
            case SDL_QUIT:
                done = true;
            break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = true;
                    }
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
                {
                    field->blinkAdjecent(event.button.x, event.button.y - yOffset);
                }
            break;
            case SDL_MOUSEBUTTONUP:

                // Start the timer
                ctrl->startTimer();

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    field->open(event.button.x, event.button.y - yOffset);
                    continue;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    field->flag(event.button.x, event.button.y - yOffset);
                    continue;
                }
            break;
        }
    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(fieldSurface);

    delete field;
    delete conf;
    
    return 0;
}

