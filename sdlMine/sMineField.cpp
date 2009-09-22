/* 
 * File:   sMineField.cpp
 * Author: walle
 * 
 * Created on August 26, 2009, 7:59 AM
 */

#include "sMineField.h"

#include <iostream>

namespace sdlMine
{
    MineField::MineField(int width, int height, int numMines, int seed) : libMine::MineField(width, height, numMines, seed)
    {
        this->surface = NULL;
        this->cellWidth = 16;

        // Load the images
        this->loadImages();

    }

    MineField::~MineField()
    {
        for (int i = 0; i < this->images.size(); i++)
        {
            SDL_FreeSurface(this->images.at(i));
        }
    }
    
    void MineField::render()
    {
        for (int y = 0; y < this->getHeight(); y++)
        {
           for (int x = 0; x < this->getWidth(); x++)
           {
               SDL_Rect outer;
               outer.x = x * this->cellWidth;
               outer.y = y * this->cellWidth;
               outer.w = this->cellWidth;
               outer.h = this->cellWidth;

               SDL_Rect inner;
               inner.x = x * this->cellWidth + 1;
               inner.y = y * this->cellWidth + 1;
               inner.w = this->cellWidth - 2;
               inner.h = this->cellWidth - 2;

               libMine::CellState state = this->getState(x, y);
               SDL_FillRect(this->surface, &outer, 0x686868);
               switch (state)
               {
                   case libMine::OPEN:
                       SDL_FillRect(this->surface, &inner, 0xa6a6a6);
                   break;
                   case libMine::FLAG:
                       //SDL_FillRect(this->surface, &inner, 0x0000ff);
                       SDL_FillRect(this->surface, &inner, 0xc4c4c4);
                       SDL_BlitSurface(this->images.at(0), NULL, this->surface, &inner);
                   break;
                   case libMine::MINE:
                       SDL_FillRect(this->surface, &inner, 0x00ff00);
                   break;
                   case libMine::FLAGERROR:
                       SDL_FillRect(this->surface, &inner, 0xcdff44);
                       SDL_BlitSurface(this->images.at(0), NULL, this->surface, &inner);
                   break;
                   case libMine::CLOSED:
                       SDL_FillRect(this->surface, &inner, 0xc4c4c4);
                   break;
                   default:
                       //SDL_FillRect(this->surface, &inner, 0xfefefe / state);
                       SDL_FillRect(this->surface, &inner, 0xa6a6a6);
                       SDL_BlitSurface(this->images.at(state), NULL, this->surface, &inner);
                   break;
               }
           }
        }
    }

    bool MineField::open(int x, int y)
    {
        int cX = x / this->cellWidth;
        int cY = y / this->cellWidth;

        if (cX > this->width || cX < 0 || cY > this->height || cY < 0)
        {
            return false;
        }

        libMine::CellState res = this->examine(cX, cY);

        switch (res)
        {
            case libMine::MINE:
                std::cout << "Boom!" << std::endl << "Game Over!" << std::endl;

                // Reveal all the mines
                this->openAll();

                // Draw the loosing minefield
                this->render();

                return true;
            break;
            case libMine::OPEN:
                std::cout << "The cell (" << cX << ", " << cY << ") is open" << std::endl;
            break;
            case libMine::ALREADYOPEN:
                std::cout << "The cell (" << cX << ", " << cY << ") is already opened" << std::endl;
            break;
            case libMine::FLAG:
                std::cout << "The cell (" << cX << ", " << cY << ") is flagged" << std::endl;
            break;
            // Closed meens error in this context, not allowed
            case libMine::CLOSED:
            case libMine::ERROR:
                std::cout << "Error!" << std::endl;
            break;
            default:
                /*
                 * ONE,
                 * TWO,
                 * THREE,
                 * FOUR,
                 * FIVE,
                 * SIX,
                 * SEVEN,
                 * EIGHT
                 */
                std::cout << "The cell (" << cX << ", " << cY << ") has " << res << " adjecent mines" << std::endl;
            break;
        }

        if (this->win())
        {
            std::cout << "You win!" << std::endl;

            // Shows all mines
            this->flagAllMines();

            // Draw the winning minefield
            this->render();

            return true;
        }

        return false;
    }

    bool MineField::flag(int x, int y)
    {
        int cX = x / this->cellWidth;
        int cY = y / this->cellWidth;

        if (cX > this->width || cX < 0 || cY > this->height || cY < 0)
        {
            return false;
        }

        if(this->field.at((this->width * cY + cX)))
        {
            libMine::CellState res = this->field.at((this->width * cY + cX))->getState();
            if (this->numFlags >= this->numMines && res != libMine::FLAG)
            {
                return false;
            }
            this->field.at((this->width * cY + cX))->flag();
            if (res == libMine::FLAG)
            {
                this->numFlags--;
            }
            else
            {
                this->numFlags++;
            }
            return true;
        }
    }

    void MineField::blinkAdjecent(int x, int y)
    {
        int cX = x / this->cellWidth;
        int cY = y / this->cellWidth;

        if(this->field.at((this->width * cY + cX)))
        {
            // The premiss is that the cell has adjecent mines so we check the state
            if(this->field.at((this->width * cY + cX))->getState() > libMine::CLOSED && this->field.at((this->width * cY + cX))->getState() != libMine::OPEN)
            {
                std::vector<libMine::Cell*> adjecent = this->field.at((this->width * cY + cX))->getAdjecent();

                for (int i = 0; i < libMine::Cell::numAdjecent; i++)
                {
                    if (adjecent.at(i))
                    {
                        if (adjecent.at(i)->getState() == libMine::CLOSED)
                        {
                            SDL_Rect outer;
                            outer.x = adjecent.at(i)->getX() * this->cellWidth;
                            outer.y = adjecent.at(i)->getY() * this->cellWidth;
                            outer.w = this->cellWidth;
                            outer.h = this->cellWidth;

                            std::cout << "Blinking the cell (" << adjecent.at(i)->getX() << ", " << adjecent.at(i)->getY() << ")" << std::endl;

                            SDL_FillRect(this->surface, &outer, 0x00ff00);
                        }
                    }
                }
            }
        }
    }

    SDL_Surface* MineField::loadImage(std::string file)
    {
        SDL_Surface* tmp = IMG_Load(file.c_str());

        // Cast the int to a float to return float from the division
        double xScale = (this->cellWidth*1.0f) / tmp->w;
        double yScale = (this->cellWidth*1.0f) / tmp->h;

        tmp = zoomSurface(tmp, xScale, yScale, 1);
        // TODO: Need new images for this, removes transparacy
        //tmp = SDL_DisplayFormat(tmp);

        return tmp;
    }

    void MineField::loadImages()
    {
        this->images.resize(9);
        this->images.at(0) = this->loadImage("res/flag.png");
        this->images.at(1) = this->loadImage("res/1.png");
        this->images.at(2) = this->loadImage("res/2.png");
        this->images.at(3) = this->loadImage("res/3.png");
        this->images.at(4) = this->loadImage("res/4.png");
        this->images.at(5) = this->loadImage("res/5.png");
        this->images.at(6) = this->loadImage("res/6.png");
        this->images.at(7) = this->loadImage("res/7.png");
        this->images.at(8) = this->loadImage("res/8.png");
    }
}

