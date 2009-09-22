/* 
 * File:   Cell.cpp
 * Author: walle
 * 
 * Created on August 19, 2009, 6:58 AM
 */

#include <stdlib.h>

#include "Cell.h"

namespace libMine
{
    Cell::Cell()
    {
        this->x = 0;
        this->y = 0;
        this->mined = false;
        this->adjecent.resize(Cell::numAdjecent);
        this->state = CLOSED;
    }

    Cell::Cell(int x, int y, bool mined, CellState state)
    {
        this->x = x;
        this->y = y;
        this->mined = mined;
        this->state = state;
        this->adjecent.resize(Cell::numAdjecent);
    }

    Cell::~Cell()
    {
        
    }

    CellState Cell::examine()
    {
        if (this->state > CLOSED)
        {
            return ALREADYOPEN;
        }

        if (this->state == FLAG)
        {
            return FLAG;
        }

        if (this->mined)
        {
            this->state = MINE;
            return MINE;
        }

        this->state = OPEN;

        int numAdjecentMines = 0;
        for (int i = 0; i < this->numAdjecent; i++)
        {
            if(this->adjecent.at(i))
            {
                if (this->adjecent.at(i)->isMined())
                {
                    numAdjecentMines++;
                }
            }
        }

        if (numAdjecentMines > 0)
        {
            this->state = (CellState)numAdjecentMines;
        }

        // The enum is ordered so the name of the number is at number
        return this->state;
    }

    void Cell::flag()
    {
        if (this->state == CLOSED)
        {
            this->state = FLAG;
        }
        else if (this->state == FLAG)
        {
            this->state = CLOSED;
        }
    }
}