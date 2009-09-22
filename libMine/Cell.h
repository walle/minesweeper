/* 
 * File:   Cell.h
 * Author: walle
 *
 * Created on August 19, 2009, 6:58 AM
 */

#ifndef _CELL_H
#define	_CELL_H

#include <vector>

namespace libMine
{
    /**
     * Represents a fixed position in the adjecent array
     */
    enum Placement
    {
        TOPLEFT = 0,
        TOP,
        TOPRIGHT,
        RIGHT,
        BOTTOMRIGHT,
        BOTTOM,
        BOTTOMLEFT,
        LEFT
    };

    /**
     * Represents the state a cell can be in
     */
    enum CellState
    {
        ERROR = -5,
        FLAGERROR = -4,
        ALREADYOPEN = -3,
        MINE = -2,
        FLAG = -1,
        CLOSED = 0,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        OPEN
    };

    /**
     * Represents a cell in a minefield
     */
    class Cell
    {
    public:
        Cell();
        Cell(int x, int y, bool mined, CellState state);
        virtual ~Cell();

        static const int numAdjecent = 8;

        /**
         * Test the cell for mine
         * Returns the new state OPEN, MINE or NUMBER
         */
        CellState examine();

        /**
         * Toggles the flag
         * Checks if it's possible to flag the cell and does so if that is the case
         */
        void flag();

        /**
         * Checks if the cell contains a mine
         */
        bool isMined() { return this->mined; }

        /**
         * Set the mined value
         */
        void setMined(bool value) { this->mined = value; }

        /**
         * Return the state the cell is in
         */
        CellState getState() { return this->state; }

        /**
         * Setter for the value, should be used with care
         */
        void setState(CellState value) { this->state = value; }

        /**
         * Returns all neighbors
         */
        std::vector<Cell*> getAdjecent() { return this->adjecent; }

        /**
         * Sets all the adjecent, this is because a loop is
         * needed to create the cells then another loop to
         * set the adjecent pointers to correct objects
         */
        void setAdjecent(std::vector<Cell*> adjecent) { this->adjecent = adjecent; }

        /**
         * Get the position
         */
        int getX() { return this->x; }
        int getY() { return this->y; }

        /**
         * Utility functions to get specific neigbors
         */
        Cell* getTopLeft() { return this->adjecent.at(TOPLEFT); }
        Cell* getTop() { return this->adjecent.at(TOP); }
        Cell* getTopRight() { return this->adjecent.at(TOPRIGHT); }
        Cell* getRight() { return this->adjecent.at(RIGHT); }
        Cell* getBottomRight() { return this->adjecent.at(BOTTOMRIGHT); }
        Cell* getBottom() { return this->adjecent.at(BOTTOM); }
        Cell* getBottomLeft() { return this->adjecent.at(BOTTOMLEFT); }
        Cell* getLeft() { return this->adjecent.at(LEFT); }

    private:
        int x;
        int y;
        bool mined;
        std::vector<Cell*> adjecent;
        CellState state;
    };
} // libMine

#endif	/* _CELL_H */

