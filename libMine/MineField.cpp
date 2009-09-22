/* 
 * File:   MineField.cpp
 * Author: walle
 * 
 * Created on August 19, 2009, 7:19 AM
 */

#include <stdlib.h>

#include "MineField.h"

namespace libMine
{
    MineField::MineField(int width, int height, int numMines, int seed)
    {
        this->width = width;
        this->height = height;
        this->numMines = numMines;
        this->seed = seed;

        // Init the counters
        this->numCells = this->width * this->height;
        this->numClosedCells = this->numCells;
        this->numFlags = 0;

        this->field.resize(this->numCells);

        this->init();
    }

    MineField::~MineField()
    {
        // Clear the field
        for (int i = 0; i < this->numCells; i++)
        {
            delete this->field.at(i);
        }
    }

    void MineField::init()
    {
        srand(this->seed);

        // Init the field
        for (int y = 0; y < this->height; y++)
        {
            for (int x = 0; x < this->width; x++)
            {
                int index = (this->width * y + x);

                // Init the cell
                this->field.at(index) = new Cell(x, y, false, CLOSED);
            }
        }

        // Place all mines
        for (int i = 0; i < this->numMines; i++)
        {
            // Randomize a location
            int x = rand() % this->width;
            int y = rand() % this->height;
            int index = (this->width * y + x);

            // If its mined choose a new
            while (this->field.at(index)->isMined())
            {
                x = rand() % this->width;
                y = rand() % this->height;
                index = (this->width * y + x);
            }

            // Place the mine
            this->field.at(index)->setMined(true);
        }

        // Set the adjecent data
        for (int y = 0; y < this->height; y++)
        {
            for (int x = 0; x < this->width; x++)
            {
                std::vector<Cell*> adjecent;
                adjecent.resize(Cell::numAdjecent);

                adjecent.at(TOPLEFT) = NULL;
                adjecent.at(TOP) = NULL;
                adjecent.at(TOPRIGHT) = NULL;
                adjecent.at(RIGHT) = NULL;
                adjecent.at(BOTTOMRIGHT) = NULL;
                adjecent.at(BOTTOM) = NULL;
                adjecent.at(BOTTOMLEFT) = NULL;
                adjecent.at(LEFT) = NULL;

                int index = (this->width * y + x);

                int topleft = (this->width * (y - 1) + (x - 1));
                int top = (this->width * (y - 1) + (x));
                int topright = (this->width * (y - 1) + (x + 1));
                int right = (this->width * (y) + (x + 1));
                int bottomright = (this->width * (y + 1) + (x + 1));
                int bottom = (this->width * (y + 1) + (x));
                int bottomleft = (this->width * (y + 1) + (x - 1));
                int left = (this->width * (y) + (x - 1));

                bool sameRowLeft = (x - 1 >= 0);
                bool sameRowRight = (x + 1 < this->width);

                if (topleft >= 0 && sameRowLeft)
                {
                    adjecent.at(TOPLEFT) = this->field.at(topleft);
                }

                if (top >= 0)
                {
                    adjecent.at(TOP) = this->field.at(top);
                }

                if (topright >= 0 && sameRowRight)
                {
                    adjecent.at(TOPRIGHT) = this->field.at(topright);
                }

                if (right <= this->numCells && sameRowRight)
                {
                    adjecent.at(RIGHT) = this->field.at(right);
                }

                if (bottomright < this->numCells && sameRowRight)
                {
                    adjecent.at(BOTTOMRIGHT) = this->field.at(bottomright);
                }

                if (bottom < this->numCells)
                {
                    adjecent.at(BOTTOM) = this->field.at(bottom);
                }

                if (bottomleft < this->numCells && sameRowLeft)
                {
                    adjecent.at(BOTTOMLEFT) = this->field.at(bottomleft);
                }

                if (left >= 0 && sameRowLeft)
                {
                    adjecent.at(LEFT) = this->field.at(left);
                }

                this->field.at(index)->setAdjecent(adjecent);
            }
        }

    }

    CellState MineField::examine(int x, int y)
    {
        if(this->field.at((this->width * y + x)))
        {
            Cell* cell = this->field.at((this->width * y + x));
            CellState res = cell->examine();

            if (res > CLOSED)
            {
                this->numClosedCells--;
            }
            
            if (res == OPEN)
            {
                // Loop through all adjecent mines ad explore them too
                for (int i = 0; i < cell->numAdjecent; i++)
                {
                    if(cell->getAdjecent().at(i))
                    {
                        this->examine(cell->getAdjecent().at(i)->getX(), cell->getAdjecent().at(i)->getY());
                    }
                }
            }

            return res;
        }

        return ERROR;
    }

    bool MineField::flag(int x, int y)
    {
        if(this->field.at((this->width * y + x)))
        {
            CellState res = this->field.at((this->width * y + x))->getState();
            if (this->numFlags == this->numMines && res != FLAG)
            {
                return false;
            }
            this->field.at((this->width * y + x))->flag();
            if (res == FLAG)
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

    CellState MineField::getState(int x, int y)
    {
        if(this->field.at((this->width * y + x)))
        {
            return this->field.at((this->width * y + x))->getState();
        }
    }

    void MineField::openAll()
    {
        for (int i = 0; i < this->numCells; i++)
        {
            if (this->field.at(i)->getState() == FLAG && this->field.at(i)->isMined() == false)
            {
                this->field.at(i)->setState(FLAGERROR);
            }
            else
            {
                this->field.at(i)->examine();
            }
        }
    }

    void MineField::flagAllMines()
    {
        for (int i = 0; i < this->numCells; i++)
        {
            if (this->field.at(i)->isMined())
            {
                this->field.at(i)->setState(FLAG);
            }
            else if (this->field.at(i)->getState() == FLAG)
            {
                this->field.at(i)->setState(FLAGERROR);
            }
        }
    }
}
