#include "MineController.h"

namespace sdlMine
{
    MineController::MineController(SDL_Surface* surface, int mines)
    {
        this->mines = mines;
        this->surface = surface;
        this->seconds = 0;
        this->state = NORMAL;
        this->lastTick = 0;
        this->timerStarted = false;
    }

    MineController::~MineController()
    {

    }

    void MineController::render()
    {
        SDL_FillRect(this->surface, NULL, 0x123456);
    }

    void MineController::update()
    {
        if (SDL_GetTicks() > this->lastTick + 1000 && this->timerStarted)
        {
            this->lastTick = SDL_GetTicks();
            this->seconds++;
            std::cout << this->seconds << " seconds" << std::endl;
        }
    }
}
