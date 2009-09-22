/* 
 * File:   MineController.h
 * Author: walle
 *
 * Created on September 4, 2009, 6:26 PM
 */

#ifndef _MINECONTROLLER_H
#define	_MINECONTROLLER_H

#include <iostream>

#include "SDL/SDL.h"

namespace sdlMine
{
    enum State
    {
        NORMAL,
        DEAD,
        COOL
    };

    class MineController
    {
    public:
        MineController(SDL_Surface* surface, int numMines);
        virtual ~MineController();

        /**
         * Render the controller
         */
        void render();

        /**
         * Updates the countes and other logic
         */
        void update();

        /**
         * Starts the seconds counter
         */
        void startTimer() { this->timerStarted = true; this->lastTick = SDL_GetTicks(); }

        /**
         * Checks if the timer is running
         */
        bool isRunning() { return this->timerStarted; }

        /**
         * Getter for the mine counter
         */
        int getMinesLeft() { return this->mines; }

        /**
         * Setter for the mine counter
         */
        void setMinesLeft(int value) { this->mines = value; }

        /**
         * Setter fot the state
         */
        void setState(State value) { this->state = value; }

        /**
         * Getter for the second counter
         */
        int getSeconds() { return this->seconds; }

    private:
        int seconds;
        int mines;
        State state;
        SDL_Surface* surface;
        long lastTick;
        bool timerStarted;
    };
}

#endif	/* _MINECONTROLLER_H */

