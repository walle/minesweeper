/* 
 * File:   sMineField.h
 * Author: walle
 *
 * Created on August 26, 2009, 7:59 AM
 */

#ifndef _SMINEFIELD_H
#define	_SMINEFIELD_H

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

#include "MineField.h"

namespace sdlMine
{
    class MineField : public libMine::MineField
    {
    public:
        MineField(int width, int height, int numMines, int seed);
        virtual ~MineField();

        /**
         * The sdl implementation of the rendering
         */
        void render();

        /**
         * Examines a cell if the cell exists,
         * this function takes w and h in pixels
         */
        bool open(int x, int y);

        /**
         * This flag method takes the coordinates in pixels
         */
        bool flag(int x, int y);

        /**
         * Show all closed adjecent cells by
         * rendering them in a special way
         * This function works with coordinates in pixels
         */
        void blinkAdjecent(int x, int y);

        /**
         * Set the pointer to the surface used in rendering
         */
        void setSurface(SDL_Surface* surface) { this->surface = surface; }

        /**
         * Set the cell size
         */
        void setCellSize(int size) { this->cellWidth = size; this->loadImages(); }

    private:
        /**
         * Loads and scales a image
         */
        SDL_Surface* loadImage(std::string file);

        /**
         * Loads all images
         */
        void loadImages();

        SDL_Surface* surface;
        int cellWidth;
        std::vector<SDL_Surface*> images;
    };
}

#endif	/* _SMINEFIELD_H */

